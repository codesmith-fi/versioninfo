/**
VersionInfo - A tool which can be used for managing application version

Author: Erno Pakarinen (codesmith.fi@gmail.com)
Date: 31.01.2022

Licenced with MIT licence. Free to copy, modify and use in your 
projects.

Usage: (Get help with -h argument)

Set a specific version with -i and provide the major, minor and
build version using -sma -smi and -sb arguments.

Increment build, minor or major version with -ima, imi or -ib
arguments.
 
Version information is stored as a file the current directory,
filename is "version.dat" and it's binary file.
 
LICENSE - MIT
Copyright(c) 2022 Erno Pakarinen(codesmith.fi@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining
a copy of this softwareand associated documentation files(the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and /or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions :

The above copyright noticeand this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
