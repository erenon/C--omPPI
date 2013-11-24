#include <fstream>
#include <stdexcept>
#include <sstream>

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
{
    loadSynonyms();
}

bool SystemType::loadDatabase() {
    INFO << "Load SystemTypes from: " << _systemPath;

    std::fstream input(_systemPath.c_str(), std::fstream::in);

    if (!input) {
        ERROR << "Failed to open systems file";
        return false;
    }

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

entity::SystemType SystemType::getSystemType(const std::string& name) {
    typedef odb::query<entity::SystemType> Query;
    typedef odb::prepared_query<entity::SystemType> PrepQuery;
    typedef odb::result<entity::SystemType> Result;

    using comppi::service::database::Transaction;
    Transaction transaction(_databasePtr->begin());

    std::string* pName;

    PrepQuery pqSystemType(
        _databasePtr->lookup_query<entity::SystemType>(
            "systemtype-systemtype",
            pName
        )
    );

    if (!pqSystemType) {
        DEBUG << "Prepare query: systemtype-systemtype";

        std::unique_ptr<std::string> namePtr(new std::string);

        pName = namePtr.get();

        Query qSystemType(Query::name == Query::_ref(*namePtr));

        pqSystemType = _databasePtr->prepare_query<entity::SystemType>(
            "systemtype-systemtype",
            qSystemType
        );

        _databasePtr->cache_query(
            pqSystemType,
            std::move(namePtr)
        );
    }

    *pName = name;

    Result rSystemType(pqSystemType.execute());

    if (!rSystemType.empty()) {
        auto systemType = *rSystemType.begin();
        transaction.commit();

        return systemType;
    } else {
        entity::SystemType systemType(name, entity::SystemType::UNKNOWN);
        _databasePtr->persist(systemType);
        transaction.commit();
        return systemType;
    }
}

bool SystemType::loadSynonyms() {
    INFO << "Load SystemType synonyms from: " << _synonymPath;

    std::fstream input(_synonymPath.c_str(), std::fstream::in);

    if (!input) {
        ERROR << "Failed to open synonyms file";
        return false;
    }

    while (input) {
        std::string line;
        std::getline(input, line, '\n');

        std::stringstream lineStream(line);
        std::string mainName;
        std::getline(lineStream, mainName, ';');

        while (lineStream) {
            std::string synonym;
            std::getline(lineStream, synonym, ';');

            boost::trim(synonym);

            if (!synonym.empty()) {
                TRACE << "Add synonym: " << synonym << " -> " << mainName;
                _synonyms.insert(std::make_pair(mainName, synonym));
            }
        }
    }

    input.close();

    return true;
}

} // namespace systemtype
} // namespace service
} // namespace comppi
