#ifndef COMPPI_CONTROLLER_GEXF_H_
#define COMPPI_CONTROLLER_GEXF_H_

#include <comppi/service/Container.h>

namespace comppi {
namespace controller {

class Gexf {
public:
    Gexf(service::Container& container);
    int generate();

private:
    service::Container& _container;
};

} // namespace controller
} // namespace comppi

#endif // GEXF_H_
