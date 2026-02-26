/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: psg_internal.h                                                     |
| project:  ZX Spectrum Next - libdrv                                          |
| author:   S. Zell                                                            |
| date:     01/07/2026                                                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| description:                                                                 |
|                                                                              |
| Driver for programmable sound generators (AY-3-8912)                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| Copyright (c) 01/07/2026 STZ Engineering                                     |
|                                                                              |
| This software is provided  "as is",  without warranty of any kind, express   |
| or implied. In no event shall STZ or its contributors be held liable for any |
| direct, indirect, incidental, special or consequential damages arising out   |
| of the use of or inability to use this software.                             |
|                                                                              |
| Permission is granted to anyone  to use this  software for any purpose,      |
| including commercial applications,  and to alter it and redistribute it      |
| freely, subject to the following restrictions:                               |
|                                                                              |
| 1. Redistributions of source code must retain the above copyright            |
|    notice, definition, disclaimer, and this list of conditions.              |
|                                                                              |
| 2. Redistributions in binary form must reproduce the above copyright         |
|    notice, definition, disclaimer, and this list of conditions in            |
|    documentation and/or other materials provided with the distribution.      |
|                                                                          ;-) |
+-----------------------------------------------------------------------------*/

#if !defined(__PSG_INTERNAL_H__)
  #define __PSG_INTERNAL_H__

/*============================================================================*/
/*                               Includes                                     */
/*============================================================================*/
#include <stdint.h>
#include "libpsg.h"

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/

/*--- Registers of a PSG (AY-3-8912) -----------------------------------------*/
#define AY8912_REG_CHN_A_FINE (0) 
#define AY8912_REG_CHN_A_COARSE (AY8912_REG_CHN_A_FINE + 1)
#define AY8912_REG_CHN_B_FINE (2) 
#define AY8912_REG_CHN_B_COARSE (AY8912_REG_CHN_B_FINE + 1)
#define AY8912_REG_CHN_C_FINE (4) 
#define AY8912_REG_CHN_C_COARSE (AY8912_REG_CHN_C_FINE + 1)
#define AY8912_REG_NOISE_PERIOD (6)
#define AY8912_REG_MIXER (7)
#define AY8912_REG_CHN_A_AMPL (8) 
#define AY8912_REG_CHN_B_AMPL (9) 
#define AY8912_REG_CHN_C_AMPL (10) 
#define AY8912_REG_ENV_FINE (11) 
#define AY8912_REG_ENV_COARSE (AY8912_REG_ENV_FINE + 1)
#define AY8912_REG_ENV_SHAPE (13) 
#define AY8912_REG_GPIO_A (14) /* not used */ 
#define AY8912_REG_GPIO_B (15) /* not used */

/*!
There seems to be a problem reading back the values of the registers from the
AY-8912 ... no idea why (assembler looks fine) ?
If this macro is set, all register values are latched within the device
structure. If we read back a value, we use it from the latch, not from the real
hardware ...
If this macro is "unset", we read the values from hardware ... 
*/
#define __PSG_USE_REG_LATCH__

/*============================================================================*/
/*                               Constants                                    */
/*============================================================================*/

/*============================================================================*/
/*                               Variables                                    */
/*============================================================================*/
/*!
IO-Port (register) to read the currently selected PSG and register
@code
BIT[7:6]  Selected PSG
          0b01 = PSG2
          0b10 = PSG1
          0b11 = PSG0
BIT[5]    reserved
BIT[4:0]  Selected PSG-register (0 .. 15)
@endcode
*/
__sfr __banked __at 0xBFF5 IO_PSG_SEL;

/*============================================================================*/
/*                               Structures                                   */
/*============================================================================*/

/*============================================================================*/
/*                               Typ-Definitions                              */
/*============================================================================*/

/*============================================================================*/
/*                               Prototypes                                   */
/*============================================================================*/
/*!
Write value to a register of a PSG (AY-3-8912).
@param pState Poiter to device structure
@param uiReg  Index of the register to write
@param uiValue Value to set
@remark
The index of the PSG (Turbosound, 3 x AY-3-8912) is taken from the device
structure ("0" = first AY-3-8912, "1" = second AY-3-8912, ..)
*/
void psg_write_reg(psgstate_t* pState, uint8_t uiReg, uint8_t uiValue);

/*!
Read value from a register of a PSG (AY-3-8912).
@param pState Poiter to device structure
@param uiReg  Index of the register to read
@return Current value of the register
@remark
The index of the PSG (Turbosound, 3 x AY-3-8912) is taken from the device
structure ("0" = first AY-3-8912, "1" = second AY-3-8912, ..)
*/
uint8_t psg_read_reg(psgstate_t* pState, uint8_t uiReg);

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

#endif /* __PSG_INTERNAL_H__ */
