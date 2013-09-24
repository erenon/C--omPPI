#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace config {

bool Config::loadFile(const std::string& fileName) {
    try {
        boost::property_tree::read_json(fileName, _data);
    } catch(const boost::property_tree::json_parser_error& ex) {
        ERROR
            << "Failed to read json config file: "
            << ex.what();

        return false;
    }

    return true;
}

Config Config::subtree(const char* key) const {
    try {
        return Config(_data.get_child(key));
    } catch (const boost::property_tree::ptree_bad_path& ex) {
        DEBUG
            << "Config: subtree not found for key: "
            << key;

        return Config();
    }
}

Config Config::subtree(const std::string& key) const {
    return subtree(key.c_str());
}

Config::Config(const Data& data)
    :_data(data)
{}

} // namespace config
} // namespace service
} // namespace comppi
