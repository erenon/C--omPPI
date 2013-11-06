#ifndef COMPPI_CONTROLLER_LOCALIZATION_H_
#define COMPPI_CONTROLLER_LOCALIZATION_H_

#include <vector>
#include <string>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace controller {

using service::config::Config;

class Localization {
public:
    Localization(service::Container& container);
    int build(std::vector<std::string> inputs);

private:
    int build(const Config& interactionConfig);

    service::Container& _container;
    std::string _localizationPath;
    Config _localizationSources;
};

} // namespace controller
} // namespace comppi



#endif // COMPPI_CONTROLLER_LOCALIZATION_H_
