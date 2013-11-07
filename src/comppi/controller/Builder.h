#ifndef COMPPI_CONTROLLER_BUILDER_H_
#define COMPPI_CONTROLLER_BUILDER_H_

#include <vector>
#include <string>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace controller {

using service::Container;
using service::config::Config;

class Builder {
public:
    Builder(Container& container, const std::string& identity);
    virtual ~Builder() {}
    int buildAll(const std::vector<std::string>& inputs);

protected:
    int checkConfig(const Config& config) const;
    int enrichDriverOptions(const Config& config, Config& options) const;

    virtual int build(const Config& config) = 0;

    Container& _container;
    std::string _identity;
    std::string _sourcePath;
    Config _sourceConfig;
};

} // namespace controller
} // namespace comppi

#endif // COMPPI_CONTROLLER_BUILDER_H_
