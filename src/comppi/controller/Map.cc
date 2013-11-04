#include <stdexcept>
#include <fstream>

#include <comppi/controller/Map.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>
#include <comppi/service/database/Inserter.h>
#include <comppi/service/species/Species.h>

#include <comppi/entity/gen/ProteinNameMap-odb.hxx>

#include <comppi/service/driver/map/Biogrid.h>

namespace comppi {
namespace controller {

Map::Map(service::Container& container)
    :_container(container)
{
    auto configPtr = container.get<service::config::Config>();

    _mapPath =
        configPtr->get("driver.sourcePath") +
        configPtr->get("driver.mapDir");

    _mapSources.loadFile(_mapPath + "maps.json");
}

int Map::build(std::vector<std::string> inputs) {
    int status = 0;

    if (inputs.empty()) {
        INFO << "Build all map sources";

        for (auto sourceConfig : _mapSources) {
            status |= build(sourceConfig);
        }
    } else {
        for (auto source : inputs) {
            try {
                auto sourceConfig = _mapSources.subtree(source);
                status |= build(sourceConfig);

            } catch (const std::invalid_argument&) {
                ERROR << "Source not found: '" << source << "'";
                status = 1;
            }
        }
    }

    return status;
}

int Map::build(const service::config::Config& mapConfig) {
    std::string driverName;
    std::string filePath = _mapPath; // + config value
    auto driverConfig = mapConfig.subtree("driverOptions");

    try {
        driverName = mapConfig.get("driver");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'driver' key.";
    }

    try {
        auto speciesPtr = _container.get<service::species::Species>();

        driverConfig.set(
            "speciesId",
            speciesPtr->getByAbbr(mapConfig.get("speciesAbbr")).id
        );
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'speciesAbbr' key.";
    } catch (const std::out_of_range&) {
        ERROR << "Invalid source configuration, invalid 'speciesAbbr' key.";
    }

    try {
        filePath += mapConfig.get("file");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'file' key.";
    }

    std::fstream input(filePath, std::fstream::in);

    if (!input) {
        ERROR << "Failed to open source file: '" << filePath << "'";
        return 1;
    }

    INFO << "Build map source: '" << filePath << "'";

    if (driverName == "Biogrid") {
        using service::driver::map::Biogrid;

        try {
            Biogrid driver(input, driverConfig);

            auto inserterPtr = _container.get<service::database::Inserter<Biogrid>>();
            inserterPtr->insert(driver);
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
