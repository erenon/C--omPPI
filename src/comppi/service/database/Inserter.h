#ifndef COMPPI_SERVICE_DATABASE_INSERTER_H_
#define COMPPI_SERVICE_DATABASE_INSERTER_H_

#include <memory>
#include <atomic>
#include <vector>
#include <thread>
#include <type_traits>

#include <comppi/service/database/Database.h>
#include <comppi/service/Container.h>
#include <comppi/service/log/Log.h>

#include <comppi/utility/Queue.h>

namespace comppi {
namespace service {
namespace database {

template <typename Driver>
class Inserter {
private:
    //decltype(std::declval<Callee>().func())
//    typedef typename std::result_of<decltype(&Driver::iterator::operator*)()>::type Entity;
    typedef decltype(std::declval<typename Driver::iterator>().operator*()) Entity;
    typedef std::vector<Entity> BufferItem;
    typedef std::shared_ptr<BufferItem> BufferItemPtr;

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

    void insert(Driver& container) {

        const int bufferItemSize = 512;

        auto itemPtr = std::make_shared<BufferItem>();
        itemPtr->reserve(bufferItemSize);

        _isRunning = true;

        std::thread consumerThread(&Inserter::consumer, std::ref(*this));

        int i = 0;
    	for (auto entity : container) {
    	    itemPtr->push_back(entity);
    	    ++i;

    	    if (i % bufferItemSize == 0) {
    	        _buffer.push(itemPtr);
    	        itemPtr = std::make_shared<BufferItem>();
    	        itemPtr->reserve(bufferItemSize);
    	    }
    	}

    	_buffer.push(itemPtr);
    	itemPtr = std::make_shared<BufferItem>();

    	// let the consumer exit
    	_isRunning = false;
    	_buffer.push(itemPtr);
    	consumerThread.join();
    }

private:
    void consumer() {
        Transaction transaction(_databasePtr->begin());

        while (_isRunning || !_buffer.empty()) {
            auto itemPtr = _buffer.pop();
            auto& batch = *itemPtr;

            for (auto entity : batch) {
                _databasePtr->persist(entity);
            }

            transaction.commit();
            transaction.reset(_databasePtr->begin());

            DEBUG << batch.size() << " records loaded";
        }

        transaction.commit();

        DEBUG << "Inserter consumer done.";
    }

    std::atomic<bool> _isRunning;
    utility::Queue<BufferItemPtr> _buffer;
    DatabasePtr _databasePtr;
};

} // namespace database
} // namespace service
} // namespace comppi

#endif /* COMPPI_SERVICE_DATABASE_INSERTER_H_ */
