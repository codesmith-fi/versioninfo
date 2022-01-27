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
    codesmith::util::CommandLineOption optionMajorVer("-sma",
        "Set major version (-sma [integer])");
    codesmith::util::CommandLineOption optionMinorVer("-smi",
        "Set minor version (-smi [integer])");
    codesmith::util::CommandLineOption optionBuild("-sb",
        "Set build version (-sb [integer])");
    codesmith::util::CommandLineOption optionIncMajor("-ima",
        "Increment major version by one");
    codesmith::util::CommandLineOption optionIncMinor("-imi",
        "Increment minor version by one");
    codesmith::util::CommandLineOption optionIncBuild("-ib",
        "Increment build version by one");
    args.addOption(optionHelp);
    args.addOption(optionInit);
    args.addOption(optionMajorVer);
    args.addOption(optionMinorVer);
    args.addOption(optionBuild);
    args.addOption(optionIncMajor);
    args.addOption(optionIncMinor);
    args.addOption(optionIncBuild);

    std::cout << "VersionInfo v0.1.0 by Erno Pakarinen (codesmith.fi@gmail.com)\n\n";
    std::cout << "Loading version info\n";
    ver.load();
    std::cout << "Current version: " << ver.str() << std::endl;

    if (args.optionExists(optionHelp)) {
        std::cout << "Following command line options can be used:\n";
        args.showHelp();
        return 0;
    } else if(args.optionExists(optionInit)) {
        std::cout << "Setting up version\n";
        int majorver = args.getValueInt(optionMajorVer);
        int minorver = args.getValueInt(optionMinorVer);
        int build = args.getValueInt(optionBuild);
        ver.set(majorver, minorver, build);
        ver.save();
        std::cout << "New version: " << ver.str() << std::endl;
    }
    else {
        if (args.optionExists(optionIncBuild)) {
            ver.incrementBuild();
            ver.save();
            std::cout << "New version: " << ver.str() << std::endl;
        } else if (args.optionExists(optionIncMinor)) {
            ver.incrementMinor();
            ver.save();
            std::cout << "New version: " << ver.str() << std::endl;
        }else if (args.optionExists(optionIncMajor)) {
            ver.incrementMajor();
            ver.save();
            std::cout << "New version: " << ver.str() << std::endl;
        }
    }

    return 0;
}
