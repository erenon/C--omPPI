#ifndef COMPPI_CONTROLLER_NAMELOOKUP_H_
#define COMPPI_CONTROLLER_NAMELOOKUP_H_

#include <comppi/service/Container.h>

namespace comppi {
namespace controller {

class Namelookup {
public:
    Namelookup(service::Container& container);
    int generate();

private:
    service::Container& _container;
};

} // namespace controller
} // namespace comppi

#endif // COMPPI_CONTROLLER_NAMELOOKUP_H_
