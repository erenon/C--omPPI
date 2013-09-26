#ifndef COMPPI_UTILITY_TOKENIZER_H_
#define COMPPI_UTILITY_TOKENIZER_H_

#include <array>
#include <stdexcept>
#include <iostream>
#include <sstream>

//#include <boost/tokenizer.hpp>

#include <comppi/service/log/Log.h>

namespace comppi {
namespace utility {

template<std::size_t ReqFieldCount>
class Tokenizer {
    typedef std::array<std::size_t, ReqFieldCount> FieldIdxArray;
    typedef std::array<std::string, ReqFieldCount> FieldArray;
public:
    Tokenizer(std::istream& input, const FieldIdxArray& reqFieldIdxs, const char delimiter = ',')
        :_iterator(input, reqFieldIdxs, delimiter)
    {
        throwIfNotAscending(reqFieldIdxs);
    }

    class iterator {
    public:
        const FieldArray& operator*() const {
            return _currentLine;
        }

        iterator& operator++(int) {
            iterator ret(*this);
            ++*this;

            return ret;
        }

        iterator& operator++() {
            tokenizeLine();
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return _isEnd == rhs._isEnd;
        }

        bool operator!=(const iterator& rhs) const {
            return _isEnd != rhs._isEnd;
        }

        std::string operator[](std::size_t index) const {
            return _currentLine[index];
        }

    private:
        friend class Tokenizer<ReqFieldCount>;

        iterator(std::istream& input, const FieldIdxArray& reqFieldIdxs, const char delimiter)
            :_input(input),
             _reqFieldIdxs(reqFieldIdxs),
             _delimiter(delimiter),
             _isEnd(false)
        {}

        iterator end() const {
            iterator end = *this;
            end._isEnd = true;
            return end;
        }

        void tokenizeLine() {
            std::string line;
            std::getline(_input, line);

            if (_input) {
                if (line.empty()) {
                    return tokenizeLine();
                }
                std::stringstream lineStream(line);
                std::string field;

                std::size_t reqFieldIdx(0);
                std::size_t currentField(0);

                while (
                    std::getline(lineStream, field, _delimiter)
                &&  reqFieldIdx < ReqFieldCount
                ) {
                    if (currentField == _reqFieldIdxs[reqFieldIdx]) {
                        _currentLine[reqFieldIdx++] = field;
                    }
                    ++currentField;
                }

                if (reqFieldIdx != ReqFieldCount) {
                    ERROR << "Tokenizer: premature end of line";
                }
            } else {    // EOF
                _isEnd = true;
            }
        }

        std::istream& _input;
        const FieldIdxArray _reqFieldIdxs;
        const char _delimiter;
        bool _isEnd;
        FieldArray _currentLine;
    };

    iterator begin() {
        _iterator.tokenizeLine();
        return _iterator;
    }

    iterator end() const {
        return _iterator.end();
    }

private:
    iterator _iterator;

    void throwIfNotAscending(const FieldIdxArray& reqFieldIdxs) {
        auto it = reqFieldIdxs.begin();
        auto prevIndex = *it;
        ++it;

        for (; it != reqFieldIdxs.end(); ++it) {
            if (*it <= prevIndex) {
                throw std::invalid_argument(
                    "Tokenizer: required field indices must be in ascending order"
                );
            }

            prevIndex = *it;
        }
    }
};

} // namespace utility
} // namespace comppi

#endif  // COMPPI_UTILITY_TOKENIZER_H_
