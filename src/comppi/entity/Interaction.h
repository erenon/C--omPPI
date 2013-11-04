#ifndef COMPPI_ENTITY_INTERACTION_H_
#define COMPPI_ENTITY_INTERACTION_H_

#include <string>
#include <memory>

#include <odb/core.hxx>

#include <comppi/entity/Protein.h>

namespace comppi {
namespace entity {

#pragma db object
class Interaction {
public:
    Interaction(
        const std::shared_ptr<Protein>& actorA,
        const std::shared_ptr<Protein>& actorB,
        const std::string& sourceDb,
        const int pubmedId
    )
        :_actorA(actorA),
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
};

} // namespace entity
} // namespace comppi

#endif // COMPPI_ENTITY_INTERACTION_H_
