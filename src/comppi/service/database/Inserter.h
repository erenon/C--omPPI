#ifndef COMPPI_SERVICE_DATABASE_INSERTER_H_
#define COMPPI_SERVICE_DATABASE_INSERTER_H_

#include <memory>

#include <comppi/service/database/Database.h>
#include <comppi/service/Container.h>

namespace comppi {
namespace service {
namespace database {

template <typename Driver>
class Inserter {
public:
	typedef std::shared_ptr<Inserter> SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container) {
            auto databasePtr = container.get<database::Database>();

        	return std::make_shared<Inserter>(databasePtr);
        }
    };

    Inserter(DatabasePtr databasePtr)
    	:_databasePtr(databasePtr)
    {}

    // TODO use producer/consumer queue
    void insert(Driver& container) {
    	Transaction transaction(_databasePtr->begin());

    	for (auto item : container) {
			_databasePtr->persist(item);
    	}

    	transaction.commit();
    }

private:
    DatabasePtr _databasePtr;
};

} // namespace database
} // namespace service
} // namespace comppi

#endif /* COMPPI_SERVICE_DATABASE_INSERTER_H_ */
