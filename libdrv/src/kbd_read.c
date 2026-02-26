/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: kbd_read.c                                                         |
| project:  ZX Spectrum Next - libdrv                                          |
| author:   S. Zell                                                            |
| date:     02/02/2026                                                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| description:                                                                 |
|                                                                              |
| Driver for the keyboard                                                      |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| Copyright (c) 02/02/2026 STZ Engineering                                     |
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
#include <z80.h> 
#include <errno.h>
#include "libkbd.h"

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
/*                               Type-Definitions                             */
/*============================================================================*/

/*============================================================================*/
/*                               Prototypes                                   */
/*============================================================================*/

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* kbd_read()                                                                 */
/*----------------------------------------------------------------------------*/
uint8_t kbd_read(kbdstate_t* pState) _KBD_FASTCALL
{
/*
@code
+--------+-------+-------------------+----------+-----+-----+-----+-----+-----+
| PORT   | DEC.   | BINARY           | ADDRLINE | D0  | D1  | D2  | D3  | D4  |
+--------+-------+-------------------+----------+-----+-----+-----+-----+-----+
| 0xFEFE | 65278 | 11111110 11111110 | A8       | CSH |  Z  |  X  |  C  |  V  |
| 0xFDFE | 65022 | 11111101 11111110 | A9       |  A  |  S  |  D  |  F  |  G  |
| 0xFBFE | 64510 | 11111011 11111110 | A10      |  Q  |  W  |  E  |  R  |  T  |
| 0xF7FE | 63486 | 11110111 11111110 | A11      |  1  |  2  |  3  |  4  |  5  |
| 0xEFFE | 61438 | 11101111 11111110 | A12      |  0  |  9  |  8  |  7  |  6  |
| 0xDFFE | 57342 | 11011111 11111110 | A13      |  P  |  O  |  I  |  U  |  Y  |
| 0xBFFE | 49150 | 10111111 11111110 | A14      | ENT |  L  |  K  |  J  |  H  |
| 0x7FFE | 32766 | 01111111 11111110 | A15      | SPC | SSH |  M  |  N  |  B  |
+--------+-------+-------------------+----------+-----+-----+-----+-----+-----+
@endcode
*/

  if (pState)
  {
    /* Reading raw state of the keyboard */
    for (uint8_t i = 0; i < uiMAX_KBDROWS; ++i)
    {
      pState->tPriv.uiAddr   = ~(UINT8_C(1) << i);
      pState->tPriv.uiAddr <<= 8;
      pState->tPriv.uiAddr  |= UINT8_C(0xFE);
      pState->tRows.uiRaw8[i] = ~z80_inp(pState->tPriv.uiAddr);
    }

    /* Detect key events */
    for (uint8_t i = 0; i < uiMAX_KBDROWS; ++i)
    {
      if (pState->tRows.uiRaw8[i] != pState->tPriv.tRows.uiRaw8[i])
      {
        pState->tPriv.uiScratch  = pState->tPriv.tRows.uiRaw8[i] ^ pState->tRows.uiRaw8[i];
        pState->tPriv.uiPressed  = pState->tRows.uiRaw8[i]       & pState->tPriv.uiScratch;
        pState->tPriv.uiReleased = pState->tPriv.tRows.uiRaw8[i] & pState->tPriv.uiScratch;

        while (pState->tPriv.uiPressed)
        {
          pState->tPriv.uiPressed >>= 1;
        }

        while (pState->tPriv.uiReleased)
        {
          pState->tPriv.uiReleased >>= 1;
        }
      }
    }

    /* Save raw state of the keyboard */
    for (uint8_t i = 0; i < (uiMAX_KBDROWS / sizeof(uint16_t)); ++i)
    {
      pState->tPriv.tRows.uiRaw16[i] = pState->tRows.uiRaw16[i];
    }

    return EOK;
  }

  return EINVAL;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
