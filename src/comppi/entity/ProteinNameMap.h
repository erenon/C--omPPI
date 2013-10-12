#ifndef COMPPI_ENTITY_PROTEINNAMEMAP_H_
#define COMPPI_ENTITY_PROTEINNAMEMAP_H_

#include <string>

#include <odb/core.hxx>

namespace comppi {
namespace entity {

#pragma db object
class ProteinNameMap {
public:
    ProteinNameMap() {}

    ProteinNameMap(
        const int speciesId,
        const std::string& namingConventionA,
        const std::string& proteinNameA,
        const std::string& namingConventionB,
        const std::string& proteinNameB
    )
       :_specieId(speciesId),
        _namingConventionA(namingConventionA),
        _proteinNameA(proteinNameA),
        _namingConventionB(namingConventionB),
        _proteinNameB(proteinNameB)
    {}

    int getSpeciesId() const {
        return _specieId;
    }

    std::string getNamingConventionA() const {
        return _namingConventionA;
    }

    std::string getProteinNameA() const {
        return _proteinNameA;
    }

    std::string getNamingConventionB() const {
        return _namingConventionB;
    }

    std::string getProteinNameB() const {
        return _proteinNameB;
    }

    void setSpeciesId(const int speciesId) {
        _specieId = speciesId;
    }

    void setNamingConventionA(const std::string& namingConventionA) {
        _namingConventionA = namingConventionA;
    }

    void setProteinNameA(const std::string& proteinNameA) {
        _proteinNameA = proteinNameA;
    }

    void setNamingConventionB(const std::string& namingConventionB) {
        _namingConventionB = namingConventionB;
    }

    void setProteinNameB(const std::string& proteinNameB) {
        _proteinNameB = proteinNameB;
    }

private:
    friend class odb::access;

    #pragma db id auto
    unsigned _id;
    int _specieId;
    std::string _namingConventionA;
    std::string _proteinNameA;
    std::string _namingConventionB;
    std::string _proteinNameB;
public:


};

} // namespace entity
} // namespace comppi

#endif  // COMPPI_ENTITY_PROTEINNAMEMAP_H_
