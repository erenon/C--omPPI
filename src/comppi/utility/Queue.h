#ifndef COMPPI_UTILITY_QUEUE_H_
#define COMPPI_UTILITY_QUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace comppi {
namespace utility {

/**
 * Original implementation:
 * http://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/
 */
template<typename T>
class Queue {
public:
	T pop() {
		std::unique_lock<std::mutex> mlock(_mutex);
		while (_queue.empty()) {
			_signal.wait(mlock);
		}
		auto item = _queue.front();
		_queue.pop();
		return item;
	}

	void pop(T& item) {
		std::unique_lock<std::mutex> mlock(_mutex);
		while (_queue.empty()) {
			_signal.wait(mlock);
		}
		item = _queue.front();
		_queue.pop();
	}

	void push(const T& item) {
		std::unique_lock<std::mutex> mlock(_mutex);
		_queue.push(item);
		mlock.unlock();
		_signal.notify_one();
	}

	inline bool empty() const {
	    return _queue.empty();
	}

private:
	std::queue<T> _queue;
	std::mutex _mutex;
	std::condition_variable _signal;
};

} // namespace utility
} // namespace comppi

#endif /* COMPPI_UTILITY_QUEUE_H_ */
