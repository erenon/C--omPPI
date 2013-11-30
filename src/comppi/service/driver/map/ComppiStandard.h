#ifndef COMPPI_SERVICE_DRIVER_MAP_COMPPISTANDARD_H_
#define COMPPI_SERVICE_DRIVER_MAP_COMPPISTANDARD_H_

#include <fstream>

#include <comppi/service/config/Config.h>
#include <comppi/entity/ProteinNameMap.h>
#include <comppi/utility/Tokenizer.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

class ComppiStandard {
private:
    typedef utility::Tokenizer<2> Tokenizer;
    typedef Tokenizer::iterator TokenIterator;
public:
    ComppiStandard(std::fstream& input, config::Config config);

    class iterator {
    public:
        iterator(const TokenIterator it, const TokenIterator end, int speciesId);
        iterator(const TokenIterator end);
        iterator& operator++();
        entity::ProteinNameMap operator*();
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
    private:
        TokenIterator _it;
        TokenIterator _end;
        int _speciesId;
        std::string _conventionA;
        std::string _conventionB;
    };

    iterator begin();
    iterator end();

private:
    Tokenizer _tokenizer;
    int _speciesId;
};

} // namespace map
} // namespace driver
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_DRIVER_MAP_COMPPISTANDARD_H_
