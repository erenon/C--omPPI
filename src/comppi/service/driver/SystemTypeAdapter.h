#ifndef COMPPI_SERVICE_DRIVER_SYSTEMTYPEADAPTER_H_
#define COMPPI_SERVICE_DRIVER_SYSTEMTYPEADAPTER_H_

#include <comppi/service/Container.h>
#include <comppi/service/systemtype/SystemType.h>
#include <comppi/entity/SystemType.h>

namespace comppi {
namespace service {
namespace driver {

template <typename Driver>
class SystemTypeAdapter {
private:
    typedef typename Driver::iterator DriverIt;
    typedef decltype(std::declval<typename Driver::iterator>().operator*()) Entity;
public:
    SystemTypeAdapter(Container& container, Driver driver)
        :_sSystemType(container.get<systemtype::SystemType>()),
         _driver(driver)
    {}

    class iterator {
    public:
        iterator(systemtype::SystemType::SelfPtr sSystemType, DriverIt it, DriverIt end)
            :_sSystemType(sSystemType),
             _it(it),
             _end(end)
        {}

        iterator& operator++() {
            ++_it;
            return (*this);
        }

        Entity operator*() {
            Entity entity = *_it;
            auto systemTypeIts = entity.getSystemTypes();

            for(
                auto it = systemTypeIts.first;
                it != systemTypeIts.second;
                ++it
            ) {
                **it = _sSystemType->getSystemType((*it)->getName());
            }

            return entity;
        }

        bool operator==(const iterator& rhs) const {
            return _it == rhs._it;
        }

        bool operator!=(const iterator& rhs) const {
            return _it != rhs._it;
        }

        systemtype::SystemType::SelfPtr _sSystemType;
        DriverIt _it;
        DriverIt _end;
    };

    iterator begin() {
        return iterator(_sSystemType, _driver.begin(), _driver.end());
    }

    iterator end() {
        return iterator(_sSystemType, _driver.end(), _driver.end());
    }

private:
    systemtype::SystemType::SelfPtr _sSystemType;
    Driver _driver;
};

} // namespace driver
} // namespace service
} // namespace comppi

#endif // COMPPI_SERVICE_DRIVER_SYSTEMTYPEADAPTER_H_
