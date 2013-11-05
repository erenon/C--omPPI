#ifndef COMPPI_SERVICE_LOCALIZATION_LOCALIZATION_H_
#define COMPPI_SERVICE_LOCALIZATION_LOCALIZATION_H_

#include <memory>
#include <map>

namespace comppi {
namespace service {

class Container;

namespace localization {

class Localization {
public:
    typedef std::shared_ptr<Localization> SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container);
    };

    Localization(const std::string& loctreePath);

    int getId(const std::string& goCode) const;

private:
    void loadLoctree(const std::string& loctreePath);

    std::map<std::string, int> _localizations;
};

} // namespace localization
} // namespace service
} // namespace comppi

#endif // COMPPI_SERVICE_LOCALIZATION_LOCALIZATION_H_
