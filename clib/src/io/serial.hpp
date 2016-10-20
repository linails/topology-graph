/*
 * Progarm Name: serial.hpp
 * Created Time: 2015-12-23 13:29:41
 * Last modified: 2016-10-19 15:27:51
 */

#ifndef _SERIAL_HPP_
#define _SERIAL_HPP_
#include <string>

/*define serial class*/
class Serial{
public:
    Serial(std::string uart = "/dev/ttyUSB0", int speed = 115200);
    ~Serial(void);

    int serial_read(char *rbuf,int &index);/*read bytes from serial*/
    int serial_write(char *wbuf,int length);/*write bytes to serial*/
    void get_uart(std::string &uart) const ;
    void get_speed(int &bspeed) const ;
private:
    std::string uart_device;
    int speed;          /*baudrate*/
    int bits;           /*data bits*/
    int parity;         /*parity check*/
    int stop;           /*stop bits*/
    int mode;           /*raw or normal mode */
private:
    int serial_setup(void);
    int serial_open(const char *name);
private:
    static int fd;      /*file desc*/
};

#endif //_SERIAL_HPP_

