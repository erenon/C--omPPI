#include <cstdlib> // getenv
#include <iostream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <comppi/service/config/Config.h>
#include <comppi/service/driver/map/Biogrid.h>

#include <comppi/utility/Tokenizer.h>

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
            expected.close();
        } else {
            std::fstream actual(expectedCsvFile.c_str(), std::fstream::out);

            write(map, actual);

            actual.close();
        }
    }

private:
    void compare(Map& map, std::fstream& expectedCsv) {
    	utility::Tokenizer<5> expected(expectedCsv, {{0,1,2,3,4}}, ';');
    	auto expectedIt = expected.begin();

        for (auto translation : map) {
        	EXPECT_EQ(boost::lexical_cast<int>(expectedIt[0]), translation.getSpeciesId());
        	EXPECT_EQ(expectedIt[1], translation.getNamingConventionA());
        	EXPECT_EQ(expectedIt[2], translation.getProteinNameA());
        	EXPECT_EQ(expectedIt[3], translation.getNamingConventionB());
        	EXPECT_EQ(expectedIt[4], translation.getProteinNameB());

        	++expectedIt;
        }
    }

    void write(Map& map, std::fstream& output) {
        for (auto translation : map) {
            output << translation.getSpeciesId() << ";"
            	   << translation.getNamingConventionA() << ";"
                   << translation.getProteinNameA() << ";"
                   << translation.getNamingConventionB() << ";"
                   << translation.getProteinNameB()
                   << std::endl;
        }
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
    config.set("speciesId", 0);

    std::fstream input((dataPath() + "biogrid/input").c_str(), std::ios::in);
    std::string outputPath = dataPath() + "biogrid/output";

    Biogrid driver(input, config);

    _tester.test(driver, outputPath);
}

} // namespace map
} // namespace driver
} // namespace service
} // namespace comppi
