#ifndef COMPPI_SERVICE_SYSTEMTYPE_SYSTEMTYPE_H_
#define COMPPI_SERVICE_SYSTEMTYPE_SYSTEMTYPE_H_

#include <memory>
#include <string>

#include <comppi/service/Container.h>
#include <comppi/service/database/Database.h>

namespace comppi {
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

private:
    const std::string _systemPath;
    const std::string _synonymPath;
    database::DatabasePtr _databasePtr;
};

} // namespace systemtype
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_SYSTEMTYPE_SYSTEMTYPE_H_
