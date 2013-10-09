#ifndef COMPPI_ENTITY_SPECIES_H_
#define COMPPI_ENTITY_SPECIES_H_

#include <string>

namespace comppi {
namespace entity {

struct Species {
    Species(int id_, const std::string& abbr_, const std::string& name_)
        :id(id_),
         abbr(abbr_),
         name(name_)
    {}

    const int id;
    const std::string abbr;
    const std::string name;
};

} // namespace entity
} // namespace comppi

#endif  // COMPPI_ENTITY_SPECIES_H_
