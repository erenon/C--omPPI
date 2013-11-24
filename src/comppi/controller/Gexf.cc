#include <comppi/controller/Gexf.h>

#include <comppi/service/database/Database.h>
#include <comppi/service/gexf/Writer.h>

#include <comppi/entity/Protein.h>
#include <comppi/entity/Interaction.h>
#include <comppi/entity/gen/Protein-odb.hxx>
#include <comppi/entity/gen/Interaction-odb.hxx>

namespace comppi {
namespace controller {

Gexf::Gexf(service::Container& container)
    :_container(container)
{}

int Gexf::generate() {
    using service::database::Database;
    using service::database::Transaction;
    using service::gexf::Writer;

    typedef odb::query<entity::Protein> PQuery;
    typedef odb::result<entity::Protein> PResult;

    typedef odb::query<entity::Interaction> IQuery;
    typedef odb::result<entity::Interaction> IResult;

    const size_t batchSize = 500;

    auto databasePtr = _container.get<Database>();
    auto writerPtr = _container.get<Writer>();

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

        writerPtr->addNodes(rProtein);
        lowerBound += batchSize;
    }

    lowerBound = 0;

    while (true) {
        IQuery qInteraction(
            IQuery::id >= lowerBound
        &&  IQuery::id < lowerBound + batchSize
        );

        IResult rInteraction(databasePtr->query<entity::Interaction>(qInteraction));

        if (rInteraction.empty()) {
            break;
        }

        writerPtr->addEdges(rInteraction);
        lowerBound += batchSize;
    }

    writerPtr->close();

    return 0;
}

} // namespace controller
} // namespace comppi
