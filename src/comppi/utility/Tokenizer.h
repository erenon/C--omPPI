#ifndef COMPPI_UTILITY_TOKENIZER_H_
#define COMPPI_UTILITY_TOKENIZER_H_

#include <array>
#include <stdexcept>
#include <iostream>

#include <boost/tokenizer.hpp>

#include <comppi/service/log/Log.h>

namespace comppi {
namespace utility {

template<std::size_t FieldCount, std::size_t ReqFieldCount>
class Tokenizer {
    typedef std::array<std::size_t, ReqFieldCount> FieldIdxArray;
    typedef std::array<std::string, ReqFieldCount> FieldArray;
public:
    Tokenizer(std::istream& input, const FieldIdxArray& reqFieldIdxs, const char* delimiter = ",\n")
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
            if (_iterator != _tokenizer.end()) {
                tokenizeLine();
            }
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return _iterator == rhs._iterator;
        }

        bool operator!=(const iterator& rhs) const {
            return _iterator != rhs._iterator;
        }

        std::string operator[](std::size_t index) const {
            return _currentLine[index];
        }

    private:
        friend class Tokenizer<FieldCount, ReqFieldCount>;

        typedef boost::escaped_list_separator<char> TokenizerFunc;
        typedef std::istreambuf_iterator<char> StreamIterator;
        typedef boost::tokenizer<TokenizerFunc, StreamIterator> BTokenizer;

        iterator(std::istream& input, const FieldIdxArray& reqFieldIdxs, const char* delimiter)
            :_tokenizer(
                StreamIterator(input),
                StreamIterator(),
                TokenizerFunc("\\", delimiter, "\"")
             ),
             _iterator(_tokenizer.begin()),
             _reqFieldIdxs(reqFieldIdxs)
        {
            tokenizeLine();
        }

        iterator end() const {
            iterator end = *this;
            end._iterator = _tokenizer.end();
            return end;
        }

        void tokenizeLine() {
            std::size_t nextReqFieldIdx(0);
            std::size_t nextFieldIdxIdx(0);

            for (std::size_t i = 0; i < FieldCount; ++i, ++_iterator) {
                if (_iterator == _tokenizer.end()) {
                    ERROR << "Tokenizer: premature end of line " << _currentLine[0];
                    break;
                }

                if (nextFieldIdxIdx < ReqFieldCount && i == _reqFieldIdxs[nextFieldIdxIdx]) {
                    _currentLine[nextReqFieldIdx++] = *_iterator;
                    ++nextFieldIdxIdx;
                }
            }
        }

        BTokenizer _tokenizer;
        BTokenizer::iterator _iterator;
        const FieldIdxArray _reqFieldIdxs;
        FieldArray _currentLine;
    };

    iterator begin() const {
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
