#ifndef COMPPI_CONTROLLER_CHECKSOURCE_H_
#define COMPPI_CONTROLLER_CHECKSOURCE_H_

#include <comppi/service/Container.h>

namespace comppi {
namespace controller {

class CheckSource {
public:
    CheckSource(service::Container& container);
    int check(const char* executable);

private:
    service::Container& _container;
};

} // namespace controller
} // namespace comppi



#endif // COMPPI_CONTROLLER_CHECKSOURCE_H_
