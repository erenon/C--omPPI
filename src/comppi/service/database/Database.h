#ifndef COMPPI_SERVICE_DATABASE_DATABASE_H_
#define COMPPI_SERVICE_DATABASE_DATABASE_H_

#include <memory>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

namespace comppi {
namespace service {

class Container;

namespace database {

typedef std::shared_ptr<odb::mysql::database> DatabasePtr;
typedef odb::core::transaction Transaction;

class Database {
public:
    typedef DatabasePtr SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container);
    };
};

} // namespace database
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_DATABASE_DATABASE_H_
