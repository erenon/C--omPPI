#include <cstdlib> // getenv
#include <iostream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include <comppi/service/config/Config.h>
#include <comppi/service/driver/map/Biogrid.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

template <typename Map>
class MapTest {
public:
    void test(Map& map, std::string expectedCsvFile) {
        std::fstream expected(expectedCsvFile.c_str(), std::fstream::in);

        if (expected) {
            compare(map, expected);
        } else {
            std::fstream actual(expectedCsvFile.c_str(), std::fstream::out);

            write(map, actual);
        }
    }

private:
    void compare(Map& map, std::fstream& expected) {
        // TODO implement diff here
    }

    void write(Map& map, std::fstream& output) {
        for (auto translation : map) {
            output << translation.getNamingConventionA() << ";"
                   << translation.getProteinNameA() << ";"
                   << translation.getNamingConventionB() << ";"
                   << translation.getProteinNameB()
                   << std::endl;
        }

        output.close();
    }
};

class BiogridTest : public testing::Test {
protected:
    MapTest<Biogrid> _tester;

    std::string dataPath() const {
        const char* pTestdataPath(getenv("TESTDATA_PATH"));
        std::string path;

        if (pTestdataPath != NULL) {
            (path += pTestdataPath) += "/";
        }

        path += "driver/map/";
        return path;
    }
};

TEST_F(BiogridTest, TestRead) {
    config::Config config{};

    std::fstream input((dataPath() + "biogrid/input").c_str(), std::ios::in);
    std::string outputPath = dataPath() + "biogrid/output";

    Biogrid driver(input, config);

    _tester.test(driver, outputPath);
}

} // namespace map
} // namespace driver
} // namespace service
} // namespace comppi
