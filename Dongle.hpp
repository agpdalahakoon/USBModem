#ifndef DONGLE_H
#define DONGLE_H

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <unistd.h>
#include <poll.h>

class Dongle
{
    private:
        int fd;
    public:
        int open_port(std::string tty);
        int configure_port();
        std::string query_modem(std::string txt);
};

#endif
