#include "Dongle.h"

int Dongle::openPort(std::string tty)
{
    fd=open(tty.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd==-1)
    {
        return -1;
    }else
    {
        fcntl(fd,F_SETFL,0);
        return 0;
    }
    return -1;
}

int main()
{

}
