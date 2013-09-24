#include <comppi/service/database/Database.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace database {

Database::SelfPtr Database::ServiceFactory::create(Container& container) {
    auto config = container.get<config::Config>();

    return std::make_shared<odb::mysql::database>(
        config->get("database.user"),
        config->get("database.password"),
        config->get("database.database"),
        (const char*)0, // host
        0, // port
        (const char*)0, // socket
        config->get("database.charset")
    );
}

} // namespace database
} // namespace service
} // namespace comppi
