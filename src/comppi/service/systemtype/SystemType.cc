#include <comppi/service/systemtype/SystemType.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace systemtype {

SystemType::SelfPtr SystemType::ServiceFactory::create(Container& container) {
    auto config = container.get<config::Config>();

    std::string systemPath(config->get("systemtype.system"));
    std::string synonymPath(config->get("systemtype.synonym"));

    auto databasePtr = container.get<database::Database>();

    return std::make_shared<SystemType>(systemPath, synonymPath, databasePtr);
}

SystemType::SystemType(
    const std::string& systemPath,
    const std::string& synonymPath,
    database::DatabasePtr databasePtr
)
    :_systemPath(systemPath),
     _synonymPath(synonymPath),
     _databasePtr(databasePtr)
{}

} // namespace systemtype
} // namespace service
} // namespace comppi
