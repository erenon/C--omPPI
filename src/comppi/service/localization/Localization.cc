#include <fstream>
#include <stack>

#include <comppi/service/localization/Localization.h>
#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>

namespace comppi {
namespace service {
namespace localization {

Localization::SelfPtr Localization::ServiceFactory::create(Container& container) {
    auto config = container.get<config::Config>();

    std::string loctreePath(config->get("loctree.loctree"));

    return std::make_shared<Localization>(loctreePath);
}

Localization::Localization(const std::string& loctreePath) {
    loadLoctree(loctreePath);
}

int Localization::getId(const std::string& goCode) const {
    auto finder(_localizations.find(goCode));

    if (finder != _localizations.end()) {
        return finder->second;
    } else {
        ERROR << "Localization not found in tree: '"
            << goCode << "'";

        return -1;
    }
}

void Localization::loadLoctree(const std::string& loctreePath) {
    INFO << "Load Loctree from: " << loctreePath;

    std::fstream input(loctreePath.c_str(), std::fstream::in);

    if (!input) {
        ERROR << "Failed to open Loctree file";
    }

    std::size_t previousLevel = 0;
    std::size_t id = 0;

    while (input) {
        std::string line;
        std::getline(input, line);

        if (line.empty()) { continue; }

        std::size_t level = line.find_first_not_of("*");
        std::string goCode = line.substr(
            line.find_last_of("(") + 1,
            line.find_last_of(")") - line.find_last_of("(") - 1
        );

        if (level > previousLevel) {
            if (previousLevel + 1 != level) {
                ERROR << "Malformed loctree identation near line: '"
                    << line << "'";
            }

            ++previousLevel;

            ++id;
        } else if (level == previousLevel) {
            id += 2;
        } else { // level < previousLevel
            id += previousLevel - level + 2;
            previousLevel = level;
        }

        TRACE << "GO code: '" << goCode << "' id: " << id;
        _localizations.insert(std::make_pair(goCode, id));
    }
}

} // namespace localization
} // namespace service
} // namespace comppi
