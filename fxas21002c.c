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

static void FXAS21002C_readRegister (FXAS21002C_DeviceHandle dev,
                                     uint8_t writeAddress,
                                     uint8_t readAddress,
                                     uint8_t registerAddress,
                                     uint8_t *data)
{
#if (NOWAE_FXAS21002C_DEVICE == 0)
    Iic_readRegister(dev->device,writeAddress,readAddress,registerAddress,data);
#elif (NOWAE_FXAS21002C_DEVICE == 1)

#endif
}

static void FXAS21002C_writeRegister (FXAS21002C_DeviceHandle dev,
                                      uint8_t writeAddress,
                                      uint8_t registerAddress,
                                      uint8_t data)
{
#if (NOWAE_FXAS21002C_DEVICE == 0)
    Iic_writeRegister(dev->device,writeAddress,registerAddress,data);
#elif (NOWAE_FXAS21002C_DEVICE == 1)

#endif
}

static void LIS2DW12_readMultipleRegister (FXAS21002C_DeviceHandle dev,
                                           uint8_t writeAddress,
                                           uint8_t readAddress,
                                           uint8_t firstRegisterAddress,
                                           uint8_t *data,
                                           uint8_t length)
{
#if (NOWAE_FXAS21002C_DEVICE == 0)
    Iic_readMultipleRegisters(dev->device,writeAddress,readAddress,firstRegisterAddress,data,length);
#elif (NOWAE_FXAS21002C_DEVICE == 1)

#endif
}

FXAS21002C_Errors FXAS21002C_init (FXAS21002C_DeviceHandle dev, FXAS21002C_Config config)
{
#if (NOWAE_FXAS21002C_DEVICE == 0)
    // Save I2C address
    if (config.address != 0)
    {
        dev->readAddr  = (config.address << 1) | 0x01;
        dev->writeAddr = (config.address << 1) & 0xFE;
    }
#elif NOWAE_FXAS21002C_DEVICE == 1
    dev->readAddr  = 0;
    dev->writeAddr = 0;
#endif

    // Check if the chip is correct
    uint8_t whoiam;
    FXAS21002C_readRegister(dev,dev->writeAddr,dev->readAddr,FXAS21002C_REG_F_WHO_I_AM,&whoiam);
    if (whoiam != FXAS21002C_WHO_I_AM_DEFAULT)
        return FXAS21002CERRORS_WRONG_REPLY;

    // Set the default status of the device...
    dev->status = FXAS21002CSTATUS_STANDBY;

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

    return FXAS21002CERRORS_NO_ERROR;
}

FXAS21002C_Errors FXAS21002C_setRange (FXAS21002C_DeviceHandle dev,
                                       FXAS21002C_FullScaleRange range)
{
    // Only during READY or STANDBY status the user can write CTRL0
    if (dev->status == FXAS21002CSTATUS_ACTIVE)
        return FXAS21002CERRORS_WRONG_STATUS;

    FXAS21002C_readRegister(dev,dev->writeAddr,dev->readAddr,FXAS21002C_REG_CTRL_REG0,&dev->reg.ctrl0.reg);
    // Set the correct bit field value
    dev->reg.ctrl0.FS = (range & 0x03);
    // write the updated value
    FXAS21002C_writeRegister(dev,dev->writeAddr,FXAS21002C_REG_CTRL_REG0,dev->reg.ctrl0.reg);

    return FXAS21002CERRORS_NO_ERROR;
}

FXAS21002C_Errors FXAS21002C_setDataRate (FXAS21002C_DeviceHandle dev,
                                          FXAS21002C_OutputDataRate odr)
{

}
