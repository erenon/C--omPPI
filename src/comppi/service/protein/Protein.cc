#include <algorithm>
#include <set>

#include <comppi/service/protein/Protein.h>
#include <comppi/service/Container.h>

#include <comppi/entity/Protein.h>
#include <comppi/entity/ProteinNameMap.h>

#include <comppi/entity/gen/Protein-odb.hxx>
#include <comppi/entity/gen/ProteinNameMap-odb.hxx>

namespace comppi {
namespace service {
namespace protein {

Protein::SelfPtr Protein::ServiceFactory::create(Container& container) {
    auto databasePtr = container.get<database::Database>();

    return std::make_shared<Protein>(databasePtr);
}

Protein::Protein(
    database::DatabasePtr databasePtr
)
    :_databasePtr(databasePtr)
{
    // TODO init naming convention order by config
    _namingConventionOrder = {
        "UniProtKB/Swiss-Prot",
        "UniProtKB/TrEmbl",
        "UniProtKB/Deleted",
        "UniProtKB-AC",
        "UniProtFull",
        "UniProtKB-ID",
        "UniProtAlt",
        "EnsemblGeneId",
        "EntrezGene",
        "refseq",
        "WBGeneId",
        "EnsemblPeptideId",
        "Hprd"
    };
}

std::vector<entity::Protein>
Protein::translate(const entity::Protein& protein) {
    std::vector<entity::Protein> persistedProteins;
    if (_translationCache.get(protein, persistedProteins)) {
        return persistedProteins;
    }

    database::Transaction transaction(_databasePtr->begin());

    auto translations = getStrongestTranslations(protein);

    // transform translation -> protein
    std::vector<entity::Protein> proteins;
    proteins.reserve(translations.size());

    for (auto translation : translations) {
        proteins.push_back(entity::Protein(
            protein.getSpecieId(),
            translation.getProteinNameB(),
            translation.getNamingConventionB()
        ));
    }

    persistedProteins.reserve(proteins.size());

    for (auto protein : proteins) {
        persistedProteins.push_back(persistProtein(protein));
    }

    transaction.commit();

    _translationCache.add(protein, persistedProteins);

    return persistedProteins;
}

/**
 * Must run in transaction
 */
std::vector<entity::ProteinNameMap>
Protein::getStrongestTranslations(const entity::Protein& protein) {
    typedef odb::query<entity::ProteinNameMap> Query;
    typedef odb::prepared_query<entity::ProteinNameMap> PrepQuery;
    typedef odb::result<entity::ProteinNameMap> Result;

    entity::Protein* pProtein;

    PrepQuery pqStrongerTranslations(
        _databasePtr->lookup_query<entity::ProteinNameMap>(
            "protein-stronger-translation",
            pProtein
        )
    );

    if (!pqStrongerTranslations) {
        DEBUG << "Prepare query: protein-stronger-translation";

        std::unique_ptr<entity::Protein> proteinPtr(
            new entity::Protein(protein)
        );

        pProtein = proteinPtr.get();

        Query qStrongerTranslations(
            Query::proteinNameA == Query::_ref(proteinPtr->getProteinName())
        &&  Query::namingConventionA == Query::_ref(proteinPtr->getProteinNamingConvention())
        &&  Query::specieId == Query::_ref(proteinPtr->getSpecieId())
        );

        pqStrongerTranslations = _databasePtr->prepare_query<entity::ProteinNameMap>(
            "protein-stronger-translation",
            qStrongerTranslations
        );

        _databasePtr->cache_query(
            pqStrongerTranslations,
            std::move(proteinPtr)
        );
    }

    *pProtein = protein;

    Result rStrongerTranslations(
        pqStrongerTranslations.execute()
    );

    auto strongestOrder = translationOrder(protein.getProteinNamingConvention());

    // get strongest translated name
    std::vector<entity::ProteinNameMap> translations;

    for (entity::ProteinNameMap& translation : rStrongerTranslations) {
        auto translatedNameOrder = translationOrder(translation.getNamingConventionB());

        if (translatedNameOrder < strongestOrder) {
            // stronger translation found
            strongestOrder = translatedNameOrder;

            // discard previous translations
            translations.clear();

            // add translation
            translations.push_back(translation);
        } else if (translatedNameOrder == strongestOrder) {
            // == : allow conventionA -> conventionA style maps
            // this is required because of the UniProtKB-AC secondary names

            // add translation
            translations.push_back(translation);
        } // else: translation is weaker, do nothing (discard)
    }

    if (!translations.empty()) { // translation found
        // try to get stronger translations using recursion
        std::vector<entity::ProteinNameMap> strongerTranslations;

        for (entity::ProteinNameMap& strongerTranslation : translations) {
            entity::Protein translatedProtein(
                protein.getSpecieId(),
                strongerTranslation.getProteinNameB(),
                strongerTranslation.getNamingConventionB()
            );

            auto evenStrongerTranslations =
                getStrongestTranslations(translatedProtein);

            strongerTranslations.reserve(
                strongerTranslations.size() + evenStrongerTranslations.size()
            );

            strongerTranslations.insert(
                strongerTranslations.end(),
                std::make_move_iterator(evenStrongerTranslations.begin()),
                std::make_move_iterator(evenStrongerTranslations.end())
            );
        }

        return strongerTranslations;
    } else {
        // no stronger translation found
        // return the one we got
        entity::ProteinNameMap map(
            protein.getSpecieId(),
            protein.getProteinNamingConvention(),
            protein.getProteinName(),
            protein.getProteinNamingConvention(),
            protein.getProteinName()
        );

        std::vector<entity::ProteinNameMap> translation(1, map);

        return translation;
    }
}

std::size_t Protein::translationOrder(
    const std::string& namingConvention
) const {
    auto it = std::find(
        _namingConventionOrder.begin(),
        _namingConventionOrder.end(),
        namingConvention
    );

    // if convention is not found,
    // return sufficently large invalid index
    return std::distance(_namingConventionOrder.begin(), it);
}

/**
 * Must run in transaction
 */
entity::Protein Protein::persistProtein(entity::Protein& protein) {
    typedef odb::query<entity::Protein> Query;
    typedef odb::prepared_query<entity::Protein> PrepQuery;
    typedef odb::result<entity::Protein> Result;

    Query qProtein(
        Query::proteinName == protein.getProteinName()
    &&  Query::proteinNamingConvention == protein.getProteinNamingConvention()
    &&  Query::specieId == protein.getSpecieId()
    );

    Result rProtein(_databasePtr->query<entity::Protein>(qProtein));

    // TODO enabling this slows the build to a crawl
    // reason unknown
//    entity::Protein* pProtein;
//
//    PrepQuery pqProtein(
//        _databasePtr->lookup_query<entity::Protein>(
//            "protein-protein",
//            pProtein
//        )
//    );
//
//    if (!pqProtein) {
//        DEBUG << "Prepare query: protein-protein";
//
//        std::unique_ptr<entity::Protein> proteinPtr(
//            new entity::Protein(protein)
//        );
//
//        pProtein = proteinPtr.get();
//
//        Query qProtein(
//            Query::proteinName == Query::_ref(proteinPtr->getProteinName())
//        &&  Query::proteinNamingConvention == Query::_ref(proteinPtr->getProteinNamingConvention())
//        &&  Query::specieId == Query::_ref(proteinPtr->getSpecieId())
//        );
//
//        pqProtein = _databasePtr->prepare_query<entity::Protein>(
//            "protein-protein",
//            qProtein
//        );
//
//        _databasePtr->cache_query(
//            pqProtein,
//            std::move(proteinPtr)
//        );
//    }
//
//    *pProtein = protein;
//
//    Result rProtein(pqProtein.execute());

    if (!rProtein.empty()) {
        return *rProtein.begin();
    } else {
        _databasePtr->persist(protein);
        return protein;
    }
}

std::vector<entity::Protein> Protein::synonyms(const entity::Protein& protein) {
    std::vector<entity::Protein> synonyms(1, protein);
    getSynonyms(synonyms);

    return synonyms;
}

std::vector<entity::Protein> Protein::getSynonyms(std::vector<entity::Protein>& proteins) {
    std::set<std::string> conventionsFound;

    for (const auto& protein : proteins) {
        conventionsFound.insert(protein.getProteinNamingConvention());
    }

    std::vector<entity::Protein> newSynonyms;

    for (const auto& protein : proteins) {
        auto strongers = getStrongerSynonyms(protein);
        auto weakers = getWeakerSynonyms(protein);

        newSynonyms.reserve(strongers.size() + weakers.size());

        for (const auto& stronger : strongers) {
            if (conventionsFound.count(stronger.getProteinNamingConvention()) == 0) {
                newSynonyms.push_back(stronger);
            }
        }

        for (const auto& weaker : weakers) {
            if (conventionsFound.count(weaker.getProteinNamingConvention()) == 0) {
                newSynonyms.push_back(weaker);
            }
        }
    }

    // get synonyms of synonyms
    if (!newSynonyms.empty()) {
        auto secSynonyms = getSynonyms(newSynonyms);
        proteins.reserve(proteins.size() + secSynonyms.size());
        proteins.insert(proteins.end(), secSynonyms.begin(), secSynonyms.end());
    }

    return proteins;
}

std::vector<entity::Protein> Protein::getWeakerSynonyms(const entity::Protein& protein) {
    typedef odb::query<entity::ProteinNameMap> Query;
    typedef odb::prepared_query<entity::ProteinNameMap> PrepQuery;
    typedef odb::result<entity::ProteinNameMap> Result;

    entity::Protein* pProtein;

    PrepQuery pqWeakerSynonyms(
        _databasePtr->lookup_query<entity::ProteinNameMap>(
            "protein-weaker-synonyms",
            pProtein
        )
    );

    if (!pqWeakerSynonyms) {
        DEBUG << "Prepare query: protein-weaker-synonyms";

        std::unique_ptr<entity::Protein> proteinPtr(
            new entity::Protein(protein)
        );

        pProtein = proteinPtr.get();

        Query qWeakerSynonyms(
            Query::proteinNameB == Query::_ref(proteinPtr->getProteinName())
        &&  Query::namingConventionB == Query::_ref(proteinPtr->getProteinNamingConvention())
        &&  Query::specieId == Query::_ref(proteinPtr->getSpecieId())
        );

        pqWeakerSynonyms = _databasePtr->prepare_query<entity::ProteinNameMap>(
            "protein-weaker-synonyms",
            qWeakerSynonyms
        );

        _databasePtr->cache_query(
            pqWeakerSynonyms,
            std::move(proteinPtr)
        );
    }

    *pProtein = protein;

    Result rWeakerSynonyms(
        pqWeakerSynonyms.execute()
    );

    std::vector<entity::Protein> synonyms;
    synonyms.reserve(rWeakerSynonyms.size());

    for (entity::ProteinNameMap& translation : rWeakerSynonyms) {
        synonyms.push_back(entity::Protein(
            protein.getSpecieId(),
            translation.getProteinNameA(),
            translation.getNamingConventionA()
        ));
    }

    return synonyms;
}

std::vector<entity::Protein> Protein::getStrongerSynonyms(const entity::Protein& protein) {
    typedef odb::query<entity::ProteinNameMap> Query;
    typedef odb::prepared_query<entity::ProteinNameMap> PrepQuery;
    typedef odb::result<entity::ProteinNameMap> Result;

    std::vector<entity::Protein> synonyms;
    if (protein.getProteinNamingConvention() == _namingConventionOrder[0]) {
        // no naming convention of higher order available
        return synonyms;
    }

    entity::Protein* pProtein;

    PrepQuery pqStrongerSynonyms(
        _databasePtr->lookup_query<entity::ProteinNameMap>(
            "protein-stronger-synonyms",
            pProtein
        )
    );

    if (!pqStrongerSynonyms) {
        DEBUG << "Prepare query: protein-stronger-synonyms";

        std::unique_ptr<entity::Protein> proteinPtr(
            new entity::Protein(protein)
        );

        pProtein = proteinPtr.get();

        Query qStrongerSynonyms(
            Query::proteinNameA == Query::_ref(proteinPtr->getProteinName())
        &&  Query::namingConventionA == Query::_ref(proteinPtr->getProteinNamingConvention())
        &&  Query::specieId == Query::_ref(proteinPtr->getSpecieId())
        );

        pqStrongerSynonyms = _databasePtr->prepare_query<entity::ProteinNameMap>(
            "protein-stronger-synonyms",
            qStrongerSynonyms
        );

        _databasePtr->cache_query(
            pqStrongerSynonyms,
            std::move(proteinPtr)
        );
    }

    *pProtein = protein;

    Result rStrongerSynonyms(
        pqStrongerSynonyms.execute()
    );

    synonyms.reserve(rStrongerSynonyms.size());

    for (entity::ProteinNameMap& translation : rStrongerSynonyms) {
        synonyms.push_back(entity::Protein(
            protein.getSpecieId(),
            translation.getProteinNameB(),
            translation.getNamingConventionB()
        ));
    }

    return synonyms;
}

} // namespace protein
} // namespace service
} // namespace comppi
