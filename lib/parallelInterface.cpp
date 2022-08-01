#include "parallelInterface.h"

Parallel8Bit::Parallel8Bit(int cs_, int reset_, int data_sel_, int readwrite_, int enable_, int bit_0_, int bit_1_, int bit_2_, int bit_3_, int bit_4_, int bit_5_, int bit_6_, int bit_7_)
{
    Parallel8Bit::cs = cs_;
    Parallel8Bit::reset = reset_;
    Parallel8Bit::data_sel = data_sel_;
    Parallel8Bit::readwrite = readwrite_;
    Parallel8Bit::enable = enable_;
    Parallel8Bit::bit_0 = bit_0_;
    Parallel8Bit::bit_1 = bit_1_;
    Parallel8Bit::bit_2 = bit_2_;
    Parallel8Bit::bit_3 = bit_3_;
    Parallel8Bit::bit_4 = bit_4_;
    Parallel8Bit::bit_5 = bit_5_;
    Parallel8Bit::bit_6 = bit_6_;
    Parallel8Bit::bit_7 = bit_7_;
    initialize();
    set_direction(GPIO_OUT);
    gpio_set_dir(Parallel8Bit::cs, GPIO_OUT);
    gpio_set_dir(Parallel8Bit::reset, GPIO_OUT);
    gpio_set_dir(Parallel8Bit::data_sel, GPIO_OUT);
    gpio_set_dir(Parallel8Bit::readwrite, GPIO_OUT);
    gpio_set_dir(Parallel8Bit::enable, GPIO_OUT);

    gpio_put(Parallel8Bit::enable, 0);
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

void Parallel8Bit::command(uint8_t c)
{
    gpio_put(Parallel8Bit::enable, 0);
    gpio_put(Parallel8Bit::data_sel, 0);
    gpio_put(Parallel8Bit::bit_0, c & 1);
    gpio_put(Parallel8Bit::bit_1, c & 2);
    gpio_put(Parallel8Bit::bit_2, c & 4);
    gpio_put(Parallel8Bit::bit_3, c & 8);
    gpio_put(Parallel8Bit::bit_4, c & 16);
    gpio_put(Parallel8Bit::bit_5, c & 32);
    gpio_put(Parallel8Bit::bit_6, c & 64);
    gpio_put(Parallel8Bit::bit_7, c & 128);
    gpio_put(Parallel8Bit::readwrite, 0);
    gpio_put(Parallel8Bit::enable, 1);
}

void Parallel8Bit::dataWrite(uint8_t c)
{
    gpio_put(Parallel8Bit::enable, 0);
    gpio_put(Parallel8Bit::data_sel, 1);
    gpio_put(Parallel8Bit::bit_0, c & 1);
    gpio_put(Parallel8Bit::bit_1, c & 2);
    gpio_put(Parallel8Bit::bit_2, c & 4);
    gpio_put(Parallel8Bit::bit_3, c & 8);
    gpio_put(Parallel8Bit::bit_4, c & 16);
    gpio_put(Parallel8Bit::bit_5, c & 32);
    gpio_put(Parallel8Bit::bit_6, c & 64);
    gpio_put(Parallel8Bit::bit_7, c & 128);
    gpio_put(Parallel8Bit::readwrite, 0);
    gpio_put(Parallel8Bit::enable, 1);
}

uint8_t Parallel8Bit::dataRead()
{
    gpio_put(Parallel8Bit::data_sel, 1);
    gpio_put(Parallel8Bit::readwrite, 1);
    gpio_put(Parallel8Bit::enable, 0);
    gpio_put(Parallel8Bit::enable, 1);
    Parallel8Bit::set_direction(GPIO_IN);
    // TODO make this not mess up at all
    uint8_t res = 0;
    res = res + 1 & gpio_get(Parallel8Bit::bit_0);
    res = res + 2 & gpio_get(Parallel8Bit::bit_1);
    res = res + 4 & gpio_get(Parallel8Bit::bit_2);
    res = res + 8 & gpio_get(Parallel8Bit::bit_3);
    res = res + 16 & gpio_get(Parallel8Bit::bit_4);
    res = res + 32 & gpio_get(Parallel8Bit::bit_5);
    res = res + 64 & gpio_get(Parallel8Bit::bit_6);
    res = res + 128 & gpio_get(Parallel8Bit::bit_7);
    Parallel8Bit::set_direction(GPIO_OUT);
    gpio_put(Parallel8Bit::enable, 0);
    return res;
}

void Parallel8Bit::set_cs(bool state)
{
    gpio_put(Parallel8Bit::cs, state);
}

void Parallel8Bit::set_reset(bool state)
{
    gpio_put(Parallel8Bit::reset, state);
}

void Parallel8Bit::set_data(bool state)
{
    gpio_put(Parallel8Bit::data_sel, state);
}

void Parallel8Bit::set_read(bool state)
{
    gpio_put(Parallel8Bit::readwrite, state);
}

void Parallel8Bit::set_enable(bool state)
{
    gpio_put(Parallel8Bit::enable, state);
}
