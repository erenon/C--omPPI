#include <cstdlib> // std::atoi

#include <comppi/service/driver/localization/Organelle.h>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>

#include <comppi/entity/Localization.h>
#include <comppi/entity/Protein.h>
#include <comppi/entity/SystemType.h>

namespace comppi {
namespace service {
namespace driver {
namespace localization {

Organelle::Organelle(std::fstream& input, const config::Config& config, Container& container)
    :_tokenizer(input, {{0, 2}}, '\t'),
     _speciesId(config.get<int>("speciesId")),
     _sLocalization(container.get<service::localization::Localization>()),
     _systemType(std::make_shared<entity::SystemType>("Experimental (experimental)", 0)),
     _locToGo({
        {"axoneme", "GO:0005930"},
        {"basal body", "GO:0005932"},
        {"bud neck", "GO:0005935"},
        {"bud tip", "GO:0005934"},
        {"cell septum", "GO:0030428"},
        {"chromosome", "GO:0005694"},
        {"cilium", "GO:0005929"},
        {"contractile ring", "GO:0070938"},
        {"cyclin-dependent protein kinase holoenzyme complex", "GO:0000307"},
        {"cytoskeleton", "GO:0005856"},
        {"cytosol", "GO:0005737"},
        {"endomembrane system", "GO:0012505"},
        {"endosome membrane", "GO:0010008"},
        {"endopeptidase Clp complex", "GO:0009368"},
        {"endoplasmic reticulum", "GO:0005783"},
        {"exocyst", "GO:0000145"},
        {"exosome (RNase complex)", "GO:0000178"},
        {"extrinsic to endoplasmic reticulum membrane", "GO:0042406"},
        {"extrinsic to vacuolar membrane", "GO:0000306"},
        {"flagellum", "GO:0019861"},
        {"incipient bud site", "GO:0000131"},
        {"inclusion body", "GO:0016234"},
        {"integral to endoplasmic reticulum membrane", "GO:0030176"},
        {"integral to Golgi membrane", "GO:0030173"},
        {"integral to nuclear inner membrane", "GO:0005639"},
        {"integral to synaptic vesicle membrane", "GO:0030285"},
        {"intracellular cyclic nucleotide activated cation channel complex", "GO:0017071"},
        {"lipopolysaccharide receptor complex", "GO:0046696"},
        {"lysosomal membrane", "GO:0005765"},
        {"meprin A complex", "GO:0017090"},
        {"mitochondrion", "GO:0005739"},
        {"mRNA cap complex", "GO:0031533"},
        {"nucleoid", "GO:0009295"},
        {"nucleus", "GO:0005634"},
        {"Organelle", "GO:0043226"},
        {"organelle inner membrane", "GO:0019866"},
        {"oxoglutarate dehydrogenase complex", "GO:0045252"},
        {"peroxisomal membrane", "GO:0005778"},
        {"plasma membrane", "GO:0005886"},
        {"polarisome", "GO:0000133"},
        {"pore complex", "GO:0046930"},
        {"proton-transporting ATP synthase complex", "GO:0045259"},
        {"proton-transporting two-sector ATPase complex", "GO:0016469"},
        {"respiratory chain complex I", "GO:0045271"},
        {"respiratory chain complex II", "GO:0045273"},
        {"respiratory chain complex III", "GO:0045275"},
        {"respiratory chain complex IV", "GO:0045277"},
        {"ribonucleoprotein complex", "GO:0030529"},
        {"RNA polymerase complex", "GO:0030880"},
        {"septin ring", "GO:0005940"},
        {"succinate dehydrogenase complex (ubiquinone)", "GO:0045281"},
        {"ubiquitin ligase complex", "GO:0000151"},
        {"UDP-N-acetylglucosamine-peptide N-acetylglucosaminyltransferase complex", "GO:0017122"},
        {"vacuolar membrane", "GO:0005774"}
    })
{
    // read config
    // TODO init map by config

    // skip header
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Organelle::iterator::iterator(const TokenIterator it, const TokenIterator end, const Organelle& driver)
    :_it(it),
     _end(end),
     _driver(driver),
     _localizationId(-1)
{
    if (!setLocalizationId()) {
        ++(*this);
    }
}

Organelle::iterator::iterator(const TokenIterator end, const Organelle& driver)
    :_it(end),
     _end(end),
     _driver(driver),
     _localizationId(-1)
{}

Organelle::iterator& Organelle::iterator::operator++() {
    bool validLoc = false;
    while (!validLoc) {
        ++_it;
        validLoc = setLocalizationId();
    }
    return *this;
}

entity::Localization Organelle::iterator::operator*() const {
    auto localization = entity::Localization(
        std::make_shared<entity::Protein>(
            _driver._speciesId,
            _it[1],
            "Organelle"
        ),
        _localizationId,
        "Organelle",
        15608270
    );

    localization.addSystemType(_driver._systemType);

    return localization;
}

bool Organelle::iterator::operator==(const iterator& rhs) const {
    return _it == rhs._it;
}

bool Organelle::iterator::operator!=(const iterator& rhs) const {
    return _it != rhs._it;
}

bool Organelle::iterator::setLocalizationId() {
    std::string goc;
    int locId;
    return _driver.goCode(_it[0], goc) && _driver.locId(goc, _localizationId);
}

bool Organelle::goCode(const std::string& localization, std::string& goCode) const {
    auto finder(_locToGo.find(localization));

    if (finder != _locToGo.end()) {
        goCode = finder->second;
        return true;
    } else {
        WARNING << "No GO code found for localization: '"
            << localization << "'";

        return false;
    }
}

bool Organelle::locId(const std::string& goCode, int& locId) const {
    locId = _sLocalization->getId(goCode);
    return locId >= 0;
}

Organelle::iterator Organelle::begin() {
    return iterator(_tokenizer.begin(), _tokenizer.end(), *this);
}

Organelle::iterator Organelle::end() {
    return iterator(_tokenizer.end(), *this);
}

} // namespace localization
} // namespace driver
} // namespace service
} // namespace comppi
