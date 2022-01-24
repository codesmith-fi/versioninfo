// versioninfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "version.h"

int main()
{
    Version16 ver;
    ver.set(1, 0, 0);

    std::cout << "Version: " << ver.getString() << std::endl;

    ver.incrementBuild();
    std::cout << "Version: " << ver.getString() << std::endl;
    return 0;
}
