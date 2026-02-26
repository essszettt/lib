/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: psg_write_reg.c                                                    |
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

/*============================================================================*/
/*                               Includes                                     */
/*============================================================================*/
#include <stdint.h>
#include <arch/zxn.h>
#include "libdrv.h"
#include "psg_internal.h"

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/

/*============================================================================*/
/*                               Constants                                    */
/*============================================================================*/

/*============================================================================*/
/*                               Variables                                    */
/*============================================================================*/

/*============================================================================*/
/*                               Structures                                   */
/*============================================================================*/

/*============================================================================*/
/*                               Typ-Definitions                              */
/*============================================================================*/

/*============================================================================*/
/*                               Prototypes                                   */
/*============================================================================*/

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* psg_write_reg()                                                            */
/*----------------------------------------------------------------------------*/
void psg_write_reg(psgstate_t* pState, uint8_t uiReg, uint8_t uiValue)
{
  if (pState)
  {
    /*
    BIT[7]	  Must be "1"
    BIT[6]	  Enable left audio
    BIT[5]    Enable right audio
    BIT[4:2]	Must be "1"
    BIT[1:0]	Select active chip. 0-3: unused, AY3, AY2, AY1.

    PSG0 = 3 : idx 0 => 4 - (idx + 1) = 3
    PSG1 = 2 : idx 1 => 4 - (idx + 1) = 2
    PSG2 = 1 : idx 2 => 4 - (idx + 1) = 1
    NONE = 0 : idx 3 => 4 - (idx + 1) = 0
    */

    IO_TURBOSOUND = 0xFC | (4 - ((pState->uiIndex & 0x03) + 1));
    IO_AY_REG = uiReg;
    IO_AY_DAT = uiValue;

   #if defined(__PSG_USE_REG_LATCH__)
    pState->uiReg[uiReg] = uiValue;
   #endif
  }
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
