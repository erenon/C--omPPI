#include <algorithm>
#include <cstring>

#include <comppi/service/driver/map/__NAME__.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

__NAME__::__NAME__(std::fstream& input, config::Config config)
    :_tokenizer(input, {{-1,-2,-3}}, '\t') /*TODO*/
{
    _speciesId = config.get<int>("speciesId");
}

__NAME__::iterator __NAME__::begin() {
    return iterator(_tokenizer.begin(), _tokenizer.end(), _speciesId);
}

__NAME__::iterator __NAME__::end() {
    return iterator(_tokenizer.end());
}

__NAME__::iterator::iterator(const TokenIterator it, const TokenIterator end, int speciesId)
    :_it(it),
     _end(end),
     _speciesId(speciesId)
{}

__NAME__::iterator::iterator(const TokenIterator end)
    :_it(end),
     _end(end)
{}

__NAME__::iterator& __NAME__::iterator::operator++() {
    ++_it;
    return *this;
}

entity::ProteinNameMap __NAME__::iterator::operator*() {
    /* TODO */
}

bool __NAME__::iterator::operator==(const iterator& rhs) const {
    return _it == rhs._it;
}

bool __NAME__::iterator::operator!=(const iterator& rhs) const {
    return _it != rhs._it;
}

} // namespace map
} // namespace driver
} // namespace service
} // namespace comppi
