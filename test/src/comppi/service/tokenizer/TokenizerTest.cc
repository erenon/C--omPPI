#include <cstdlib> // getenv
#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include <comppi/utility/Tokenizer.h>

namespace comppi {
namespace utility {

class TokenizerTest : public testing::Test {
protected:
    std::string csvPath() const {
        return dataPath() += "tokenizer/testcsv.csv";
    }

    std::string tsvPath() const {
        return dataPath() += "tokenizer/testtsv.tsv";
    }

private:
    std::string dataPath() const {
        const char* pTestdataPath(getenv("TESTDATA_PATH"));
        std::string path;

        if (pTestdataPath != NULL) {
            (path += pTestdataPath) += "/";
        }

        return path;
    }
};

TEST_F(TokenizerTest, Tokenize) {
    std::fstream csv(csvPath().c_str(), std::fstream::in);
    Tokenizer<3> t(csv, {{0,1,4}});

    auto it = t.begin();

    ASSERT_EQ("11", it[0]);
    ASSERT_EQ("12", it[1]);
    ASSERT_EQ("15", it[2]);

    ++it;
    ++it;
    ++it;

    ASSERT_EQ("foo", it[0]);
    ASSERT_EQ("barbaz", it[1]);

    csv.close();
}

TEST_F(TokenizerTest, TokenizeTabular) {
    std::fstream tsv(tsvPath().c_str(), std::fstream::in);
    Tokenizer<3> t(tsv, {{0,1,4}}, '\t');

    auto it = t.begin();

    ASSERT_EQ("11", it[0]);
    ASSERT_EQ("12", it[1]);
    ASSERT_EQ("15", it[2]);

    ++it;
    ++it;
    ++it;

    ASSERT_EQ("foo", it[0]);
    ASSERT_EQ("barbaz", it[1]);

    tsv.close();
}

TEST_F(TokenizerTest, InvalidFieldSpec) {
    std::fstream csv(csvPath().c_str(), std::fstream::in);

    typedef Tokenizer<3> T;
    ASSERT_THROW(
        T(csv, {{1,1,4}}),
        std::invalid_argument
    );

    csv.close();
}

TEST_F(TokenizerTest, Iterate) {
    std::fstream csv(csvPath().c_str(), std::fstream::in);
    Tokenizer<1> t(csv, {{4}});

    for (const auto& line : t) {
        std::cout << line[0] << std::endl;
    }

    csv.close();
}

} // namespace utility
} // namespace comppi
