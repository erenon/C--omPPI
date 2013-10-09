#include <string>
#include <cstdlib> // getenv
#include <stdexcept>

#include <gtest/gtest.h>

#include <comppi/service/species/Species.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace species {

class SpeciesTest : public testing::Test {
protected:
    config::Config config() const {
        const char* pTestdataPath(getenv("TESTDATA_PATH"));
        std::string configPath;

        if (pTestdataPath != NULL) {
            (configPath += pTestdataPath) += "/";
        }

        configPath += "species/testconfig.json";
        config::Config config;
        config.loadFile(configPath);
        return config.subtree("species");
    }
};

TEST_F(SpeciesTest, LoadFile) {
    Species s(config());
}

TEST_F(SpeciesTest, GetById) {
    Species s(config());

    auto descriptor = s.getById(0);
    ASSERT_EQ(std::string("hs"), descriptor.abbr);
}

TEST_F(SpeciesTest, GetByAbbr) {
    Species s(config());

    auto descriptor = s.getByAbbr("ce");
    ASSERT_EQ(2, descriptor.id);
}

TEST_F(SpeciesTest, GetByIdNonexistent) {
    Species s(config());

    EXPECT_THROW(
        s.getById(10),
        std::out_of_range
    );
}

TEST_F(SpeciesTest, GetByAbbrNonexistent) {
    Species s(config());

    EXPECT_THROW(
        s.getByAbbr("nonexistent"),
        std::out_of_range
    );
}

} // namespace species
} // namespace service
} // namespace comppi
