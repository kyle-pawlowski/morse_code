#include <wiringPi.h>
int rs_pin = 1;
int rw_pin = 2;
int en_pin = 3;
int db4_pin = 4;
int db5_pin = 5;
int db6_pin = 6;
int db7_pin = 7;
class Display{
    Display(){
        wiringPiSetup();
        pinMode(rs_pin, OUTPUT);
        pinMode(rw_pin, OUTPUT);
        pinMode(en_pin, OUTPUT);
        pinMode(db4_pin, OUTPUT);
        pinMode(db5_pin, OUTPUT);
        pinMode(db6_pin, OUTPUT);
        pinMode(db7_pin, OUTPUT);
    }
    void command(char data){

    }
    void data(char data){

    }
    int* byte_out(char data, int* out){
        int msb = data/8;
        out[3] = msb;
        int msb2 = (data - msb*8)/4;
        out[2] = msb2;
        int msb3 = (data-msb*8-msb2*4);
        out[1] = msb3;
        int msb4 = (data-msb*8-msb2*4-msb3*2);
    }
}