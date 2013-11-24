#include <stdexcept>

#include <comppi/service/gexf/Writer.h>
#include <comppi/service/config/Config.h>

namespace comppi {
namespace service {
namespace gexf {

Writer::SelfPtr Writer::ServiceFactory::create(Container& container) {
    auto config = container.get<config::Config>();

    std::string outputPath(config->get("gexf.output"));

    return std::make_shared<Writer>(outputPath);
}

Writer::Writer(const std::string& outputPath)
    :_status(INIT),
     _output(outputPath.c_str(), std::ios_base::out)
{
    if (!_output) {
        ERROR << "Gexf Writer: failed to open file: '"
              << outputPath << "'";
        throw std::invalid_argument("Failed to open file");
    }

    _output <<
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<gexf xmlns=\"http://www.gexf.net/1.2draft\""
        "      xmlns:viz=\"http://www.gexf.net/1.1draft/viz\""
        "      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
        "      xsi:schemaLocation=\"http://www.gexf.net/1.2draft http://www.gexf.net/1.2draft/gexf.xsd\""
        "      version=\"1.2\""
        ">"
        "<graph mode=\"static\">";
}

void Writer::close() {
    _output << "</edges></graph></gexf>";
}


} // namespace gexf
} // namespace service
} // namespace comppi
