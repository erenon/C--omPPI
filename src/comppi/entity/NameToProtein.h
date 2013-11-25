#ifndef COMPPI_ENTITY_NAMETOPROTEIN_H_
#define COMPPI_ENTITY_NAMETOPROTEIN_H_

#include <string>
#include <memory>

#include <odb/core.hxx>

namespace comppi {
namespace entity {

class Protein;

#pragma db value(std::string) type("VARCHAR(255)")

#pragma db object
class NameToProtein {
    #pragma db index("search_idx") members(_name, _namingConvention, _specieId)
    #pragma db index("synonym_idx") members(_protein)
public:
    NameToProtein(
        int specieId,
        const std::string& name,
        const std::string& namingConvention,
        const std::shared_ptr<Protein>& protein
    )
        :_id(0),
         _specieId(specieId),
         _name(name),
         _namingConvention(namingConvention),
         _protein(protein)
    {}

private:
    friend class odb::access;

    #pragma db id auto
    unsigned _id;
    int _specieId;
    std::string _name;
    std::string _namingConvention;
    #pragma db column("proteinId")
    std::shared_ptr<Protein> _protein;
};

} // namespace entity
} // namespace comppi

#ifdef ODB_COMPILER
    #include <comppi/entity/Protein.h>
#endif

#endif // COMPPI_ENTITY_NAMETOPROTEIN_H_
