#include <memory>
#include <cstdlib>

#include <comppi/service/driver/interaction/Biogrid.h>

#include <comppi/entity/Protein.h>
#include <comppi/entity/SystemType.h>

#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace driver {
namespace interaction {

Biogrid::Biogrid(std::fstream& input, const config::Config& config)
    :_tokenizer(input, {{1, 2, 12, 14}}, '\t'),
     _speciesId(config.get<int>("speciesId"))
{
    // skip header
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Biogrid::iterator::iterator(const TokenIterator it, const TokenIterator end, int speciesId)
    :_it(it),
     _end(end),
     _speciesId(speciesId)
{
    if (_it[2] == "genetic") {
        ++(*this);
    }
}

Biogrid::iterator::iterator(const TokenIterator end)
    :_it(end),
     _end(end)
{}

Biogrid::iterator& Biogrid::iterator::operator++() {
    for (++_it; _it != _end && _it[2] == "genetic"; ++_it)
        ;   // skip while non genetic record found

    return *this;
}

entity::Interaction Biogrid::iterator::operator*() const {
    auto interaction = entity::Interaction(
        std::make_shared<entity::Protein>(
            _speciesId,
            _it[0],
            "EntrezGene"
        ),
        std::make_shared<entity::Protein>(
            _speciesId,
            _it[1],
            "EntrezGene"
        ),
        "Biogrid",
        std::atoi(_it[3].c_str())
    );

    interaction.addSystemType(std::make_shared<entity::SystemType>(_it[2], 0));

    return interaction;
}

bool Biogrid::iterator::operator==(const iterator& rhs) const {
    return _it == rhs._it;
}

bool Biogrid::iterator::operator!=(const iterator& rhs) const {
    return _it != rhs._it;
}

Biogrid::iterator Biogrid::begin() {
    return iterator(_tokenizer.begin(), _tokenizer.end(), _speciesId);
}

Biogrid::iterator Biogrid::end() {
    return iterator(_tokenizer.end());
}

} // namespace interaction
} // namespace driver
} // namespace service
} // namespace comppi
