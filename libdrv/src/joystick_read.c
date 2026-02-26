/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: joystick_read.c                                                    |
| project:  ZX Spectrum Next - libdrv                                          |
| author:   S. Zell                                                            |
| date:     01/05/2026                                                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| description:                                                                 |
|                                                                              |
| Driver for joystick-/gamepad-devices                                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| Copyright (c) 01/05/2026 STZ Engineering                                     |
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
#include <errno.h>
#include "libzxn.h"
#include "libdrv.h"

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/
/*!
Number of NREG to read the state of the buttons of a MegaDrive-controller
*/
#define REG_EXT_MD_PAD_BTN (0xB2)

/*============================================================================*/
/*                               Constants                                    */
/*============================================================================*/

/*============================================================================*/
/*                               Variables                                    */
/*============================================================================*/
__sfr __at 0x1F IO_KJOYSTICK0;
__sfr __at 0x37 IO_KJOYSTICK1;

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
/* joystick_read()                                                            */
/*----------------------------------------------------------------------------*/
uint8_t joystick_read(joystickstate_t* pState) __z88dk_fastcall
{
  if (pState)
  {
    /*
    Kempston IO-Ports (0x1F / 0x37):

    BIT0  DIR-RIGHT
    BIT1  DIR-LEFT
    BIT2  DIR-DOWN
    BIT3  DIR-UP
    BIT4  BTN-B
    BIT5  BTN-C
    BIT6  BTN-A
    BIT7  BTN-START

    NEXTREG 0xB2 (178) - Extended MD Pad Buttons (3.01.10):

    BIT0  BTN-MODE  (left)
    BIT1  BTN-Y     (left)
    BIT2  BTN-Z     (left)
    BIT3  BTN-X     (left)
    BIT4  BTN-MODE  (right)
    BIT5  BTN-Y     (right)
    BIT6  BTN-Z     (right)
    BIT7  BTN-X     (right)
    */

    switch (pState->uiIndex)
    {
      case 0:
        pState->uiScratch = IO_KJOYSTICK0;
        pState->uiBtn     = (ZXN_READ_REG(REG_EXT_MD_PAD_BTN) & 0x0F) << 4; 
        break;

      case 1:
        pState->uiScratch = IO_KJOYSTICK1;
        pState->uiBtn     = (ZXN_READ_REG(REG_EXT_MD_PAD_BTN) & 0xF0); 
        break;

      default:
        return ERANGE;
    }

    pState->uiDir  = pState->uiScratch & 0x0F;
    pState->uiBtn |= pState->uiScratch >> 4;

    return EOK;
  }

  return EINVAL;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
