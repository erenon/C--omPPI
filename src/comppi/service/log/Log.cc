#include <comppi/service/log/Log.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace log {

void bootstrapLog(const comppi::service::config::Config& config) {
    std::string levelStr = config.get("log.level", std::string("info"));

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

} // namespace log
} // namespace service
} // namespace comppi
