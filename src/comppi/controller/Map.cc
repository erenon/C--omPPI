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
    :Builder(container, "map")
{}

int Map::build(const service::config::Config& config) {
    int invalidConfig = checkConfig(config);
    if (invalidConfig) { return invalidConfig; }

    auto driverOptions = config.subtree("driverOptions");
    invalidConfig = enrichDriverOptions(config, driverOptions);
    if (invalidConfig) { return invalidConfig; }

    std::string driverName = config.get("driver");
    std::string filePath = _sourcePath + config.get("file");

    std::fstream input(filePath, std::fstream::in);

    if (!input) {
        ERROR << "Failed to open source file: '" << filePath << "'";
        return 1;
    }

    INFO << "Build map source: '" << filePath << "'";

    if (driverName == "Biogrid") {
        using service::driver::map::Biogrid;

        try {
            Biogrid driver(input, driverOptions);

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
