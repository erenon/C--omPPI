#include <algorithm>

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
    // TODO add cache

    database::Transaction transaction(_databasePtr->begin());

    auto translations = getStrongestTranslations(protein);

    // transform translation -> protein
    std::vector<entity::Protein> proteins;
    proteins.reserve(translations.size());

    for (auto translation : translations) {
        // TODO use emplace if gcc version >= 4.8
        proteins.push_back(entity::Protein(
            protein.getSpecieId(),
            translation.getProteinNameB(),
            translation.getNamingConventionB()
        ));
    }

    std::vector<entity::Protein> persistedProteins;
    persistedProteins.reserve(proteins.size());

    for (auto protein : proteins) {
        persistedProteins.push_back(persistProtein(protein));
    }

    transaction.commit();

    return persistedProteins;
}

/**
 * Must run in transaction
 */
std::vector<entity::ProteinNameMap>
Protein::getStrongestTranslations(const entity::Protein& protein) {
    typedef odb::query<entity::ProteinNameMap> Query;
    typedef odb::result<entity::ProteinNameMap> Result;

    // TODO use prepared query
    // http://www.codesynthesis.com/products/odb/doc/manual.xhtml#4.5

    Query qStrongerTranslations(
        Query::specieId == protein.getSpecieId()
    &&  Query::proteinNameA == protein.getProteinName()
    &&  Query::namingConventionA == protein.getProteinNamingConvention());

    Result rStrongerTranslations(
        _databasePtr->query<entity::ProteinNameMap>(qStrongerTranslations)
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
    typedef odb::result<entity::Protein> Result;

    // TODO use prepared query
    Query qProtein(
        Query::specieId == protein.getSpecieId()
    &&  Query::proteinName == protein.getProteinName()
    &&  Query::proteinNamingConvention == protein.getProteinNamingConvention()
    );

    Result rProtein(_databasePtr->query<entity::Protein>(qProtein));

    if (!rProtein.empty()) {
        return *rProtein.begin();
    } else {
        _databasePtr->persist(protein);
        return protein;
    }
}

} // namespace protein
} // namespace service
} // namespace comppi
