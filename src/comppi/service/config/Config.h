#ifndef COMPPI_SERVICE_CONFIG_CONFIG_H_
#define COMPPI_SERVICE_CONFIG_CONFIG_H_

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace comppi {
namespace service {
namespace config {

class Config {
public:
    Config() {}
    bool loadFile(const std::string& fileName);

    template<typename Value = std::string, typename Key>
    Value get(Key key) const {
        return _data.get<Value>(key);
    }

    template<typename Value, typename Key>
    Value get(Key key, Value defaultValue) const {
        return _data.get<Value>(key, defaultValue);
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
