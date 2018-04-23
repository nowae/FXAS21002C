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

/******************************************************************************
 * @mainpage FXAS21002C - C library for FXAS21002C device based on @a libohiboard
 *
 * @section changelog ChangeLog
 *
 * @li v1.0.0 of 2018/03/xx - Initial version
 *
 * @section library External Library
 *
 * The library use the following external library
 * @li libohiboard https://github.com/ohilab/libohiboard a C framework for
 * NXP Kinetis microcontroller
 * @li cli https://github.com/Loccioni-Electronic/cli Small library for a simple
 * command line interface based on microcontroller UART
 *
 *
 ******************************************************************************/

#ifndef __NOWAE_FXAS21002C_H
#define __NOWAE_FXAS21002C_H

#ifndef __NO_BOARD_H
#include "board.h"
#endif

#define NOWAE_FXAS21002C_LIBRARY_VERSION     "1.0.0"
#define NOWAE_FXAS21002C_LIBRARY_VERSION_M   1
#define NOWAE_FXAS21002C_LIBRARY_VERSION_m   0
#define NOWAE_FXAS21002C_LIBRARY_VERSION_bug 0
#define NOWAE_FXAS21002C_LIBRARY_TIME        0

/**
 * This define must be init with one of the following value:
 *   0 - I2C
 *   1 - SPI
 */
#if !defined(NOWAE_FXAS21002C_DEVICE)
#error "You must define the correct peripheripal type to manage the device!"
#endif

#if (NOWAE_FXAS21002C_DEVICE == 0)
typedef enum _FXAS21002C_Address
{
    FXAS21002CADDRESS_0x20 = 0x20,
    FXAS21002CADDRESS_0x21 = 0x21,

} FXAS21002C_Address;
#endif

/**
 *
 */
typedef struct _FXAS21002C_Device
{

#if (NOWAE_FXAS21002C_DEVICE == 0)

    Iic_DeviceHandle device;

    uint8_t readAddr;
    uint8_t writeAddr;

#elif (NOWAE_FXAS21002C_DEVICE == 1)

#endif

} FXAS21002C_Device, *FXAS21002C_DeviceHandle;

typedef struct _FXAS21002C_Config
{

#if (NOWAE_FXAS21002C_DEVICE == 0)

    FXAS21002C_Address address;

#elif (NOWAE_FXAS21002C_DEVICE == 1)

#endif

} FXAS21002C_Config;

/**
 *
 */
typedef enum _FXAS21002C_Errors
{
    FXAS21002CERRORS_NO_ERROR,
    FXAS21002CERRORS_WRONG_REPLY,
} FXAS21002C_Errors;

/**
 *
 * The unit is degree per second.
 */
typedef enum _FXAS21002C_FullScaleRange
{
    FXAS21002CFULLSCALERANGE_2000,
    FXAS21002CFULLSCALERANGE_1000,
    FXAS21002CFULLSCALERANGE_500,
    FXAS21002CFULLSCALERANGE_250,

} FXAS21002C_FullScaleRange;

/**
 *
 * The unit is Hertz
 */
typedef enum _FXAS21002C_OutputDataRate
{
    FXAS21002COUTPUTDATARATE_12_5,
    FXAS21002COUTPUTDATARATE_25,
    FXAS21002COUTPUTDATARATE_50,
    FXAS21002COUTPUTDATARATE_100,
    FXAS21002COUTPUTDATARATE_200,
    FXAS21002COUTPUTDATARATE_400,
    FXAS21002COUTPUTDATARATE_800,

} FXAS21002C_OutputDataRate;

/**
 *
 */
FXAS21002C_Errors FXAS21002C_init (FXAS21002C_DeviceHandle dev,
                                   FXAS21002C_Config config);

/**
 *
 */
FXAS21002C_Errors FXAS21002C_getValues (FXAS21002C_DeviceHandle dev,
                                        int16_t* axisX,
                                        int16_t* axisY,
                                        int16_t* axisZ);

#if (NOWAE_FXAS21002C_DEBUG == 1)

#include "cli/cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FXAS21002C_cliParser (void* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE]);

#endif // (NOWAE_FXAS21002C_DEBUG == 1)

#endif // __NOWAE_FXAS21002C_H
