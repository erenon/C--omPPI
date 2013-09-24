#ifndef COMPPI_SERVICE_DATABASE_DATABASE_H_
#define COMPPI_SERVICE_DATABASE_DATABASE_H_

#include <memory>

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

namespace comppi {
namespace service {
namespace database {

typedef typename std::shared_ptr<odb::mysql::database> DatabasePtr;
typedef typename odb::core::transaction Transaction;

DatabasePtr createDatabase() {
    return std::make_shared<odb::mysql::database>(
        "odb_test", // user
        "odb_test_pw",
        "odb_test", // db
        (const char*)0, // host
        0, // port
        (const char*)0, // socket
        "utf8"
    );
}

} // namespace database
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_DATABASE_DATABASE_H_
