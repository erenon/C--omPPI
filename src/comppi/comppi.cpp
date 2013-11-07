#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include <comppi/service/Container.h>
#include <comppi/service/config/Config.h>
#include <comppi/service/log/Log.h>
#include <comppi/service/systemtype/SystemType.h>

#include <comppi/controller/Map.h>
#include <comppi/controller/Interaction.h>
#include <comppi/controller/Localization.h>

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

    { // init program options
        using namespace boost::program_options;

        options_description generic("Allowed options");
        generic.add_options()
            ("help,h", "Show this help")
            ("verbose,v", "Be verbose")
            ("moreverbose,V", "Be more verbose")
        ;

        options_description command("Command and options");
        command.add_options()
            ("command", value<std::string>(), "Command")
            ("subcommand", value<std::string>(), "Subcommand")
            ("inputs", value< std::vector<std::string> >(), "Inputs")
        ;

        options_description cli("CLI commands");
        cli.add(generic).add(command);

        positional_options_description p;
        p.add("command", 1);
        p.add("subcommand", 1);
        p.add("inputs", -1);

        variables_map vm;

        try {
            store(
                command_line_parser(argc, argv)
                    .options(cli)
                    .positional(p).run(),
                vm
            );
        } catch (const unknown_option& ex) {
            std::cout << ex.what() << std::endl
                << cli << std::endl;
        }
        //notify(vm);

        if (vm.count("help")) {
            std::cout << cli << std::endl;
            return 0;
        }

        {   // bootstrap logging
            auto config = container.get<Config>();

            if (vm.count("moreverbose")) {
                config->set("log.level", "trace");
            } else if (vm.count("verbose")) {
                config->set("log.level", "debug");
            }

            comppi::service::log::bootstrapLog(*config);
        }

        // TODO show proper help messages
        // e.g: list available commands

        // TODO return command method result

        if (vm.count("command")) {
            std::cout << vm["command"].as<std::string>() << std::endl;

            std::string command = vm["command"].as<std::string>();

            if (command == "build") {
                if (vm.count("subcommand")) {
                    std::string subcommand = vm["subcommand"].as<std::string>();
                    std::vector<std::string> inputs;
                    if (vm.count("inputs")) {
                        inputs = vm["inputs"].as<std::vector<std::string>>();
                    }

                    if (subcommand == "systemtype")
                    {
                        using comppi::service::systemtype::SystemType;
                        auto stPtr = container.get<SystemType>();
                        stPtr->loadDatabase();
                    }
                    else if (subcommand == "map")
                    {
                        using comppi::controller::Map;
                        Map mapController(container);
                        mapController.buildAll(inputs);
                    }
                    else if (subcommand == "interaction")
                    {
                        using comppi::controller::Interaction;
                        Interaction controller(container);
                        controller.buildAll(inputs);
                    }
                    else if (subcommand == "localization")
                    {
                        using comppi::controller::Localization;
                        Localization controller(container);
                        controller.buildAll(inputs);
                    }
                    else
                    {
                        std::cerr << "Unknown subcommand" << std::endl;
                        return 1;
                    }
                } else {
                    std::cout << "Usage: build subcommand" << std::endl;
                    return 0;
                }
            } else {
                std::cerr << "Unknown command" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Usage: " << argv[0] << " command" << std::endl;
            return 0;
        }
    }

    return 0;
}
