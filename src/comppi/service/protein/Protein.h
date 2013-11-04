#ifndef COMPPI_SERVICE_PROTEIN_PROTEIN_H_
#define COMPPI_SERVICE_PROTEIN_PROTEIN_H_

#include <memory>
#include <vector>

#include <comppi/service/database/Database.h>

namespace comppi {
namespace entity {

class Protein;
class ProteinNameMap;

} // namespace entity

namespace service {

class Container;

namespace protein {

class Protein {
public:
    typedef std::shared_ptr<Protein> SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container);
    };

    Protein(
        database::DatabasePtr databasePtr
    );

    std::vector<entity::Protein> translate(const entity::Protein& protein);

private:
    std::vector<entity::ProteinNameMap> getStrongestTranslations(const entity::Protein& protein);
    std::size_t translationOrder(const std::string& namingConvention) const;
    entity::Protein persistProtein(entity::Protein& protein);

    database::DatabasePtr _databasePtr;
    std::vector<std::string> _namingConventionOrder;
};

} // namespace protein
} // namespace service
} // namespace comppi

#endif // COMPPI_SERVICE_PROTEIN_PROTEIN_H_
