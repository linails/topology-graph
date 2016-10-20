/*
 * Progarm Name: serial.cpp
 * Created Time: 2015-12-23 13:29:37
 * Last modified: 2016-10-19 15:28:37
 */

#include "serial.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pty.h>
#include <ctype.h>
#include <sched.h>
#include <signal.h>
#include <termios.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/stat.h>

using std::cin;
using std::cout;
using std::string;
using std::endl;

/*file desc*/
int Serial::fd = 0;

/*serial constructor*/
Serial::Serial(std::string uart,int speed)
    :bits(8)         /*data bits*/
    ,parity('N')     /*parity check*/
    ,stop(1)         /*stop bits*/
    ,mode(0)         /*raw or normal mode */
{
    if(fd == 0){
        int ttyfd = serial_open(uart.c_str());
        if(ttyfd < 0){
            cout << "can not open : "<< this->uart_device << endl;
            return ;
        }else{
            cout << "open : " << this->uart_device << endl;
        }

        fd = ttyfd;
        this->uart_device = uart;
        this->speed = speed;
        if(serial_setup() != 0){
            cout << "set serial error\n" << endl;
        }
    }
}

/*serial destructor*/
Serial::~Serial(void)
{
    if(fd != 0){
        close(fd);
        fd=0;
    }
}

/*read bytes from serial*/
int Serial::serial_read(char *rbuf,int &index)
{
    index = 0;
    if(fd != 0){
        int size = 0;
        while(1){
            size = read(fd,rbuf+index,1024);
            if(size == 0) break;
            index += size;
		    usleep(10*1000);
        }
    }else{
        return -1;
    }
    return index;
}

/*write bytes to serial*/
int Serial::serial_write(char *wbuf,int length)
{
    if(fd != 0){
        usleep(10*1000);
        return write(fd,wbuf,length);
    }else{
        return -1;
    }
}

/*get uart*/
void Serial::get_uart(std::string &uart) const
{
    if(fd != 0){
        uart = this->uart_device;
    }else{
        uart.clear();
    }
}

/*get speed*/
void Serial::get_speed(int &bspeed) const
{
    if(fd != 0){
        bspeed = this->speed;
    }else{
        bspeed = 0;
    }
}

//-----------------------------------------------------------------------------

/*serial setup : serial control cfg*/
int Serial::serial_setup(void)
{
    struct termios newtio, oldtio;

    if(tcgetattr(fd, &oldtio) != 0){
        cout<< "tcgetattr failed: %s\n" << strerror(errno) << endl;
        return -1;
    }

    memset(&newtio, 0, sizeof(newtio));
    memcpy(&newtio, &oldtio, sizeof(struct termios));

    if(this->mode == 0){
        /* Set raw mode: the remote application will handle all terminal characters*/
        cfmakeraw(&newtio);
    }

    switch(this->bits){
        case 7: newtio.c_cflag |= CS7; break;
        case 8: newtio.c_cflag |= CS8; break;
    }

    switch(this->parity){
        case 'O':
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'E':
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'N':
            newtio.c_cflag &= ~PARENB;
            newtio.c_iflag &= ~INPCK;
            break;
    }

    switch(this->speed){
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 38400:
            cfsetispeed(&newtio, B38400);
            cfsetospeed(&newtio, B38400);
            break;
        case 57600:
            cfsetispeed(&newtio, B57600);
            cfsetospeed(&newtio, B57600);
            break;
        case 115200:            
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        default:
            cfsetispeed(&newtio, B38400);
            cfsetospeed(&newtio, B38400);
            break;
    }

    if(this->stop == 1)         newtio.c_cflag &= ~CSTOPB;
    else if(this->stop == 2)    newtio.c_cflag |= CSTOPB;

    tcflush(this->fd, TCIOFLUSH);

    /*set timeout of newtio.c_cc[VTIME]/10 s*/
    newtio.c_cc[VTIME] = 0.001;
    newtio.c_cc[VMIN] = 0;

    if(tcsetattr(this->fd, TCSANOW, &newtio) < 0){
        cout<< "tcsetattr failed: " << strerror(errno) << endl;
        return -1;
    }
        
    return 0;
}

/*serial open*/
int Serial::serial_open(const char *name)
{
    int fd = open(name,O_RDWR);

    if(fd < 0) return -1;

    /*set serial to block status
     * wait for read from serial port*/
    fcntl(fd, F_SETFL, 0);
    return fd;
}


