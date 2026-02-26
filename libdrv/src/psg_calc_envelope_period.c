/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: psg_calc_envelope_period.c                                         |
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
/* psg_calc_envelope_period()                                                 */
/*----------------------------------------------------------------------------*/
uint16_t psg_calc_envelope_period(uint16_t uiFrequency)
{
  if (uiFrequency)
  {
    uint32_t uiFreq = ((uint32_t) (PSG_PRESCALER_ENV)) * ((uint32_t) uiFrequency);
    return ((((uint32_t) PSG_CLOCK) + (uiFreq >> 1)) / uiFreq);
  }

  return 0;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
