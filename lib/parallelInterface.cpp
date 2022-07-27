#include "parallelInterface.h"

Parallel8Bit::Parallel8Bit(int cs_, int reset_, int data_sel_, int readwrite_, int enable_, int bit_0_, int bit_1_, int bit_2_, int bit_3_, int bit_4_, int bit_5_, int bit_6_, int bit_7_)
{
    cs = cs_;
    reset = reset_;
    data_sel = data_sel_;
    readwrite = readwrite_;
    enable = enable_;
    bit_0 = bit_0_;
    bit_1 = bit_1_;
    bit_2 = bit_2_;
    bit_3 = bit_3_;
    bit_4 = bit_4_;
    bit_5 = bit_5_;
    bit_6 = bit_6_;
    bit_7 = bit_7_;
    initialize();
    set_direction(GPIO_OUT);
}

void Parallel8Bit::initialize()
{
    gpio_init(cs);
    gpio_init(reset);
    gpio_init(data_sel);
    gpio_init(readwrite);
    gpio_init(enable);
    gpio_init(bit_0);
    gpio_init(bit_1);
    gpio_init(bit_2);
    gpio_init(bit_3);
    gpio_init(bit_4);
    gpio_init(bit_5);
    gpio_init(bit_6);
    gpio_init(bit_7);
}

void Parallel8Bit::set_direction(bool dir)
{
    gpio_set_dir(bit_0, dir);
    gpio_set_dir(bit_1, dir);
    gpio_set_dir(bit_2, dir);
    gpio_set_dir(bit_3, dir);
    gpio_set_dir(bit_4, dir);
    gpio_set_dir(bit_5, dir);
    gpio_set_dir(bit_6, dir);
    gpio_set_dir(bit_7, dir);
};