/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: psg_calc_envelope_period_ms.c                                      |
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
#include "libpsg.h"
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
static struct _data
{
  uint16_t uiSec;
  uint16_t uiMSec;
  uint32_t uiNum;
  uint32_t uiResult_s;
  uint32_t uiResult_ms;
} g_tData;

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
/* psg_calc_envelope_period_ms()                                              */
/*----------------------------------------------------------------------------*/
uint16_t psg_calc_envelope_period_ms(uint16_t uiTime /* ms */)
{
  g_tData.uiSec  = uiTime / UINT16_C(1000);   // 0 .. 65
  g_tData.uiMSec = uiTime - (g_tData.uiSec * UINT16_C(1000)); // 0 .. 999

  // Part 1: floor(PSG_CLOCK * s / 256)
  // PSG_CLOCK * s <= 1773447 * 65 = 115274055 (fits 32-bit)
  g_tData.uiResult_s = (((uint32_t) PSG_CLOCK) * ((uint32_t) g_tData.uiSec)) / ((uint32_t) PSG_PRESCALER_ENV);

  // Part 2: round(PSG_CLOCK * ms / (256*1000))
  // PSG_CLOCK * ms <= 1773447 * 999 = 1771673553 (fits 32-bit)
  const uint32_t uiDENOM = ((uint32_t) PSG_PRESCALER_ENV) * UINT32_C(1000); // 256000
  g_tData.uiNum       = ((uint32_t) PSG_CLOCK) * ((uint32_t) g_tData.uiMSec);
  g_tData.uiResult_ms = (g_tData.uiNum + (uiDENOM / 2)) / uiDENOM;         // +128000

  return (uint16_t) (g_tData.uiResult_s + g_tData.uiResult_ms);
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
