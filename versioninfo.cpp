// versioninfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "version.h"
#include "cmdline.h"

int main(int argc, char** argv)
{
    codesmith::types::Version ver;
    codesmith::util::CommandLineArgs args(argc, argv);
    codesmith::util::CommandLineOption optionInit("-i",
        "Initialize version information with given details"); // init version
    codesmith::util::CommandLineOption optionHelp("-h",
        "Show this help"); // help

    args.addOption(optionHelp);
    args.addOption(optionInit);

    if (args.optionExists(optionHelp)) {
        std::cout << "VersionInfo v0.1.0 by Erno Pakarinen (codesmith.fi@gmail.com)\n";
        std::cout << "Following command line options can be used:\n";
        args.showHelp();
        return 0;
    } else if(args.optionExists(optionInit)) {
        std::cout << "Initializing version";
        return 0;
    }

    ver.set(1, 0, 0);

    std::cout << "Version: " << ver.str() << std::endl;

    ver.incrementBuild();
    std::cout << "Version: " << ver.str() << std::endl;

    std::cout << "Saving\n";
    ver.save();
    ver.incrementMinor();
    std::cout << "Version: " << ver.str() << std::endl;

    std::cout << "Loading\n";
    ver.load();
    std::cout << "Version: " << ver.str() << std::endl;
    return 0;
}
