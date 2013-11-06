#ifndef COMPPI_SERVICE_DRIVER_LOCALIZATION_ORGANELLE_H_
#define COMPPI_SERVICE_DRIVER_LOCALIZATION_ORGANELLE_H_

#include <fstream>
#include <memory>
#include <map>
#include <string>

#include <comppi/utility/Tokenizer.h>

#include <comppi/service/localization/Localization.h>

#include <comppi/entity/SystemType.h>

namespace comppi {

namespace entity {
    class Localization;
} // namespace entity

namespace service {

class Container;

namespace config {
    class Config;
} // namespace config

namespace driver {
namespace localization {

class Organelle {
private:
    typedef utility::Tokenizer<2> Tokenizer;
    typedef Tokenizer::iterator TokenIterator;
public:
    Organelle(std::fstream& input, const config::Config& config, Container& container);

    class iterator {
    public:
        iterator(const TokenIterator it, const TokenIterator end, const Organelle& driver);
        iterator(const TokenIterator end, const Organelle& driver);
        iterator& operator++();
        entity::Localization operator*() const;
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
    private:
        bool setLocalizationId();

        TokenIterator _it;
        TokenIterator _end;
        const Organelle& _driver;
        int _localizationId;
    };

    iterator begin();
    iterator end();

private:
    bool goCode(const std::string& localization, std::string& goCode) const;
    bool locId(const std::string& goCode, int& locId) const;

    Tokenizer _tokenizer;
    int _speciesId;
    service::localization::Localization::SelfPtr _sLocalization;
    std::shared_ptr<entity::SystemType> _systemType;
    std::map<std::string, std::string> _locToGo;
};

} // namespace localization
} // namespace driver
} // namespace service
} // namespace comppi

#endif // COMPPI_SERVICE_DRIVER_LOCALIZATION_ORGANELLE_H_
