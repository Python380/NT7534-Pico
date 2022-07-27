#ifndef PARALLELINTERFACE_H
#define PARALLELINTERFACE_H

#include "pico/stdlib.h"

class Parallel8Bit
{
public:
    Parallel8Bit(int cs, int reset, int data_sel, int readwrite, int enable, int bit_0, int bit_1, int bit_2, int bit_3, int bit_4, int bit_5, int bit_6, int bit_7);
    void set_direction(bool dir);

    int cs;
    int reset;
    int data_sel;
    int readwrite;
    int enable;
    int bit_0;
    int bit_1;
    int bit_2;
    int bit_3;
    int bit_4;
    int bit_5;
    int bit_6;
    int bit_7;

private:
    void initialize();
};

#endif