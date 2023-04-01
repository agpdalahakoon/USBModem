#ifndef DONGLE_H
#define DONGLE_H

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <unistd.h>
#include <sys/ioctl.h>

class Dongle
{
    private:
        int fd;
    public:
        ~Dongle()
        {
            close(fd);
        }
        int open_port(std::string tty);
        void configure_port();
        std::string query_modem(std::string txt);
        std::string decode(std::string txt);
};

#endif
