/*
$Id:$

NT7534 LCD library! (for GTK-281)

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

Henrik Pedersen - Ported to Raspberry Pi Pico
*/

#ifndef LIB_NT7534_H
#define LIB_NT7534_H

#include "pico/stdlib.h"
#include "./parallelInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <utility>

#define swap(a, b)         \
      {                    \
            uint8_t t = a; \
            a = b;         \
            b = t;         \
      }

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

// Commands see data sheet NT7534
#define CMD_DISPLAY_OFF 0xAE
#define CMD_DISPLAY_ON 0xAF
#define CMD_SET_DISP_START_LINE 0x40 // From 0x40 to 0x7F
#define CMD_SET_PAGE 0xB0
#define CMD_SET_COLUMN_UPPER 0x10
#define CMD_SET_COLUMN_LOWER 0x00
#define CMD_SET_ADC_NORMAL 0xA0
#define CMD_SET_ADC_REVERSE 0xA1
#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7
#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON 0xA5
#define CMD_SET_BIAS_9 0xA2
#define CMD_SET_BIAS_7 0xA3
#define CMD_SET_COM_NORMAL 0xC0
#define CMD_SET_COM_REVERSE 0xC8
#define CMD_SET_POWER_CONTROL 0x28
#define CMD_SET_RESISTOR_RATIO 0x20
#define CMD_SET_VOLUME_FIRST 0x81
#define CMD_SET_VOLUME_SECOND 0x00
#define CMD_SET_STATIC_OFF 0xAC
#define CMD_SET_STATIC_ON 0xAD
#define CMD_SET_STATIC_REG 0x00
#define CMD_SET_BOOSTER_FIRST 0xF8
#define CMD_SET_BOOSTER_234 0
#define CMD_SET_BOOSTER_5 1
#define CMD_SET_BOOSTER_6 3
#define CMD_RMW 0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET 0xE2
#define CMD_NOP 0xE3
// #define CMD_TEST 0xF0

class NT7534
{
public:
      NT7534(Parallel8Bit interface);

      void command(uint8_t c);
      void datawrite(uint8_t c);
      uint8_t dataread();
      void init(void);
      void begin(uint8_t contrast);
      void setbrightness(uint8_t val);
      void clear();
      void setall(void);
      void setpixel(uint8_t x, uint8_t y, uint8_t color);
      bool getpixel(uint8_t x, uint8_t y);
      void setbyte(uint8_t x, uint8_t p, uint8_t b);
      uint8_t getbyte(uint8_t x, uint8_t p);
      void drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
      void fillcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
      void drawcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color);
      void drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
      void fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

private:
      Parallel8Bit interface;
};

#endif
