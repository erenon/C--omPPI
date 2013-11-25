#ifndef COMPPI_CONTROLLER_CHECKLOC_H_
#define COMPPI_CONTROLLER_CHECKLOC_H_

#include <comppi/service/Container.h>

namespace comppi {
namespace controller {

class CheckLoc {
public:
    CheckLoc(service::Container& container);
    int check();

private:
    service::Container& _container;
};

} // namespace controller
} // namespace comppi



#endif // COMPPI_CONTROLLER_CHECKLOC_H_
