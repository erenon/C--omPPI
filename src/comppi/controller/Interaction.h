#ifndef COMPPI_CONTROLLER_INTERACTION_H_
#define COMPPI_CONTROLLER_INTERACTION_H_

#include <vector>
#include <string>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace controller {

using service::config::Config;

class Interaction {
public:
    Interaction(service::Container& container);
    int build(std::vector<std::string> inputs);

private:
    int build(const Config& interactionConfig);

    service::Container& _container;
    std::string _interactionPath;
    Config _interactionSources;
};

} // namespace controller
} // namespace comppi

#endif // INTERACTION_H_
