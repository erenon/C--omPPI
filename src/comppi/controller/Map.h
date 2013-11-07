#ifndef COMPPI_CONTROLLER_MAP_H_
#define COMPPI_CONTROLLER_MAP_H_

#include <vector>
#include <string>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

#include <comppi/controller/Builder.h>

namespace comppi {
namespace controller {

using service::config::Config;

class Map : public Builder {
public:
    Map(service::Container& container);

private:
    int build(const Config& config);
};

} // namespace controller
} // namespace comppi

#endif  // COMPPI_CONTROLLER_MAP_H_
