#ifndef COMPPI_SERVICE_LOG_LOG_H_
#define COMPPI_SERVICE_LOG_LOG_H_

#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#define TRACE BOOST_LOG_TRIVIAL(trace)
#define DEBUG BOOST_LOG_TRIVIAL(debug)
#define INFO BOOST_LOG_TRIVIAL(info)
#define WARNING BOOST_LOG_TRIVIAL(warning)
#define ERROR BOOST_LOG_TRIVIAL(error)
#define FATAL BOOST_LOG_TRIVIAL(fatal)

#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace log {

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

} // namespace log
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_LOG_LOG_H_
