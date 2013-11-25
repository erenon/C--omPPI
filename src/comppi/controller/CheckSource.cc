#include <fstream>
#include <cstdlib>
#include <sstream>

#include <comppi/controller/CheckSource.h>

#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>

namespace comppi {
namespace controller {

CheckSource::CheckSource(service::Container& container)
    :_container(container)
{}

int CheckSource::check(const char* executable) {
    using service::config::Config;

    auto configPtr = _container.get<Config>();
    const std::string sourceTypes[3] = {"map", "interaction", "localization"};
    bool success = true;

    for (size_t sourceTypeIdx = 0; sourceTypeIdx < 3; ++sourceTypeIdx) {
        const std::string& type = sourceTypes[sourceTypeIdx];

        const std::string sourcePath =
            configPtr->get("driver.sourcePath") +
            configPtr->get("driver." + type + "Dir");

        Config sourceConfigs;
        bool confLoadSt = sourceConfigs.loadFile(sourcePath + type + "s.json");
        if (!confLoadSt) {
            success = false;
            continue;
        }

        for (auto sourceConfig : sourceConfigs) {
            std::string file;
            std::string driver;

            try {
                driver = sourceConfig.get("driver");
            } catch (const std::invalid_argument&) {
                ERROR << "Invalid source configuration, missing mandatory 'driver' key.";
                success = false;
                continue;
            }

            try {
                sourceConfig.get("speciesAbbr");
            } catch (const std::invalid_argument&) {
                ERROR << "Invalid source configuration, missing mandatory 'speciesAbbr' key.";
                success = false;
                continue;
            }

            try {
                file = sourceConfig.get("file");
            } catch (const std::invalid_argument&) {
                ERROR << "Invalid source configuration, missing mandatory 'file' key.";
                success = false;
                continue;
            }

            INFO << "Check " << file;
            {
                std::fstream sourceFile(sourcePath + file);
                if (!sourceFile) {
                    ERROR << "Failed to open file: '"
                          << sourcePath + file << "'";
                    success = false;
                    continue;
                }
            }

#ifdef __linux__
            INFO << "Check driver: " << driver;

            bool validDriverName = true;
            for (char c : driver) {
                if (! (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))) {
                    ERROR << "Invalid driver name: " << driver;
                    success = false;
                    validDriverName = false;
                    break;
                }
            }

            if (!validDriverName) {
                continue;
            }

            std::stringstream command;
            command << "nm -C " << executable
                << " | grep \"T comppi::service::driver::" << type << "::" << driver << "\" > /dev/null";
            int status = system(command.str().c_str());
            if (status) {
                ERROR << "No class found for driver: " << driver;
                success = false;
                continue;
            }
#endif // __linux__
        }
    }

    return success ? 0 : 1;
}

} // namespace controller
} // namespace comppi
