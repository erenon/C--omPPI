#include <comppi/controller/Builder.h>

#include <comppi/service/species/Species.h>

namespace comppi {
namespace controller {

Builder::Builder(Container& container, const std::string& identity)
    :_container(container),
     _identity(identity)
{
    auto configPtr = container.get<service::config::Config>();

    _sourcePath =
        configPtr->get("driver.sourcePath") +
        configPtr->get("driver." + identity + "Dir");

    _sourceConfig.loadFile(_sourcePath + identity + "s.json");
}

int Builder::buildAll(const std::vector<std::string>& inputs) {
    int status = 0;

    if (inputs.empty()) {
        INFO << "Build all " + _identity + " sources";

        for (auto sourceConfig : _sourceConfig) {
            status |= build(sourceConfig);
        }
    } else {
        for (auto source : inputs) {
            try {
                auto sourceConfig = _sourceConfig.subtree(source);
                status |= build(sourceConfig);

            } catch (const std::invalid_argument&) {
                ERROR << "Source not found: '" << source << "'";
                status = 1;
            }
        }
    }

    return status;
}

int Builder::checkConfig(const Config& config) const {
    try {
        config.get("driver");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'driver' key.";
        return 1;
    }

    try {
        config.get("speciesAbbr");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'speciesAbbr' key.";
        return 2;
    }

    try {
        config.get("file");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'file' key.";
        return 4;
    }

    return 0;
}

int Builder::enrichDriverOptions(const Config& config, Config& options) const {
    try {
        auto speciesPtr = _container.get<service::species::Species>();

        options.set(
            "speciesId",
            speciesPtr->getByAbbr(config.get("speciesAbbr")).id
        );
    } catch (const std::out_of_range&) {
        ERROR << "Invalid source configuration, invalid 'speciesAbbr' key.";
        return 1;
    }

    return 0;
}

} // namespace controller
} // namespace comppi
