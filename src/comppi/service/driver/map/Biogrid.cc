#include <algorithm>
#include <cstring>

#include <comppi/service/driver/map/Biogrid.h>

namespace comppi {
namespace service {
namespace driver {
namespace map {

Biogrid::Biogrid(std::fstream& input, config::Config config)
    :_tokenizer(input, {{0, 1, 2}}, '\t')
{
    _speciesId = config.get<int>("speciesId");

    // skip header
    const char* firstColumnHeader = "BIOGRID_ID";
    std::string line;
    do {
        std::getline(input, line);
    } while (
        line.substr(0, strlen(firstColumnHeader)) != firstColumnHeader
    &&  input.eof() == false
    );
}

Biogrid::iterator Biogrid::begin() {
    return iterator(_tokenizer.begin(), _tokenizer.end(), _speciesId);
}

Biogrid::iterator Biogrid::end() {
    return iterator(_tokenizer.end());
}

Biogrid::iterator::iterator(const TokenIterator it, const TokenIterator end, int speciesId)
    :_it(it),
     _end(end),
     _speciesId(speciesId)
{
    ++(*this);
}

Biogrid::iterator::iterator(const TokenIterator end)
    :_it(end),
     _end(end)
{}

Biogrid::iterator& Biogrid::iterator::operator++() {
    while (_buffer.empty() && _it != _end) {

        int strongestOrder = -1;
        entity::ProteinNameMap strongestTranslation;

        for (std::string id = _it[0];
            id == _it[0] && _it != _end;
            ++_it
        ) {
            // get naming convention <id, normalizedName>
            Convention convention = getConvention(_it[2]);

            // if id < 0, continue
            if (convention.first < 0) {
                continue;
            }

            entity::ProteinNameMap translation;
            translation.setNamingConventionB(convention.second);
            translation.setProteinNameB(_it[1]);

            if (strongestOrder == -1) {
                strongestTranslation = translation;
                strongestOrder = convention.first;
            } else if (convention.first > strongestOrder) {
                // put prev strongest into buffer
                std::swap(strongestTranslation, translation);
                strongestOrder = convention.first;

                _buffer.push_back(translation);
            } else {
                _buffer.push_back(translation);
            }
        }

        //if (strongestOrder >= 0) {
        if (!_buffer.empty()) {
            for (auto& translation : _buffer) {
                translation.setNamingConventionA(
                    strongestTranslation.getNamingConventionB());

                translation.setProteinNameA(
                    strongestTranslation.getProteinNameB());

                translation.setSpeciesId(_speciesId);
            }

            _buffer.erase(std::remove_if(
                _buffer.begin(),
                _buffer.end(),
                [](const entity::ProteinNameMap& translation) {
                    return translation.getNamingConventionA()
                        == translation.getNamingConventionB();
                }
            ), _buffer.end());
        }
    }

    return *this;
}

entity::ProteinNameMap Biogrid::iterator::operator*() {
    auto front = _buffer.front();
    _buffer.pop_front();
    return front;
}

bool Biogrid::iterator::operator==(const iterator& rhs) const {
    return _it == rhs._it;
}

bool Biogrid::iterator::operator!=(const iterator& rhs) const {
    return _it != rhs._it;
}

Biogrid::iterator::Convention
Biogrid::iterator::getConvention(const std::string& originalName) const {
    if (originalName == "SWISSPROT") {
        return std::make_pair(3, std::string("UniProtKB-AC"));
    }
    if (originalName == "ENSEMBL") {
        return std::make_pair(2, std::string("EnsemblGeneId"));
    }
    if (originalName == "REFSEQ_PROTEIN_ACCESSION") {
        return std::make_pair(1, std::string("refseq"));
    }
    if (originalName == "WORMBASE") {
        return std::make_pair(0, std::string("WBGeneId"));
    }

    return std::make_pair(-1, std::string());
}

} // namespace map
} // namespace driver
} // namespace service
} // namespace comppi
