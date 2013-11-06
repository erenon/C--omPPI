#include <stdexcept>

#include <comppi/controller/Localization.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>
#include <comppi/service/species/Species.h>
#include <comppi/service/database/Inserter.h>
#include <comppi/service/driver/SystemTypeAdapter.H>
#include <comppi/service/driver/localization/ProteinAdapter.h>

#include <comppi/entity/gen/Localization-odb.hxx>

#include <comppi/service/driver/localization/Organelle.h>

namespace comppi {
namespace controller {

Localization::Localization(service::Container& container)
    :_container(container)
{
    auto configPtr = container.get<service::config::Config>();

    _localizationPath =
        configPtr->get("driver.sourcePath") +
        configPtr->get("driver.localizationDir");

    _localizationSources.loadFile(_localizationPath + "localizations.json");
}

int Localization::build(std::vector<std::string> inputs) {
    int status = 0;

    if (inputs.empty()) {
        INFO << "Build all localization sources";

        for (auto sourceConfig : _localizationSources) {
            status |= build(sourceConfig);
        }
    } else {
        for (auto source : inputs) {
            try {
                auto sourceConfig = _localizationSources.subtree(source);
                status |= build(sourceConfig);

            } catch (const std::invalid_argument&) {
                ERROR << "Source not found: '" << source << "'";
                status = 1;
            }
        }
    }

    return status;
}

int Localization::build(const Config& localizationConfig) {
    std::string driverName;
    std::string filePath = _localizationPath; // + config value
    auto driverConfig = localizationConfig.subtree("driverOptions");

    try {
        driverName = localizationConfig.get("driver");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'driver' key.";
    }

    try {
        auto speciesPtr = _container.get<service::species::Species>();

        driverConfig.set(
            "speciesId",
            speciesPtr->getByAbbr(localizationConfig.get("speciesAbbr")).id
        );
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'speciesAbbr' key.";
    } catch (const std::out_of_range&) {
        ERROR << "Invalid source configuration, invalid 'speciesAbbr' key.";
    }

    try {
        filePath += localizationConfig.get("file");
    } catch (const std::invalid_argument&) {
        ERROR << "Invalid source configuration, missing mandatory 'file' key.";
    }

    std::fstream input(filePath, std::fstream::in);

    if (!input) {
        ERROR << "Failed to open source file: '" << filePath << "'";
        return 1;
    }

    INFO << "Build localization source: '" << filePath << "'";

    using service::driver::SystemTypeAdapter;
    using service::driver::localization::ProteinAdapter;

    if (driverName == "Organelle") {
        using service::driver::localization::Organelle;

        try {
            Organelle driver(input, driverConfig, _container);
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
