#ifndef COMPPI_ENTITY_SYSTEMTYPE_H_
#define COMPPI_ENTITY_SYSTEMTYPE_H_

#include <string>

#include <odb/core.hxx>

namespace comppi {
namespace entity {

#pragma db object
class SystemType {
public:
    enum ConfidenceType {
        UNKNOWN = 0,
        PREDICTED = 1,
        EXPERIMENTAL = 2
    };

    SystemType(const std::string& name, ConfidenceType confidenceType)
        :_name(name),
         _confidenceType(confidenceType)
    {}

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
};

} // namespace entity
} // namespace comppi

#endif  // COMPPI_ENTITY_SYSTEMTYPE_H_
