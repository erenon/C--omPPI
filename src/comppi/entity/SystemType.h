#ifndef COMPPI_ENTITY_SYSTEMTYPE_H_
#define COMPPI_ENTITY_SYSTEMTYPE_H_

#include <string>
#include <stdexcept>
#include <memory>
#include <vector>

#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>

namespace comppi {
namespace entity {

class Interaction;

#pragma db object
class SystemType {
public:
    enum ConfidenceType {
        UNKNOWN = 0,
        PREDICTED = 1,
        EXPERIMENTAL = 2,
        GENETIC = 3
    };

    SystemType(const std::string& name, ConfidenceType confidenceType)
        :_id(0),
         _name(name),
         _confidenceType(confidenceType)
    {}

    SystemType(const std::string& name, int confidenceType)
        :_id(0),
         _name(name)
    {
        switch(confidenceType) {
        case UNKNOWN:
            _confidenceType = UNKNOWN;
            break;
        case PREDICTED:
            _confidenceType = PREDICTED;
            break;
        case EXPERIMENTAL:
            _confidenceType = EXPERIMENTAL;
            break;
        case GENETIC:
            _confidenceType = GENETIC;
            break;
        default:
            throw std::invalid_argument("SystemType: Invalid confidence type");
            break;
        }
    }

    // GETTERS

    ConfidenceType getConfidenceType() const {
        return ConfidenceType(_confidenceType);
    }

    unsigned getId() const {
        return _id;
    }

    std::string getName() const {
        return _name;
    }

    // SETTERS

    void setName(std::string name) {
        _name = name;
    }

    void setConfidenceType(ConfidenceType confidenceType) {
        _confidenceType = confidenceType;
    }

private:
    friend class odb::access;

    SystemType() {}

    #pragma db id auto
    unsigned _id;
    std::string _name;
    int _confidenceType;

    #pragma db value_not_null inverse(_systemTypes)
    std::vector<odb::lazy_weak_ptr<Interaction>> _interactions;
};

} // namespace entity
} // namespace comppi

#ifdef ODB_COMPILER
    #include <comppi/entity/Interaction.h>
#endif

#endif  // COMPPI_ENTITY_SYSTEMTYPE_H_
