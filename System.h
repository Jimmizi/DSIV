#ifndef SYSTEM_H
#define SYSTEM_H

#include "GameObject.h"

class System
{
public:
    System();

    std::string convertInt(int number);
    int convertString(std::string number);

    void quit();

    bool inPlay();
private:
    bool stillPlaying;

};

#endif // SYSTEM_H
