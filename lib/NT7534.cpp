/* NT7534 LCD library! (for GTK-281)

Copyright (C) 2016 Guy WEILER www.weigu.lu

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

some of this code was written by <cstone@pobox.com> originally and
some of this code was written by Limor Fried, Adafruit Industries
it is in the public domain.

Ported to Raspberry Pi Pico by Henrik Pedersen in 2022
*/
#include "NT7534.h"

uint8_t is_reversed = 0;

// a handy reference to where the pages are on the screen
const uint8_t pagemap[] = {3, 2, 1, 0, 7, 6, 5, 4};

// a 5x7 font table
// const uint8_t font[0] = {};

NT7534::NT7534(Parallel8Bit interface): interface(std::move(interface))
{
    NT7534::interface = interface;
}

void NT7534::init(void)
{
    NT7534::interface.set_direction(GPIO_OUT);
    NT7534::interface.set_reset(0);
    sleep_ms(100);
    NT7534::interface.set_reset(1);
    sleep_ms(100);
    NT7534::interface.command(CMD_SET_BIAS_7);              // LCD bias select
    NT7534::interface.command(CMD_SET_ADC_NORMAL);          // ADC select
    NT7534::interface.command(CMD_SET_COM_NORMAL);          // SHL select
    NT7534::interface.command(CMD_SET_DISP_START_LINE);     // Initial display line
    NT7534::interface.command(CMD_SET_POWER_CONTROL | 0x4); // turn on voltage converter
    sleep_ms(50);                         // (VC=1, VR=0, VF=0)
    NT7534::interface.command(CMD_SET_POWER_CONTROL | 0x6); // turn on voltage regulator
    sleep_ms(50);                         // (VC=1, VR=1, VF=0)
    NT7534::interface.command(CMD_SET_POWER_CONTROL | 0x7); // turn on voltage follower
    sleep_ms(10);                         // (VC=1, VR=1, VF=1)
    NT7534::interface.command(CMD_SET_RESISTOR_RATIO | 0x6);
} // set lcd operating voltage

// Para:val (5 bit) from 0x01 (small) to 0x3F (large)
void NT7534::setbrightness(uint8_t val)
{
    NT7534::interface.command(CMD_SET_VOLUME_FIRST);
    NT7534::interface.command(CMD_SET_VOLUME_SECOND | (val & 0x3f));
}

void NT7534::begin(uint8_t contrast)
{
    NT7534::init();
    NT7534::interface.command(CMD_DISPLAY_ON);
    NT7534::interface.command(CMD_SET_ALLPTS_NORMAL);
    NT7534::setbrightness(contrast);
}

void NT7534::clear(void)
{
    uint8_t p, c;
    for (p = 0; p < 8; p++)
    {
        NT7534::interface.command(CMD_SET_PAGE | pagemap[p]);
        c = 0; // start at the beginning of the row
        NT7534::interface.command(CMD_SET_COLUMN_LOWER | ((c + 1) & 0x0f));
        NT7534::interface.command(CMD_SET_COLUMN_UPPER | (((c + 1) >> 4) & 0x0f));
        NT7534::interface.command(CMD_RMW);
        for (c = 0; c <= LCDWIDTH; c++)
        {
            NT7534::interface.dataWrite(0x00);
        }
        NT7534::interface.command(CMD_RMW_CLEAR);
    }
}

void NT7534::setall(void)
{
    uint8_t p, c;
    for (p = 0; p < 8; p++)
    {
        NT7534::interface.command(CMD_SET_PAGE | pagemap[p]);
        c = 0; // start at the beginning of the row
        NT7534::interface.command(CMD_SET_COLUMN_LOWER | ((c + 1) & 0x0f));
        NT7534::interface.command(CMD_SET_COLUMN_UPPER | (((c + 1) >> 4) & 0x0f));
        NT7534::interface.command(CMD_RMW);
        for (c = 0; c <= LCDWIDTH; c++)
        {
            NT7534::interface.dataWrite(0xFF);
        }
        NT7534::interface.command(CMD_RMW_CLEAR);
    }
}

void NT7534::setpixel(uint8_t x, uint8_t y, uint8_t color)
{
    if ((x > LCDWIDTH) || (y > LCDHEIGHT))
        return;
    uint8_t c = getbyte(x, y / 8);
    NT7534::interface.command(CMD_SET_PAGE | pagemap[y / 8]);
    NT7534::interface.command(CMD_SET_COLUMN_LOWER | ((x + 1) & 0xf));
    NT7534::interface.command(CMD_SET_COLUMN_UPPER | (((x + 1) >> 4) & 0xf));
    if (color)
        NT7534::interface.dataWrite(c | (0x80 >> (y % 8)));
    else
        NT7534::interface.dataWrite(c & ~(0x80 >> (y % 8)));
}

void NT7534::setbyte(uint8_t x, uint8_t p, uint8_t b)
{
    NT7534::interface.command(CMD_SET_PAGE | pagemap[p]);
    NT7534::interface.command(CMD_SET_COLUMN_LOWER | ((x + 1) & 0xf));
    NT7534::interface.command(CMD_SET_COLUMN_UPPER | (((x + 1) >> 4) & 0xf));
    NT7534::interface.dataWrite(b);
}

bool NT7534::getpixel(uint8_t x, uint8_t y)
{
    uint8_t c;
    NT7534::interface.command(CMD_SET_PAGE | pagemap[y / 8]);
    NT7534::interface.command(CMD_SET_COLUMN_LOWER | ((x + 1) & 0xf));
    NT7534::interface.command(CMD_SET_COLUMN_UPPER | (((x + 1) >> 4) & 0xf));
    c = NT7534::interface.dataRead(); // dummy read see datasheet
    c = NT7534::interface.dataRead();
    if ((c & ((0x80 >> (y % 8)))) == 0)
        return 0;
    else
        return 1;
}

uint8_t NT7534::getbyte(uint8_t x, uint8_t p)
{
    uint8_t c;
    NT7534::interface.command(CMD_SET_PAGE | pagemap[p]);
    NT7534::interface.command(CMD_SET_COLUMN_LOWER | ((x + 1) & 0xf));
    NT7534::interface.command(CMD_SET_COLUMN_UPPER | (((x + 1) >> 4) & 0xf));
    c = NT7534::interface.dataRead(); // dummy read see datasheet
    c = NT7534::interface.dataRead();
    return c;
}

void NT7534::drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{ // bresenham's algorithm - thx wikpedia
    uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep)
    {
        swap(x0, y0);
        swap(x1, y1);
    }
    if (x0 > x1)
    {
        swap(x0, x1);
        swap(y0, y1);
    }
    uint8_t dx, dy;
    dx = x1 - x0;
    dy = std::abs(y1 - y0);
    int8_t err = dx / 2;
    int8_t ystep;
    if (y0 < y1)
        ystep = 1;
    else
        ystep = -1;
    for (; x0 <= x1; x0++)
    {
        if (steep)
            NT7534::setpixel(y0, x0, color);
        else
            NT7534::setpixel(x0, y0, color);
        err -= dy;
        if (err < 0)
        {
            y0 += ystep;
            err += dx;
        }
    }
}

void NT7534::drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
    for (uint8_t i = x; i < x + w; i++)
    {
        NT7534::setpixel(i, y, color);
        NT7534::setpixel(i, y + h - 1, color);
    }
    for (uint8_t i = y; i < y + h; i++)
    {
        NT7534::setpixel(x, i, color);
        NT7534::setpixel(x + w - 1, i, color);
    }
}

void NT7534::fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
    for (uint8_t i = x; i < x + w; i++)
    {
        for (uint8_t j = y; j < y + h; j++)
            NT7534::setpixel(i, j, color);
    }
}

void NT7534::drawcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
    int8_t f = 1 - r;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * r;
    int8_t x = 0;
    int8_t y = r;
    NT7534::setpixel(x0, y0 + r, color);
    NT7534::setpixel(x0, y0 - r, color);
    NT7534::setpixel(x0 + r, y0, color);
    NT7534::setpixel(x0 - r, y0, color);
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        NT7534::setpixel(x0 + x, y0 + y, color);
        NT7534::setpixel(x0 - x, y0 + y, color);
        NT7534::setpixel(x0 + x, y0 - y, color);
        NT7534::setpixel(x0 - x, y0 - y, color);
        NT7534::setpixel(x0 + y, y0 + x, color);
        NT7534::setpixel(x0 - y, y0 + x, color);
        NT7534::setpixel(x0 + y, y0 - x, color);
        NT7534::setpixel(x0 - y, y0 - x, color);
    }
}

void NT7534::fillcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
    int8_t f = 1 - r;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * r;
    int8_t x = 0;
    int8_t y = r;
    for (uint8_t i = y0 - r; i <= y0 + r; i++)
        NT7534::setpixel(x0, i, color);
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        for (uint8_t i = y0 - y; i <= y0 + y; i++)
        {
            NT7534::setpixel(x0 + x, i, color);
            NT7534::setpixel(x0 - x, i, color);
        }
        for (uint8_t i = y0 - x; i <= y0 + x; i++)
        {
            NT7534::setpixel(x0 + y, i, color);
            NT7534::setpixel(x0 - y, i, color);
        }
    }
}
