#ifndef COMPPI_ENTITY_LOCALIZATION_H_
#define COMPPI_ENTITY_LOCALIZATION_H_

#include <string>
#include <memory>
#include <vector>

#include <odb/core.hxx>

#include <comppi/entity/Protein.h>

namespace comppi {
namespace entity {

class SystemType;

#pragma db value(std::string) type("VARCHAR(255)")

#pragma db object table("ProteinToLocalization")
class Localization {
    #pragma db index("search_idx") members(_protein)
    #pragma db index("single_loc_per_source") members(_protein, _localizationId, _sourceDb)
public:
    Localization(
        const std::shared_ptr<Protein>& protein,
        const int localizationId,
        const std::string& sourceDb,
        const int pubmedId
    )
        :_id(0),
         _protein(protein),
         _localizationId(localizationId),
         _sourceDb(sourceDb),
         _pubmedId(pubmedId)
    {}

    unsigned getId() const {
        return _id;
    }

    const std::shared_ptr<Protein>& getProtein() const {
        return _protein;
    }

    void setProtein(const std::shared_ptr<Protein>& protein) {
        _protein = protein;
    }

    int getLocalizationId() const {
        return _localizationId;
    }

    void setLocalizationId(int localizationId) {
        _localizationId = localizationId;
    }

    const std::string& getSourceDb() const {
        return _sourceDb;
    }

    void setSourceDb(const std::string& sourceDb) {
        _sourceDb = sourceDb;
    }

    int getPubmedId() const {
        return _pubmedId;
    }

    void setPubmedId(int pubmedId) {
        _pubmedId = pubmedId;
    }

    void addSystemType(const std::shared_ptr<SystemType>& systemType) {
        _systemTypes.push_back(systemType);
    }

    std::pair<
        std::vector<std::shared_ptr<SystemType>>::iterator,
        std::vector<std::shared_ptr<SystemType>>::iterator
    >
    getSystemTypes() {
        return std::make_pair(_systemTypes.begin(), _systemTypes.end());
    }

private:
    friend class odb::access;

    Localization() {}

    #pragma db id auto
    unsigned _id;

    #pragma db column("proteinId")
    std::shared_ptr<Protein> _protein;

    int _localizationId;
    std::string _sourceDb;
    int _pubmedId;

    #pragma db value_not_null unordered \
        table("ProtLocToSystemType") \
        id_column("protLocId") \
        value_column("systemTypeId")
    std::vector<std::shared_ptr<SystemType>> _systemTypes;
};

} // namespace entity
} // namespace comppi

#ifdef ODB_COMPILER
    #include <comppi/entity/SystemType.h>
#endif

#endif // COMPPI_ENTITY_LOCALIZATION_H_
