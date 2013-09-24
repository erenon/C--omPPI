#ifndef COMPPI_SERVICE_CONFIG_CONFIG_H_
#define COMPPI_SERVICE_CONFIG_CONFIG_H_

#include <string>
#include <stdexcept>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <comppi/service/log/Log.h>

namespace comppi {
namespace service {
namespace config {

class Config {
public:
    Config() {}
    bool loadFile(const std::string& fileName);

    template<typename Value = std::string, typename Key>
    Value get(Key key) const {
        try {
            return _data.get<Value>(key);
        } catch (const boost::property_tree::ptree_bad_path& ex) {
            DEBUG
                << "Config: value not found for key: "
                << key;

            throw std::invalid_argument(ex.what());
        }
    }

    template<typename Value, typename Key>
    Value get(Key key, Value defaultValue) const {
        try {
            return _data.get<Value>(key, defaultValue);
        } catch (const boost::property_tree::ptree_bad_path& ex) {
            DEBUG
                << "Config: value not found for key: "
                << key;

            throw std::invalid_argument(ex.what());
        }
    }

    Config subtree(const char* key) const;
    Config subtree(const std::string& key) const;

private:
    typedef boost::property_tree::ptree Data;

    Config(const Data& data);

    Data _data;
};

} // namespace config
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_CONFIG_CONFIG_H_
