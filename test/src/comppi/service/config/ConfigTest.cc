#include <string>
#include <cstdlib> // getenv
#include <stdexcept>

#include <gtest/gtest.h>

#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace config {

class ConfigTest : public testing::Test {
protected:
    Config _config;

    std::string configPath() const {
        const char* pTestdataPath(getenv("TESTDATA_PATH"));
        std::string configPath;

        if (pTestdataPath != NULL) {
            (configPath += pTestdataPath) += "/";
        }

        return configPath + "config/";
    }
};

TEST_F(ConfigTest, LoadFile) {
    _config.loadFile(configPath() + "testconfig.json");
}

TEST_F(ConfigTest, LoadNonexistentFile) {
    ASSERT_FALSE(
        _config.loadFile(configPath() + "nonexistent.json")
    );
}

TEST_F(ConfigTest, Get) {
    _config.loadFile(configPath() + "testconfig.json");

    ASSERT_EQ(42u, _config.get<unsigned>("answer"));
    ASSERT_EQ(std::string("foobar"), _config.get("name"));
}

TEST_F(ConfigTest, GetNonexistent) {
    _config.loadFile(configPath() + "testconfig.json");

    EXPECT_THROW(
        _config.get<unsigned>("nonexistent"),
        std::invalid_argument
    );
}

TEST_F(ConfigTest, Subtree) {
    _config.loadFile(configPath() + "testconfig.json");
    Config sub(_config.subtree("driver.species"));
}


} // namespace config
} // namespace service
} // namespace comppi
