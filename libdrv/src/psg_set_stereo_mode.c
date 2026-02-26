/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: psg_set_stereo_mode.c                                              |
| project:  ZX Spectrum Next - libdrv                                          |
| author:   S. Zell                                                            |
| date:     01/16/2026                                                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| description:                                                                 |
|                                                                              |
| Driver for programmable sound generators (AY-3-8912)                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| Copyright (c) 01/16/2026 STZ Engineering                                     |
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
#include <arch/zxn.h>
#include "libpsg.h"

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
/* psg_set_stereo_mode()                                                      */
/*----------------------------------------------------------------------------*/
uint8_t psg_set_stereo_mode(uint8_t uiMode) __z88dk_fastcall
{
  if (0x01 >= uiMode)
  {
    register uint8_t uiScratch;
    uiScratch  = ZXN_READ_REG(REG_PERIPHERAL_3);
    uiScratch &= ~(1 << 5);
    uiScratch |= (uiMode << 5);
    ZXN_WRITE_REG(REG_PERIPHERAL_3, uiScratch);
    return EOK;
  }

  return EINVAL;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
