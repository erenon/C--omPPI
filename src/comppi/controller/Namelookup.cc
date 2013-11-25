#include <memory>

#include <comppi/controller/Namelookup.h>

#include <comppi/service/database/Database.h>
#include <comppi/service/protein/Protein.h>

#include <comppi/entity/Protein.h>
#include <comppi/entity/gen/Protein-odb.hxx>
#include <comppi/entity/NameToProtein.h>
#include <comppi/entity/gen/NameToProtein-odb.hxx>

namespace comppi {
namespace controller {

Namelookup::Namelookup(service::Container& container)
    :_container(container)
{}

int Namelookup::generate() {
    using service::database::Database;
    using service::database::Transaction;

    typedef odb::query<entity::Protein> PQuery;
    typedef odb::result<entity::Protein> PResult;

    const size_t batchSize = 500;

    auto databasePtr = _container.get<Database>();
    auto sProtein = _container.get<service::protein::Protein>();

    Transaction transaction(databasePtr->begin());
    size_t lowerBound = 0;

    while (true) {
        PQuery qProtein(
            PQuery::id >= lowerBound
        &&  PQuery::id < lowerBound + batchSize
        );

        PResult rProtein(databasePtr->query<entity::Protein>(qProtein));

        if (rProtein.empty()) {
            break;
        }

        for (const entity::Protein& protein : rProtein) {
            auto proteinPtr = std::make_shared<entity::Protein>(protein);
            auto synonyms = sProtein->synonyms(protein);

            for (const auto& synonym : synonyms) {
                entity::NameToProtein nameToProtein(
                    synonym.getSpecieId(),
                    synonym.getProteinName(),
                    synonym.getProteinNamingConvention(),
                    proteinPtr
                );

                databasePtr->persist(nameToProtein);
            }
        }

        transaction.commit();
        transaction.reset(databasePtr->begin());

        lowerBound += batchSize;
    }

    transaction.commit();

    return 0;
}

} // namespace controller
} // namespace comppi
