#ifndef COMPPI_SERVICE_SPECIES_SPECIES_H_
#define COMPPI_SERVICE__SPECIES_H_

#include <memory>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

#include <comppi/entity/Species.h>

namespace comppi {
namespace service {
namespace species {

namespace bmi = boost::multi_index;

class Species {
public:
    typedef std::shared_ptr<Species> SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container);
    };

    Species(const config::Config& config);

    typedef entity::Species Descriptor;

    Descriptor getById(int id);
    Descriptor getByAbbr(const std::string& abbr);

private:
    typedef bmi::multi_index_container<
        Descriptor,
        bmi::indexed_by<
            bmi::ordered_unique<bmi::member_offset<Descriptor, int, offsetof(Descriptor, id)>>,
            bmi::ordered_unique<bmi::member_offset<Descriptor, std::string, offsetof(Descriptor, abbr)>>
        >
    > DescriptorContainer;

    DescriptorContainer _descriptors;
};

} // namespace species
} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE__SPECIES_H_
