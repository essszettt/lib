/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: mouse_read.c                                                       |
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
#include "libdrv.h"

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/

/*============================================================================*/
/*                               Constants                                    */
/*============================================================================*/

/*============================================================================*/
/*                               Variables                                    */
/*============================================================================*/
__sfr __banked __at 0xFBDF IO_KMOUSE_X;
__sfr __banked __at 0xFFDF IO_KMOUSE_Y;
__sfr __banked __at 0xFADF IO_KMOUSE_BTN;

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
Function to compute the signed difference between two unsigned values
@param uiCurr Current value
@param uiPrev Previous value
@return Signed delta of both values
*/
static int8_t mouse_delta(uint8_t uiCurr, uint8_t uiPrev) __z88dk_callee;

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* mouse_read()                                                               */
/*----------------------------------------------------------------------------*/
uint8_t mouse_read(mousestate_t* pState) __z88dk_fastcall
{
  /*
  0xFBDF Kempston mouse X
  (R)
  Returns the current x position of the mouse 0-255. The value wraps from 255 to
  0 on a right movement and from 0 to 255 on a left movement.

  0xFFDF Kempston mouse Y
  (R)
  Returns the current y position of the mouse 0-255. The value decrements and
  wraps from 0 to 255 on a downward movement and increments and wraps from 255
  to 0 on an upward movement.

  0xFADF Kempston mouse buttons
  (R)
  bits 7:4 = mouse wheel position 0-15, wraps
  bit 2 = 1 for middle button press
  bit 1 = 1 for left button press
  bit 0 = 1 for right button press
  */

  if (pState)
  {
    /* Update buttons and wheel */
    pState->tPriv.uiCurrX = ~IO_KMOUSE_BTN;
    pState->uiBtn = pState->tPriv.uiCurrX & 0x07; /* MAME sets BIT3 ?!*/
    pState->uiWhl = pState->tPriv.uiCurrX >> 4;   /* MAME sets constant 0x7 */

    /* Update position */
    pState->tPriv.uiCurrX = IO_KMOUSE_X;
    pState->tPriv.uiCurrY = IO_KMOUSE_Y;

    pState->iX += mouse_delta(pState->tPriv.uiCurrX, pState->tPriv.uiPrevX);   // right = +
    pState->iY += mouse_delta(pState->tPriv.uiCurrY, pState->tPriv.uiPrevY);   // up    = +

    pState->tPriv.uiPrevX = pState->tPriv.uiCurrX;
    pState->tPriv.uiPrevY = pState->tPriv.uiCurrY;

    return EOK;
  }

  return EINVAL;
}


/*----------------------------------------------------------------------------*/
/* mouse_delta()                                                              */
/*----------------------------------------------------------------------------*/
static int8_t mouse_delta(uint8_t uiCurr, uint8_t uiPrev) __z88dk_callee
{
  register uint8_t uiDelta = (uint8_t) (uiCurr - uiPrev);   // modulo 256
  return (uiDelta >= 128) ? (int8_t) (uiDelta - 256) : (int8_t) uiDelta;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
