#ifndef COMPPI_ENTITY__PROTEINNAMEMAP_H_
#define COMPPI_ENTITY__PROTEINNAMEMAP_H_

#include <string>

#include <odb/core.hxx>

#include <comppi/entity/Species.h>

namespace comppi {
namespace entity {

#pragma db object
class ProteinNameMap {
public:
    ProteinNameMap(
        const Species& species,
        const std::string& namingConventionA,
        const std::string& proteinNameA,
        const std::string& namingConventionB,
        const std::string& proteinNameB
    )
       :_specieId(species.id),
        _namingConventionA(namingConventionA),
        _proteinNameA(proteinNameA),
        _namingConventionB(namingConventionB),
        _proteinNameB(proteinNameB)
    {}

private:
    friend class odb::access;

    ProteinNameMap() {}

    #pragma db id auto
    unsigned _id;
    int _specieId;
    std::string _namingConventionA;
    std::string _proteinNameA;
    std::string _namingConventionB;
    std::string _proteinNameB;
};

} // namespace entity
} // namespace comppi

#endif  // COMPPI_ENTITY__PROTEINNAMEMAP_H_
