#ifndef COMPPI_CONTROLLER_MAP_H_
#define COMPPI_CONTROLLER_MAP_H_

#include <vector>
#include <string>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

//#include <comppi/controller/BuildAbstract.h>

namespace comppi {
namespace controller {

using service::config::Config;

class Map /*:public BuildAbstract*/ {
public:
    Map(service::Container& container);
    int build(std::vector<std::string> inputs);

private:
    int build(const Config& mapConfig);

    service::Container& _container;
    std::string _mapPath;
    Config _mapSources;
};

} // namespace controller
} // namespace comppi

#endif  // COMPPI_CONTROLLER_MAP_H_
