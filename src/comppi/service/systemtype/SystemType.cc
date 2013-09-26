#include <fstream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <comppi/service/systemtype/SystemType.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>

#include <comppi/entity/SystemType.h>
#include <comppi/entity/gen/SystemType-odb.hxx>

#include <comppi/utility/Tokenizer.h>

namespace comppi {
namespace service {
namespace systemtype {

SystemType::SelfPtr SystemType::ServiceFactory::create(Container& container) {
    auto config = container.get<config::Config>();

    std::string systemPath(config->get("systemtype.system"));
    std::string synonymPath(config->get("systemtype.synonym"));

    auto databasePtr = container.get<database::Database>();

    return std::make_shared<SystemType>(systemPath, synonymPath, databasePtr);
}

SystemType::SystemType(
    const std::string& systemPath,
    const std::string& synonymPath,
    database::DatabasePtr databasePtr
)
    :_systemPath(systemPath),
     _synonymPath(synonymPath),
     _databasePtr(databasePtr)
{}

bool SystemType::loadDatabase() {
    INFO << "Load SystemTypes from: " << _systemPath;

    std::fstream input(_systemPath.c_str(), std::fstream::in);
    utility::Tokenizer<2> tokenizer(input, {{0, 1}}, ';');

    {
        using namespace comppi::service::database;
        Transaction transaction(_databasePtr->begin());

        for (const auto& line : tokenizer) {
            try {
                int confidenceType = boost::lexical_cast<int>(line[1]);

                entity::SystemType st(
                    boost::trim_copy(line[0]),
                    confidenceType
                );

//                TRACE << "Load [" << boost::trim_copy(line[0])
//                    << ", " << confidenceType << "]";

                _databasePtr->persist(st);
            } catch (const boost::bad_lexical_cast& ex) {
                ERROR << "System type named '" << line[0]
                    << "' has invalid confidence type: "
                    << ex.what();
            } catch (const std::invalid_argument& ex) {
                ERROR << "While loading system type named '" << line[0]
                    << "': "
                    << ex.what();
            }
        }

        transaction.commit();
    }

    input.close();

    return true;
}

} // namespace systemtype
} // namespace service
} // namespace comppi
