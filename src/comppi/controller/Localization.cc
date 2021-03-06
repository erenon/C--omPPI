#include <stdexcept>

#include <comppi/controller/Localization.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>
#include <comppi/service/database/Inserter.h>
#include <comppi/service/driver/SystemTypeAdapter.h>
#include <comppi/service/driver/localization/ProteinAdapter.h>

#include <comppi/entity/gen/Localization-odb.hxx>

#include <comppi/service/driver/localization/Organelle.h>

namespace comppi {
namespace controller {

Localization::Localization(service::Container& container)
    :Builder(container, "localization")
{}

int Localization::build(const Config& config) {
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
        return 5;
    }

    INFO << "Build localization source: '" << filePath << "'";

    using service::driver::SystemTypeAdapter;
    using service::driver::localization::ProteinAdapter;

    if (driverName == "Organelle") {
        using service::driver::localization::Organelle;

        try {
            Organelle driver(input, driverOptions, _container);
            SystemTypeAdapter<Organelle> stadapter(_container, driver);
            ProteinAdapter<SystemTypeAdapter<Organelle>> multimap(_container, stadapter);

            auto inserterPtr = _container.get<service::database::Inserter<
                ProteinAdapter<SystemTypeAdapter<Organelle>>
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
