#include "Dongle.hpp"


int Dongle::open_port(std::string tty)
{
    fd=open(tty.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd==-1)
    {
        return -1;
    }else
    {
        fcntl(fd,F_SETFL,0);
        configure_port();
        return 0;
    }
    return -1;
}

void Dongle::configure_port()
{
    struct termios port_settings;      // structure to store the port settings in

	cfsetispeed(&port_settings, B9600);    // set baud rates
	cfsetospeed(&port_settings, B9600);

	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;

	tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
}
std::string Dongle::query_modem(std::string txt)
{
    std::string str;

    std::cout<<"Writing :"<<txt.c_str()<<std::endl;
	write(fd,txt.c_str() ,txt.size() );  //Send data

    
    bool finished{false};
    while(!finished)
    {
        int bytes{0};
        while(bytes==0)
        {
            ioctl(fd,FIONREAD,&bytes);
        }
        std::cout<<"Ioctl returned "<<bytes<<std::endl;

        char buf[bytes];
        
        int r=read(fd,buf,sizeof(buf));
        std::cout<<"Readed "<<r<<std::endl;
        str+=buf;
        auto ret=str.find("OK");
        if(ret!=std::string::npos)
        {
            finished=true;
        }
    }

    return str;
}

std::string Dongle::decode(std::string txt)
{
    std::string message;
    return message;
}

int main()
{
    std::cout<<"Starting the program"<<std::endl;
    Dongle d;
    int r=d.open_port("/dev/ttyUSB0");
    std::cout<<"Port open :"<<r<<std::endl;
    std::cout<<""<<d.query_modem("AT+CPMS=\"ME\"\r\n")<<std::endl;
    std::cout<<""<<d.query_modem("AT+CMGF=1\r\n")<<std::endl;
    std::cout<<""<<d.query_modem("AT+CMGR=3\r\n")<<std::endl;
    std::string inp;
    while(1)
    {
        std::cout<<"Please input command"<<std::endl;
        std::cin >> inp;
        std::cout<<d.query_modem(inp+"\r\n")<<std::endl;
    }

}
