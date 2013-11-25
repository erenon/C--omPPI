#ifndef COMPPI_ENTITY_PROTEINNAME_H_
#define COMPPI_ENTITY_PROTEINNAME_H_

#include <string>

#include <odb/core.hxx>

namespace comppi {
namespace entity {

#pragma db value(std::string) type("VARCHAR(255)")

#pragma db object
class ProteinName {
    #pragma db index("unique_name") unique members(_name)
public:
    ProteinName(const std::string& name)
        :_name(name)
    {}

private:
    friend class odb::access;

    #pragma db id
    std::string _name;
};

} // namespace entity
} // namespace comppi

#endif // COMPPI_ENTITY_PROTEINNAME_H_
