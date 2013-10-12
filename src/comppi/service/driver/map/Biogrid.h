#ifndef COMPPI_SERVICE_DRIVER_MAP_BIOGRID_H_
#define COMPPI_SERVICE_DRIVER_MAP_BIOGRID_H_

#include <fstream>
#include <deque>
#include <utility>

#include <comppi/service/config/Config.h>
#include <comppi/entity/ProteinNameMap.h>
#include <comppi/utility/Tokenizer.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

class Biogrid {
private:
    typedef utility::Tokenizer<3> Tokenizer;
    typedef Tokenizer::iterator TokenIterator;
public:
    Biogrid(std::fstream& input, config::Config config);

    class iterator {
    public:
        iterator(const TokenIterator it, const TokenIterator end, int speciesId);
        iterator(const TokenIterator end);
        iterator& operator++();
        entity::ProteinNameMap operator*();
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
    private:
        typedef std::pair<int, std::string> Convention;

        Convention getConvention(const std::string& originalName) const;

        TokenIterator _it;
        TokenIterator _end;
        int _speciesId;
        std::deque<entity::ProteinNameMap> _buffer;
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

#endif  // COMPPI_SERVICE_DRIVER_MAP_BIOGRID_H_
