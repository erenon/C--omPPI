#ifndef COMPPI_SERVICE_CONFIG_CONFIG_H_
#define COMPPI_SERVICE_CONFIG_CONFIG_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <utility>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string/replace.hpp>

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
            return transform(_data.get<Value>(key));
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
            return transform(_data.get<Value>(key, defaultValue));
        } catch (const boost::property_tree::ptree_bad_path& ex) {
            DEBUG
                << "Config: value not found for key: "
                << key;

            throw std::invalid_argument(ex.what());
        }
    }

    template<typename Value>
    inline Value transform(const Value& value) const {
        return value;
    }

    Config subtree(const char* key) const;
    Config subtree(const std::string& key) const;

    void setTransformation(const std::string& from, const std::string& to);

private:
    typedef boost::property_tree::ptree Data;

    Config(const Data& data);

    Data _data;
    std::vector<std::pair<std::string, std::string>> _transformations;
};

template<>
inline std::string Config::transform<std::string>(const std::string& value) const {
    std::string transformed(value);
    for (const auto& tf : _transformations) {
        boost::algorithm::replace_all(transformed, tf.first, tf.second);
    }
    return transformed;
}

} // namespace config
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_CONFIG_CONFIG_H_
