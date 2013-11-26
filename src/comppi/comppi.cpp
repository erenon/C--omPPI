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
#include <comppi/controller/Gexf.h>
#include <comppi/controller/Namelookup.h>
#include <comppi/controller/Namelist.h>
#include <comppi/controller/CheckLoc.h>
#include <comppi/controller/CheckSource.h>

void showHelp(int argc, char* argv[]) {
    std::cout
        << "C++omPPI database builder and resurce generator. Usage:"
        << std::endl << std::endl

        << "    comppi [options] command [[subcommand], [input1, ...]]"
        << std::endl << std::endl

        << "Options:" << std::endl << std::endl

        << "  -v,--verbose       Be verbose (set log level to debug)" << std::endl
        << "  -V,--moreverbose   Be more verbose (set log level to trace)" << std::endl
        << "  --root             Specify project root (dir of config/)" << std::endl
        << std::endl

        << "Commands:" << std::endl << std::endl

        << "  build <subcmd> [source, ...]  Load specified or all sources into the database" << std::endl
        << "    systemtype       Load systemtypes" << std::endl
        << "    map              Load maps" << std::endl
        << "    interaction      Load interactions" << std::endl
        << "    localization     Load localizations" << std::endl
        << std::endl

        << "  generate <subcmd>  Generate derived resources and tables" << std::endl
        << "    gexfgraph        Create .gexf graph based on interactions" << std::endl
        << "    namelookup       Generate reverse name mapping" << std::endl
        << "    namelist         Generate list of protein names" << std::endl
        << std::endl

        << "  check <subcmd>     Check configuration" << std::endl
        << "    localization     Check localization tree" << std::endl
        << "    source           Check source configurations" << std::endl
        << std::endl
        << "  help               Show this help"
        << std::endl
        ;
}

bool parseArgs(
    int argc, char* argv[],
    boost::program_options::variables_map& vm
) {
    using namespace boost::program_options;

    options_description generic("Allowed options");
    generic.add_options()
        ("help,h", "Show this help")
        ("verbose,v", "Be verbose")
        ("moreverbose,V", "Be more verbose")
        ("root", value<std::string>(), "Project root")
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

    try {
        store(
            command_line_parser(argc, argv)
                .options(cli)
                .positional(p).run(),
            vm
        );
    } catch (const error& ex) {
        std::cerr << ex.what() << std::endl
            << cli << std::endl;

        return false;
    }

    if (vm.count("help")) {
        showHelp(argc, argv);
        return false;
    }

    return true;
}

int dispatchCommand(
    comppi::service::Container& container,
    boost::program_options::variables_map& vm,
    int argc, char* argv[]
) {
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
                bool success = stPtr->loadDatabase();
                if (success) {
                    return 0;
                } else {
                    return 2;
                }
            }
            else if (subcommand == "map")
            {
                using comppi::controller::Map;
                Map mapController(container);
                return mapController.buildAll(inputs);
            }
            else if (subcommand == "interaction")
            {
                using comppi::controller::Interaction;
                Interaction controller(container);
                return controller.buildAll(inputs);
            }
            else if (subcommand == "localization")
            {
                using comppi::controller::Localization;
                Localization controller(container);
                return controller.buildAll(inputs);
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
    } else if (command == "generate") {
        if (vm.count("subcommand")) {
            std::string subcommand = vm["subcommand"].as<std::string>();

            if (subcommand == "gexfgraph")
            {
                using comppi::controller::Gexf;
                Gexf controller(container);
                return controller.generate();
            }
            else if (subcommand == "namelookup")
            {
                using comppi::controller::Namelookup;
                Namelookup controller(container);
                return controller.generate();
            }
            else if (subcommand == "namelist") {
                using comppi::controller::Namelist;
                Namelist controller(container);
                return controller.generate();
            }
            else
            {
                std::cerr << "Unknown subcommand" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Usage: generate subcommand" << std::endl;
            return 0;
        }
    } else if (command == "check") {
        if (vm.count("subcommand")) {
            std::string subcommand = vm["subcommand"].as<std::string>();

            if (subcommand == "localization") {
                using comppi::controller::CheckLoc;
                CheckLoc controller(container);
                return controller.check();
            } else if (subcommand == "source") {
                using comppi::controller::CheckSource;
                CheckSource controller(container);
                return controller.check(argv[0]);
            } else {
                std::cerr << "Unknown subcommand" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Usage: check subcommand" << std::endl;
            return 0;
        }
    } else if (command == "help") {
        showHelp(argc, argv);
        return 0;
    } else {
        std::cerr << "Unknown command" << std::endl;
        return 1;
    }
}

int main(int argc, char* argv[]) {
    boost::program_options::variables_map vm;
    bool success = parseArgs(argc, argv, vm);
    if (!success) { return 1; }

    comppi::service::Container container;

    std::string projectRoot(".");
    if (vm.count("root")) {
        projectRoot = vm["root"].as<std::string>();
    }

    {   // bootstrap config
        auto config = container.get<comppi::service::config::Config>();

        // read config
        bool status = config->loadFile(projectRoot + "/config/config.json");

        if (!status) {
            return 1;
        }

        config->setTransformation("comppi_root", projectRoot);
    }

    {   // bootstrap logging
        auto config = container.get<comppi::service::config::Config>();

        if (vm.count("moreverbose")) {
            config->set("log.level", "trace");
        } else if (vm.count("verbose")) {
            config->set("log.level", "debug");
        }

        comppi::service::log::bootstrapLog(*config);
    }

    // TODO show proper help messages
    // e.g: list available commands

    if (vm.count("command")) {
        return dispatchCommand(container, vm, argc, argv);
    } else {
        std::cout << "Usage: " << argv[0] << " command" << std::endl;
        return 0;
    }
}
