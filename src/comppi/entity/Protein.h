#ifndef COMPPI_ENTITY_PROTEIN_H_
#define COMPPI_ENTITY_PROTEIN_H_

#include <string>

#include <odb/core.hxx>

namespace comppi {
namespace entity {

#pragma db value(std::string) type("VARCHAR(255)")

#pragma db object
class Protein {
    #pragma db index("search_idx") members(_proteinName, _proteinNamingConvention, _specieId)
    #pragma db index("species_idx") members(_specieId)
public:
    Protein(
        int specieId,
        std::string proteinName,
        std::string proteinNamingConvention
    )
        :_specieId(specieId),
         _proteinName(proteinName),
         _proteinNamingConvention(proteinNamingConvention)
    {}

    unsigned getId() const {
        return _id;
    }

    void setId(unsigned id) {
        _id = id;
    }

    int getSpecieId() const {
        return _specieId;
    }

    void setSpecieId(int specieId) {
        _specieId = specieId;
    }

    const std::string& getProteinName() const {
        return _proteinName;
    }

    void setProteinName(const std::string& proteinName) {
        _proteinName = proteinName;
    }

    const std::string& getProteinNamingConvention() const {
        return _proteinNamingConvention;
    }

    void setProteinNamingConvention(
        const std::string& proteinNamingConvention) {
        _proteinNamingConvention = proteinNamingConvention;
    }

private:
    friend class odb::access;

    Protein() {}

    #pragma db id auto
    unsigned _id;
    int _specieId;
    std::string _proteinName;
    std::string _proteinNamingConvention;
};

} // namespace entity
} // namespace comppi

#endif // COMPPI_ENTITY_PROTEIN_H_
