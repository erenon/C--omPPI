#include <stdexcept>

#include <comppi/service/species/Species.h>
#include <comppi/service/log/Log.h>

namespace comppi {
namespace service {
namespace species {

Species::SelfPtr Species::ServiceFactory::create(Container& container) {
    auto config = container.get<config::Config>()->subtree("species");

    return std::make_shared<Species>(config);
}

Species::Species(const config::Config& config) {
    int i = 0;
    for (auto sd : config) {
        Descriptor descriptor(i, sd.get("abbr"), sd.get("name"));
        _descriptors.insert(descriptor);

        i++;
    }
}


Species::Descriptor Species::getById(int id) {
    const auto& byId = _descriptors.get<0>();
    auto finder = byId.find(id);

    if (finder == byId.end()) {
        WARNING << "No species found for id: " << id;
        throw std::out_of_range("Invalid species id");
    }

    return *finder;
}

Species::Descriptor Species::getByAbbr(const std::string& abbr) {
    const auto& byAbbr = _descriptors.get<1>();
    auto finder = byAbbr.find(abbr);

    if (finder == byAbbr.end()) {
        WARNING << "No species found for abbreviation: " << abbr;
        throw std::out_of_range("Invalid species abbr");
    }

    return *finder;
}


} // namespace species
} // namespace service
} // namespace comppi
