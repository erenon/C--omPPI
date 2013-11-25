#include <comppi/controller/Namelist.h>

#include <comppi/service/database/Database.h>

namespace comppi {
namespace controller {

Namelist::Namelist(service::Container& container)
    :_container(container)
{}

int Namelist::generate() {
    using service::database::Database;
    using service::database::Transaction;

    auto databasePtr = _container.get<Database>();

    Transaction transaction(databasePtr->begin());

    databasePtr->execute(
        "INSERT IGNORE INTO ProteinName(name)"
        " SELECT name FROM NameToProtein"
    );

    transaction.commit();

    return 0;
}

} // namespace controller
} // namespace comppi
