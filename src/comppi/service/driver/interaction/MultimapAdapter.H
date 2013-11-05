#ifndef COMPPI_SERVICE_DRIVER_INTERACTION_MULTIMAPADAPTER_H_
#define COMPPI_SERVICE_DRIVER_INTERACTION_MULTIMAPADAPTER_H_

#include <deque>
#include <memory>

#include <comppi/service/protein/Protein.h>
#include <comppi/entity/Interaction.h>
#include <comppi/entity/Protein.h>

namespace comppi {
namespace service {

class Container;

namespace driver {
namespace interaction {

template <typename Driver>
class MultimapAdapter {
private:
    typedef typename Driver::iterator DriverIt;
public:
    MultimapAdapter(Container& container, Driver driver)
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

        entity::Interaction operator*() {
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
            entity::Interaction interaction = *_it;

            auto translatedAs = _sProtein->translate(*interaction.getActorA());
            auto translatedBs = _sProtein->translate(*interaction.getActorB());

            for (auto translatedA : translatedAs) {
                for (auto translatedB : translatedBs) {
                    entity::Interaction tInteraction(interaction);

                    auto actorA = std::make_shared<entity::Protein>(translatedA);
                    auto actorB = std::make_shared<entity::Protein>(translatedB);

                    if (actorB->getId() < actorA->getId()) {
                        actorA.swap(actorB);
                    }

                    tInteraction.setActorA(actorA);
                    tInteraction.setActorB(actorB);

                    _buffer.push_back(tInteraction);
                }
            }
        }

        protein::Protein::SelfPtr _sProtein;
        DriverIt _it;
        DriverIt _end;
        std::deque<entity::Interaction> _buffer;
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

} // namespace interaction
} // namespace driver
} // namespace service
} // namespace comppi

#endif // COMPPI_SERVICE_DRIVER_INTERACTION_MULTIMAPADAPTER_H_
