#include <iostream>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>

#include <comppi/entity/SystemType.h>
#include <comppi/entity/gen/SystemType-odb.hxx>
#include <comppi/service/database/Database.h>

int main(int argc, char* argv[]) {
//    comppi::entity::SystemType st("bar", comppi::entity::SystemType::EXPERIMENTAL);
//
//    std::cout << st.getName() << std::endl;
//
//    {
//        using namespace comppi::service::database;
//        DatabasePtr db(createDatabase());
//
//        Transaction transaction(db->begin());
//
//        db->persist(st);
//
//        std::cout << st.getId() << std::endl;
//
//        transaction.commit();
//    }
    using comppi::service::Container;
    Container container;

    using comppi::service::config::Config;

    {
        auto config = container.get<Config>();

        // read config
        bool status = config->loadFile("config/config.json");

        if (!status) {
            return 1;
        }
    }

    {
        auto config = container.get<Config>();
        std::cout << config->get("log.level") << std::endl;
    }


    return 0;
}
