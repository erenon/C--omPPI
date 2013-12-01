C++omPPI
========
C++ port of the [ComPPI][1] project.

How to Build
============

To build and run the `Release` branch:

    comppi-root/ $ cd Release
    comppi-root/Release/ $ make all
    comppi-root/Release/ $ cd ../
    comppi-root/ $ ./Release/comppi help
    
To build and run the `Debug` branch:

    comppi-root/ $ cd Debug
    comppi-root/Debug/ $ make all
    comppi-root/Debug/ $ cd ../
    comppi-root/ $ ./Debug/comppi help

Commands
========

    build <subcmd> [source, ...]  Load specified or all sources into the database
      systemtype       Load systemtypes
      map              Load maps
      interaction      Load interactions
      localization     Load localizations

    generate <subcmd>  Generate derived resources and tables
      gexfgraph        Create .gexf graph based on interactions
      namelookup       Generate reverse name mapping
      namelist         Generate list of protein names

    check <subcmd>     Check configuration
      localization     Check localization tree
      source           Check source configurations

    help               Show this help
        
[1]: https://github.com/erenon/ComPPI
