#ifndef COMPPI_SERVICE_SYSTEMTYPE_SYSTEMTYPE_H_
#define COMPPI_SERVICE_SYSTEMTYPE_SYSTEMTYPE_H_

#include <memory>
#include <string>
#include <map>
#include <vector>

#include <comppi/service/Container.h>
#include <comppi/service/database/Database.h>
#include <comppi/utility/Cache.h>

namespace comppi {

namespace entity {
    class SystemType;
} // namespace entity

namespace service {
namespace systemtype {

class SystemType {
public:
    typedef std::shared_ptr<SystemType> SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container);
    };

    SystemType(
        const std::string& systemPath,
        const std::string& synonymPath,
        database::DatabasePtr databasePtr
    );

    bool loadDatabase();

    entity::SystemType getSystemType(const std::string& name);

private:
    bool loadSynonyms();

    const std::string _systemPath;
    const std::string _synonymPath;
    database::DatabasePtr _databasePtr;
    std::map<std::string, std::string> _synonyms;
    utility::Cache<std::string, entity::SystemType, 3> _cache;
};

} // namespace systemtype
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_SYSTEMTYPE_SYSTEMTYPE_H_
