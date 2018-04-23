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

#include "fxas21002c.h"

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
#define FXAS21002C_REG_CTRL_REG1           0x13
#define FXAS21002C_REG_CTRL_REG2           0x14
#define FXAS21002C_REG_CTRL_REG3           0x15

FXAS21002C_Errors FXAS21002C_init (FXAS21002C_DeviceHandle dev, FXAS21002C_Config config)
{
#if (NOWAE_FXAS21002C_DEVICE == 0)

    // Save I2C address
    if (config.address != 0)
    {
        dev->readAddr  = (config.address << 1) | 0x01;
        dev->writeAddr = (config.address << 1) & 0xFE;
    }

    uint8_t whoiam;
    Iic_readRegister(dev->device,dev->writeAddr,dev->readAddr,FXAS21002C_REG_F_WHO_I_AM,&whoiam);
    if (whoiam != 0xD7)
        return FXAS21002CERRORS_WRONG_REPLY;

    Iic_writeRegister(dev->device,dev->writeAddr,FXAS21002C_REG_CTRL_REG1,0x02);

#elif NOWAE_FXAS21002C_DEVICE == 1

#endif

    return FXAS21002CERRORS_NO_ERROR;
}

FXAS21002C_Errors FXAS21002C_getValues (FXAS21002C_DeviceHandle dev,
                                        int16_t* axisX,
                                        int16_t* axisY,
                                        int16_t* axisZ)
{
    uint8_t values[6];

    Iic_readMultipleRegisters(dev->device,dev->writeAddr,dev->readAddr,FXAS21002C_REG_OUT_X_MSB,values,6);

    *axisX  = values[0];
    *axisX  = *axisX << 8;
    *axisX |= values[1];

    *axisY  = values[2];
    *axisY  = *axisY << 8;
    *axisY |= values[3];

    *axisZ  = values[4];
    *axisZ  = *axisZ << 8;
    *axisZ |= values[5];

    return
}
