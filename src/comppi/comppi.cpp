#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>

#include <comppi/controller/Map.h>
#include <comppi/controller/Interaction.h>

int main(int argc, char* argv[]) {
    using comppi::service::Container;
    Container container;

    using comppi::service::config::Config;

    {   // bootstrap config
        auto config = container.get<Config>();

        // read config
        bool status = config->loadFile("config/config.json");

        if (!status) {
            return 1;
        }

        // TODO make this configurable from cli
        config->setTransformation("comppi_root", ".");
    }

//    {   // TODO bootstrap logging
//        auto config = container.get<Config>();
//        std::cout << config->get("log.level") << std::endl;
//    }

//    {
//        using comppi::service::systemtype::SystemType;
//        auto stPtr = container.get<SystemType>();
//        stPtr->loadDatabase();
//    }
//    { // init program options
//        using namespace boost::program_options;
//
//        options_description generic("Allowed options");
//        generic.add_options()
//            ("help,h", "Show this help")
//        ;
//
//        options_description command("Command and options");
//        command.add_options()
//            ("command", value< std::vector<std::string> >(), "Command and arguments")
//        ;
//
//        options_description cli("CLI commands");
//        cli.add(generic).add(command);
//
//        positional_options_description p;
//        p.add("command", -1);
//
//        variables_map vm;
//
//        try {
//            store(
//                command_line_parser(argc, argv)
//                    .options(cli)
//                    .positional(p).run(),
//                vm
//            );
//        } catch (const unknown_option& ex) {
//            std::cout << ex.what() << std::endl
//                << generic << std::endl;
//        }
//        //notify(vm);
//
//        if (vm.count("help")) {
//            std::cout << generic << std::endl;
//            return 1;
//        }
//
//        if (vm.count("command")) {
//            std::cout << vm["command"].as< std::vector<std::string> >()[0]
//                << std::endl;
//        }
//    }

//    {
//        using comppi::controller::Map;
//        Map mapController(container);
//        std::vector<std::string> inputs;
//        mapController.build(inputs);
//    }

    {
        using comppi::controller::Interaction;
        Interaction controller(container);
        std::vector<std::string> inputs;
        controller.build(inputs);
    }

    return 0;
}
