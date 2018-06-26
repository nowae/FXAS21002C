/******************************************************************************
 * FXAS21002C - C library for FXAS21002C device based on libohiboard
 * Copyright (C) 2018 nowae <http://www.nowae.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Author:
 *  Gianluca Calignano <g.calignano97@gmail.com>
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 ******************************************************************************/

#ifndef __NOWAE_FXAS21002C_REGISTER_H
#define __NOWAE_FXAS21002C_REGISTER_H

#ifndef __NO_BOARD_H
#include "board.h"
#endif

#define FXAS21002C_REG_STATUS              0x00
#define FXAS21002C_REG_OUT_X_MSB           0x01
#define FXAS21002C_REG_OUT_X_LSB           0x02
#define FXAS21002C_REG_OUT_Y_MSB           0x03
#define FXAS21002C_REG_OUT_Y_LSB           0x04
#define FXAS21002C_REG_OUT_Z_MSB           0x05
#define FXAS21002C_REG_OUT_Z_LSB           0x06
#define FXAS21002C_REG_DR_STATUS           0x07
#define FXAS21002C_REG_F_STATUS            0x08
#define FXAS21002C_REG_F_SETUP             0x09
#define FXAS21002C_REG_F_WHO_I_AM          0x0C
#define FXAS21002C_REG_CTRL_REG0           0x0D
#define FXAS21002C_REG_CTRL_REG1           0x13
#define FXAS21002C_REG_CTRL_REG2           0x14
#define FXAS21002C_REG_CTRL_REG3           0x15

#define FXAS21002C_WHO_I_AM_DEFAULT        0xD7

typedef union _FXAS21002C_Ctrl0
{
    uint8_t reg;
    struct
    {
        uint8_t FS                       : 2;
        uint8_t HPF_EN                   : 1;
        uint8_t SEL                      : 2;
        uint8_t SPIW                     : 1;
        uint8_t BW                       : 2;
    };
} FXAS21002C_Ctrl0;




#endif /* SOURCES_FXAS21002C_FXAS21002C_REGISTER_H_ */
