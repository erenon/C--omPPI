#ifndef COMPPI_SERVICE_DRIVER_MAP___FCAPS_NAME___H_
#define COMPPI_SERVICE_DRIVER_MAP___FCAPS_NAME___H_

#include <fstream>

#include <comppi/service/config/Config.h>
#include <comppi/entity/ProteinNameMap.h>
#include <comppi/utility/Tokenizer.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

class __NAME__ {
private:
    typedef utility::Tokenizer<__FIELD_COUNT__> Tokenizer;
    typedef Tokenizer::iterator TokenIterator;
public:
    __NAME__(std::fstream& input, config::Config config);

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

#endif  // COMPPI_SERVICE_DRIVER_MAP___FCAPS_NAME___H_
