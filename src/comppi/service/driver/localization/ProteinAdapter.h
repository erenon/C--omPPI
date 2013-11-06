#ifndef COMPPI_SERVICE_DRIVER_LOCALIZATION_PROTEINADAPTER_H_
#define COMPPI_SERVICE_DRIVER_LOCALIZATION_PROTEINADAPTER_H_

#include <deque>
#include <memory>

#include <comppi/service/Container.h>
#include <comppi/service/protein/Protein.h>
#include <comppi/entity/Localization.h>
#include <comppi/entity/Protein.h>

namespace comppi {
namespace service {
namespace driver {
namespace localization {

template <typename Driver>
class ProteinAdapter {
private:
    typedef typename Driver::iterator DriverIt;
public:
    ProteinAdapter(Container& container, Driver driver)
        :_sProtein(container.get<protein::Protein>()),
         _driver(driver)
    {}

    class iterator {
    public:
        iterator(protein::Protein::SelfPtr sProtein, DriverIt it, DriverIt end)
            :_sProtein(sProtein),
             _it(it),
             _end(end)
        {
            processItem();
        }

        iterator& operator++() {
            if (_buffer.empty()) {
                ++_it;
                processItem();
            }

            return (*this);
        }

        entity::Localization operator*() {
            auto front = _buffer.front();
            _buffer.pop_front();
            return front;
        }

        bool operator==(const iterator& rhs) const {
            return _it == rhs._it;
        }

        bool operator!=(const iterator& rhs) const {
            return _it != rhs._it;
        }

    private:
        void processItem() {
            entity::Localization localization = *_it;

            auto translateds = _sProtein->translate(*localization.getProtein());

            for (auto& translated : translateds) {
                entity::Localization tLocalization(localization);

                auto proteinPtr = std::make_shared<entity::Protein>(translated);
                tLocalization.setProtein(proteinPtr);

                _buffer.push_back(tLocalization);
            }
        }

        protein::Protein::SelfPtr _sProtein;
        DriverIt _it;
        DriverIt _end;
        std::deque<entity::Localization> _buffer;
    };

    iterator begin() {
        return iterator(_sProtein, _driver.begin(), _driver.end());
    }

    iterator end() {
        return iterator(_sProtein, _driver.end(), _driver.end());
    }

private:
    protein::Protein::SelfPtr _sProtein;
    Driver _driver;
};

} // namespace localization
} // namespace driver
} // namespace service
} // namespace comppi


#endif // COMPPI_SERVICE_DRIVER_LOCALIZATION_PROTEINADAPTER_H_
