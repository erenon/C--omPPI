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

namespace comppi {
namespace service {

namespace config {
    class Config;
} // namespace config

namespace log {

void bootstrapLog(const comppi::service::config::Config& config);

} // namespace log
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_LOG_LOG_H_
