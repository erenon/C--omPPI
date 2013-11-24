#ifndef COMPPI_SERVICE_GEXF_WRITER_H_
#define COMPPI_SERVICE_GEXF_WRITER_H_

#include <memory>
#include <fstream>

#include <comppi/service/Container.h>

#include <comppi/entity/Protein.h>
#include <comppi/entity/Interaction.h>

namespace comppi {
namespace service {
namespace gexf {

class Writer {
public:
    typedef std::shared_ptr<Writer> SelfPtr;

    struct ServiceFactory {
        static SelfPtr create(Container& container);
    };

    Writer(const std::string& outputPath);

    template <typename NodeCont>
    void addNodes(NodeCont& nodes) {
        if (_status != NODES) {
            _output << "<nodes>";
            _status = NODES;
        }

        for (const entity::Protein& protein : nodes) {
            _output << "<node id=\"" << protein.getId()
                << "\" label=\"" << protein.getProteinName()
                << "\">";
        }
    }

    template <typename EdgeCont>
    void addEdges(EdgeCont& edges) {
        if (_status == NODES) {
            _output << "</nodes><edges>";
            _status = EDGES;
        }

        for (const entity::Interaction& interaction : edges) {
            _output << "<edge source=\""
                << interaction.getActorA()->getId()
                << "\" target=\""
                << interaction.getActorB()->getId() << "\">";
        }
    }

    void close();

private:
    enum STATUS {
        INIT,
        NODES,
        EDGES
    };

    STATUS _status;
    std::fstream _output;
};

} // namespace gexf
} // namespace service
} // namespace comppi


#endif // COMPPI_SERVICE_GEXF_WRITER_H_
