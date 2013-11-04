#ifndef COMPPI_SERVICE_DRIVER_INTERACTION_BIOGRID_H_
#define COMPPI_SERVICE_DRIVER_INTERACTION_BIOGRID_H_

#include <comppi/utility/Tokenizer.h>

#include <comppi/entity/Interaction.h>

#include <comppi/service/protein/Protein.h>

namespace comppi {
namespace service {

namespace config {
    class Config;
} // namespace config

namespace driver {
namespace interaction {

class Biogrid {
private:
    typedef utility::Tokenizer<4> Tokenizer;
    typedef Tokenizer::iterator TokenIterator;
public:
    Biogrid(std::fstream& input, const config::Config& config);

    class iterator {
    public:
        iterator(const TokenIterator it, const TokenIterator end, int speciesId);
        iterator(const TokenIterator end);
        iterator& operator++();
        entity::Interaction operator*() const;
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

} // namespace interaction
} // namespace driver
} // namespace service
} // namespace comppi

#endif // COMPPI_SERVICE_DRIVER_INTERACTION_BIOGRID_H_
