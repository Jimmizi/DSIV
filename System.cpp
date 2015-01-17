#include "System.h"
#include <sstream>

System::System()
{
    stillPlaying = true;
}

std::string System::convertInt(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

int System::convertString(std::string number)
{
    return atoi(number.c_str());
}

void System::quit()
{
    stillPlaying = false;
}

bool System::inPlay()
{
    return stillPlaying;
}
