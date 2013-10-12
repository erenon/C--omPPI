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

TEST_F(ConfigTest, Set) {
    _config.set("foo.bar", 123);
    ASSERT_EQ(123, _config.get<int>("foo.bar"));
}

TEST_F(ConfigTest, Subtree) {
    _config.loadFile(configPath() + "testconfig.json");
    Config sub(_config.subtree("driver.species"));
}

TEST_F(ConfigTest, Transformation) {
    _config.loadFile(configPath() + "testconfig.json");
    ASSERT_EQ("${comppi_root}/sources/", _config.get("driver.sourcePath"));
    _config.setTransformation("comppi_root", "/home/comppi");
    ASSERT_EQ("/home/comppi/sources/", _config.get("driver.sourcePath"));
}

TEST_F(ConfigTest, Iterator) {
    _config.loadFile(configPath() + "testconfig.json");
    Config sub(_config.subtree("array"));

    std::string values[3] = {"first", "second", "third"};

    int i = 0;
    for (auto it : sub) {
        EXPECT_EQ(values[i++], it.get(""));
    }
}


} // namespace config
} // namespace service
} // namespace comppi
