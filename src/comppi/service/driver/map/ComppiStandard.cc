#include <algorithm>
#include <cstring>

#include <comppi/service/driver/map/ComppiStandard.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

ComppiStandard::ComppiStandard(std::fstream& input, config::Config config)
    :_tokenizer(input, {{0, 1}}, '\t')
{
    _speciesId = config.get<int>("speciesId");
}

ComppiStandard::iterator ComppiStandard::begin() {
    return iterator(_tokenizer.begin(), _tokenizer.end(), _speciesId);
}

ComppiStandard::iterator ComppiStandard::end() {
    return iterator(_tokenizer.end());
}

ComppiStandard::iterator::iterator(const TokenIterator it, const TokenIterator end, int speciesId)
    :_it(it),
     _end(end),
     _speciesId(speciesId)
{
    _conventionA = _it[0];
    _conventionB = _it[1];
    ++(*this);
}

ComppiStandard::iterator::iterator(const TokenIterator end)
    :_it(end),
     _end(end)
{}

ComppiStandard::iterator& ComppiStandard::iterator::operator++() {
    ++_it;
    return *this;
}

entity::ProteinNameMap ComppiStandard::iterator::operator*() {
   return entity::ProteinNameMap(
       _speciesId, _conventionA, _it[0], _conventionB, _it[1]
   );
}

bool ComppiStandard::iterator::operator==(const iterator& rhs) const {
    return _it == rhs._it;
}

bool ComppiStandard::iterator::operator!=(const iterator& rhs) const {
    return _it != rhs._it;
}

} // namespace map
} // namespace driver
} // namespace service
} // namespace comppi
