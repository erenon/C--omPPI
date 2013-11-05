#ifndef COMPPI_ENTITY_INTERACTION_H_
#define COMPPI_ENTITY_INTERACTION_H_

#include <string>
#include <memory>
#include <vector>

#include <odb/core.hxx>

#include <comppi/entity/Protein.h>

namespace comppi {
namespace entity {

class SystemType;

#pragma db object
class Interaction {
public:
    Interaction(
        const std::shared_ptr<Protein>& actorA,
        const std::shared_ptr<Protein>& actorB,
        const std::string& sourceDb,
        const int pubmedId
    )
        :_id(0),
         _actorA(actorA),
         _actorB(actorB),
         _sourceDb(sourceDb),
         _pubmedId(pubmedId)
    {}

    unsigned getId() const {
        return _id;
    }

    const std::shared_ptr<Protein>& getActorA() const {
        return _actorA;
    }

    void setActorA(const std::shared_ptr<Protein>& actorA) {
        _actorA = actorA;
    }

    const std::shared_ptr<Protein>& getActorB() const {
        return _actorB;
    }

    void setActorB(const std::shared_ptr<Protein>& actorB) {
        _actorB = actorB;
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

    void setPubmedId(const int pubmedId) {
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

    Interaction() {}

    #pragma db id auto
    unsigned _id;

    #pragma db column("actorAId")
    std::shared_ptr<Protein> _actorA;

    #pragma db column("actorBId")
    std::shared_ptr<Protein> _actorB;

    std::string _sourceDb;
    int _pubmedId;

    #pragma db value_not_null unordered \
        table("InteractionToSystemType") \
        id_column("interactionId") \
        value_column("systemTypeId")
    std::vector<std::shared_ptr<SystemType>> _systemTypes;
};

} // namespace entity
} // namespace comppi

#ifdef ODB_COMPILER
    #include <comppi/entity/SystemType.h>
#endif

#endif // COMPPI_ENTITY_INTERACTION_H_
