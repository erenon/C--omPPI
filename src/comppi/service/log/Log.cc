#include <comppi/service/log/Log.h>
#include <comppi/service/config/Config.h>

using comppi::service::config::Config;

void bootstrapLog(const Config& config) {
    std::string levelStr = config.get("level", std::string("info"));

    namespace blt = boost::log::trivial;

    auto level = blt::trace;
    if (levelStr == "debug") level = blt::debug;
    if (levelStr == "info") level = blt::info;
    if (levelStr == "warning") level = blt::warning;
    if (levelStr == "error") level = blt::error;
    if (levelStr == "fatal") level = blt::fatal;

    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= level
    );
}
