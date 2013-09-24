#include <iostream>

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

    {
        // read config
        using comppi::service::config::Config;
        Config conf;
        bool status = conf.loadFile("config/config.json");

        if (!status) {
            return 1;
        }
    }


    return 0;
}
