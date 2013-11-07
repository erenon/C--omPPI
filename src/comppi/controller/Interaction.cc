#include <stdexcept>

#include <comppi/controller/Interaction.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>
#include <comppi/service/species/Species.h>
#include <comppi/service/database/Inserter.h>
#include <comppi/service/driver/SystemTypeAdapter.h>
#include <comppi/service/driver/interaction/ProteinAdapter.h>

#include <comppi/entity/gen/Interaction-odb.hxx>

#include <comppi/service/driver/interaction/Biogrid.h>

namespace comppi {
namespace controller {

Interaction::Interaction(service::Container& container)
    :Builder(container, "interaction")
{}

int Interaction::build(const Config& config) {
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

    INFO << "Build interaction source: '" << filePath << "'";

    using service::driver::SystemTypeAdapter;
    using service::driver::interaction::ProteinAdapter;

    if (driverName == "Biogrid") {
        using service::driver::interaction::Biogrid;

        try {
            Biogrid driver(input, driverOptions);
            SystemTypeAdapter<Biogrid> stadapter(_container, driver);
            ProteinAdapter<SystemTypeAdapter<Biogrid>> multimap(_container, stadapter);

            auto inserterPtr = _container.get<service::database::Inserter<
                ProteinAdapter<SystemTypeAdapter<Biogrid>>
            >>();
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
