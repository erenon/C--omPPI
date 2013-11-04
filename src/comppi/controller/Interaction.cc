#include <stdexcept>

#include <comppi/controller/Interaction.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>
#include <comppi/service/species/Species.h>
#include <comppi/service/database/Inserter.h>
#include <comppi/service/driver/interaction/MultimapAdapter.H>

#include <comppi/entity/gen/Interaction-odb.hxx>

#include <comppi/service/driver/interaction/Biogrid.h>

namespace comppi {
namespace controller {

Interaction::Interaction(service::Container& container)
    :_container(container)
{
    auto configPtr = container.get<service::config::Config>();

    _interactionPath =
        configPtr->get("driver.sourcePath") +
        configPtr->get("driver.interactionDir");

    _interactionSources.loadFile(_interactionPath + "interactions.json");
}

int Interaction::build(std::vector<std::string> inputs) {
    int status = 0;

    if (inputs.empty()) {
        INFO << "Build all interaction sources";

        for (auto sourceConfig : _interactionSources) {
            status |= build(sourceConfig);
        }
    } else {
        for (auto source : inputs) {
            try {
                auto sourceConfig = _interactionSources.subtree(source);
                status |= build(sourceConfig);

            } catch (const std::invalid_argument&) {
                ERROR << "Source not found: '" << source << "'";
                status = 1;
            }
        }
    }

    return status;
}

int Interaction::build(const Config& interactionConfig) {
    std::string driverName;
    std::string filePath = _interactionPath; // + config value
    auto driverConfig = interactionConfig.subtree("driverOptions");

    try {
        driverName = interactionConfig.get("driver");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'driver' key.";
    }

    try {
        auto speciesPtr = _container.get<service::species::Species>();

        driverConfig.set(
            "speciesId",
            speciesPtr->getByAbbr(interactionConfig.get("speciesAbbr")).id
        );
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'speciesAbbr' key.";
    } catch (const std::out_of_range&) {
        ERROR << "Invalid source configuration, invalid 'speciesAbbr' key.";
    }

    try {
        filePath += interactionConfig.get("file");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'file' key.";
    }

    std::fstream input(filePath, std::fstream::in);

    if (!input) {
        ERROR << "Failed to open source file: '" << filePath << "'";
        return 1;
    }

    INFO << "Build interaction source: '" << filePath << "'";

    using service::driver::interaction::MultimapAdapter;

    if (driverName == "Biogrid") {
        using service::driver::interaction::Biogrid;

        try {
            Biogrid driver(input, driverConfig);
            MultimapAdapter<Biogrid> multimap(_container, driver);

            auto inserterPtr = _container.get<service::database::Inserter<
                MultimapAdapter<Biogrid>>>();
            inserterPtr->insert(multimap);
        } catch (const std::invalid_argument&) {
            ERROR << "Invalid driver configuration";
        }

    } else {
        ERROR << "Invalid driver name in source config: '" << driverName << "'";
        return 1;
    }

    return 0;
}

} // namespace controller
} // namespace comppi
