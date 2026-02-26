/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: libpsg.h                                                           |
| project:  ZX Spectrum Next - libpsg                                          |
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

#if !defined(__LIBPSG_H__)
  #define __LIBPSG_H__

/*============================================================================*/
/*                               Includes                                     */
/*============================================================================*/

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/
/*!
This macro describes the basic clock frequency of the CPU [Hz].
(checked with Korg GA-50: A4 = 440 Hz)
*/
#define PSG_CLOCK_CPU (3500000) /* __CPU_CLOCK */

/*!
This macro describes the basic clock frequency used by the sound generators
in [Hz] (typically "CPU clock / 2").
*/
#define PSG_CLOCK (PSG_CLOCK_CPU / 2)

/*!
Prescaler of the tone generators.
*/
#define PSG_PRESCALER_FREQ (16)

/*!
Prescaler of the noise generator
*/
#define PSG_PRESCALER_NOISE (PSG_PRESCALER_FREQ)

/*!
Prescaler of the envelope generators
*/
#define PSG_PRESCALER_ENV (256)

#define PSG_FREQ_C4  (262)
#define PSG_FREQ_DB4 (277)
#define PSG_FREQ_D4  (294)
#define PSG_FREQ_EB4 (311)
#define PSG_FREQ_E4  (330)
#define PSG_FREQ_F4  (349)
#define PSG_FREQ_GB4 (370)
#define PSG_FREQ_G4  (392)
#define PSG_FREQ_AB4 (415)
#define PSG_FREQ_A4  (440)
#define PSG_FREQ_BB4 (466)
#define PSG_FREQ_B4  (494)
#define PSG_FREQ_C5  (PSG_FREQ_C4 * 2)

/*!
This macro describes sound core, that should be used: YM2149F
(used with "psg_set_core")
*/
#define PSG_CORE_YM (0x00)

/*!
This macro describes sound core, that should be used: AY-3-8912
(used with "psg_set_core")
*/
#define PSG_CORE_AY (0x01)

/*!
This macro describes sound core, that should be used: ZXN-8950 (3.02.00)
(used with "psg_set_core")
*/
#define PSG_CORE_ZX (0x02)

/*!
This macro describes sound core, that should be used: Hold all AY in RESET
(used with "psg_set_core")
*/
#define PSG_CORE_RST (0x03)

#define PSG_MODE_SINGLE   (0)   /* psg_set_mode */
#define PSG_MODE_MULTIPLE (1)   /* psg_set_mode */

#define PSG_STEREO_ABC (0)      /* psg_set_stereo_mode */
#define PSG_STEREO_ACB (1)      /* psg_set_stereo_mode */

#define PSG_CHANNEL_A (0)       /* psg_open, ... */
#define PSG_CHANNEL_B (1)       /* psg_open, ... */
#define PSG_CHANNEL_C (2)       /* psg_open, ... */

#define PSG_MODE_STEREO (0)     /* psg_set_mono_mode */
#define PSG_MODE_MONO   (1)     /* psg_set_mono_mode */

#define PSG_AMPL_ENVELOPE (0x10)

#define PSG_MIXER_TONE_A  (1 << PSG_CHANNEL_A)  /* Tone on channel A */
#define PSG_MIXER_TONE_B  (1 << PSG_CHANNEL_B)  /* Tone on channel B */
#define PSG_MIXER_TONE_C  (1 << PSG_CHANNEL_C)  /* Tone on channel C */
#define PSG_MIXER_NOISE_A (1 << 3)              /* Noise on channel A */
#define PSG_MIXER_NOISE_B (1 << 4)              /* Noise on channel B */
#define PSG_MIXER_NOISE_C (1 << 5)              /* Noise on channel C */

#define PSG_ENV_SHAPE_HOLD      (1 << 0)
#define PSG_ENV_SHAPE_ALTERNATE (1 << 1)
#define PSG_ENV_SHAPE_ATTACK    (1 << 2)
#define PSG_ENV_SHAPE_CONTINUE  (1 << 3)

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
/*!
This structure is used to manage and read the state of a programmable sound
generator (AY-3-8912)
*/
typedef struct _psgstate
{
  /*!
  Index of the opened sound generator:
  - "0" = first AY-3-8912
  - "1" = second AY-3-8912
  - "2" = third AY-3-8912
  */
  uint8_t uiIndex;

  /*!
  Internal buffer for calculations
  */
  uint8_t uiScratch;

  /*!
  Buffer for the contents of all registers of AY-3-8912 (used in tracker-mode)
  */
  uint8_t uiReg[16];
} psgstate_t;

/*============================================================================*/
/*                               Prototypes                                   */
/*============================================================================*/

/*!
There are two slightly different sound generators implementied in the core:
  - YM2149F
  - AY-3-8912
Both generators are compatible but sound slightly different.
With this function, the active implementation can be selected globally.
@code
psg_set_core(PSG_CORE_AY);
@endcode
@param uiCore Soundcore to acivate: "0" = YM2149F, "1" = AY-3-8912
return EOK = no error
*/
uint8_t psg_set_core_fastcall(uint8_t uiCore) __z88dk_fastcall;
#define psg_set_core(x) psg_set_core_fastcall(x)

/*!
This function return the current selected sound core.
@return Current setting
*/
uint8_t psg_get_core_fastcall(void) __z88dk_fastcall;
#define psg_get_core() psg_get_core_fastcall()

/*!
With this function the additional PSGs can be enabled or disabled (see NREG 0x05).
@code
  psg_set_mode(PSG_MODE_MULTIPLE);
@endcode

@param uiMode If set to "1", all PSGs are enabled; if set to "0", multiple PSGs
are disabled (only one PSG, like with 128K/+2/+3).
@return EOK = no error
*/
uint8_t psg_set_mode_fastcall(uint8_t uiMode) __z88dk_fastcall;
#define psg_set_mode(x) psg_set_mode_fastcall(x)

/*!
This function returns the curretn setting, if multiple PSGs are enabled or just
a single PSG.
@return Current setting: "0" = only one PSG enabled; "1" = all PSGs enabled
*/
uint8_t psg_get_mode_fastcall(void) __z88dk_fastcall;
#define psg_get_mode() psg_get_mode_fastcall()

/*!
Set the stereo-mode of the system (global setting for all PSGs): ABC or ACB
  - ABC: A=left, B=middle, C=right
  - ACB: A=left, C=middle, B=right
@code
  psg_set_stereo_mode(PSG_STEREO_ABC);
@endcode
@param uiMode Mode to set: "0" = ABC, "1" = ACB
@return EOK = no error
*/
uint8_t psg_set_stereo_mode_fastcall(uint8_t uiMode) __z88dk_fastcall;
#define psg_set_stereo_mode(x) psg_set_stereo_mode_fastcall(x)

/*!
This function opens and initializes a connection to a PSG.
@code
 EXAMPLE
=========

psgstate_t tSound0;
// --- global settings -----------------
psg_set_core(PSG_CORE_AY);                      // enable AY-3-8912 emulation
psg_set_mode(PSG_MODE_MULTIPLE);                           // enable all PSGs
psg_set_stereo_mode(PSG_STEREO_ABC);                // all PSGs to stereo ABC
// --- sound generator settings --------
psg_open(&tSound0, 0);                                           // open PSG0
psg_set_mono_mode(&tSound0, PSG_MODE_STEREO);           // set PSG0 to STEREO
psg_set_period(&tSound0, PSG_CHANNEL_A, psg_calc_tone_period(PSG_FREQ_C4));
psg_set_period(&tSound0, PSG_CHANNEL_B, psg_calc_tone_period(PSG_FREQ_E4));
psg_set_period(&tSound0, PSG_CHANNEL_C, psg_calc_tone_period(PSG_FREQ_G4));
psg_set_amplitude(&tSound0, PSG_CHANNEL_A, 15);    // set max. amplitude ChnA
psg_set_amplitude(&tSound0, PSG_CHANNEL_B, 15);    // set max. amplitude ChnB
psg_set_amplitude(&tSound0, PSG_CHANNEL_C, 15);    // set max. amplitude ChnC
psg_set_mixer(&tSound0, PSG_CHANNEL_A | PSG_CHANNEL_B | PSG_CHANNEL_C);
zxn_sleep_ms(5000);                                       // do some work ;-)
psg_set_mixer(&tSound0, 0);                  // disable all channels in mixer
psg_close(&tSound0);                                            // close PSG0
@endcode

@code
 AY-3-8912 REGISTERS
=====================

+---------+--------------------------------------------------------------------+
| REGIDX  | FUNCTION                                                           |
+---------+--------------------------------------------------------------------+
| 0	      | Channel A Fine Tune                                     [LLLLLLLL] |
+---------+--------------------------------------------------------------------+
| 1	      | Channel A Coarse Tune (4 bits)                          [----HHHH] |
+---------+--------------------------------------------------------------------+
| 2       | Channel B Fine Tune                                                |
+---------+--------------------------------------------------------------------+
| 3	      | Channel B Coarse Tune (4 bits)                                     |
+---------+--------------------------------------------------------------------+
| 4	      | Channel C Fine Tune                                                |
+---------+--------------------------------------------------------------------+
| 5	      | Channel C Coarse Tune (4 bits)                                     |
+---------+--------------------------------------------------------------------+
| 6	      | Noise Period (5 bits)                                   [---LLLLL] |
+---------+--------------------------------------------------------------------+
| 7	      | Tone enable flags.                                                 |
|         | Bits 0-2 enable tone on channels A, B, C respectively, but are     |
|         | inverted - 0 is enabled.                                           |
|         | Bits 3-5 enable noise on A, B, C are likewise inverted. [--NNNTTT] |
+---------+--------------------------------------------------------------------+
| 8	      | Channel A amplitude.                                               |
|         | Bits 0-3 set the fixed amplitude which is used if bit 4 is 0. If   |
|         | bit 4 is 1, the envelope generator is used instead, and bits 0-3   |
|         | are ignored.                                            [---EAAAA] |
+---------+--------------------------------------------------------------------+
| 9       | Channel B amplitude, same as above.                     [---EAAAA] |
+---------+--------------------------------------------------------------------+
| 10      | Channel C amplitude, same as above.                     [---EAAAA] |
+---------+--------------------------------------------------------------------+
| 11      | Envelope period fine.                                   [LLLLLLLL] |
+---------+--------------------------------------------------------------------+
| 12      | Envelope period coarse.                                 [HHHHHHHH] |
+---------+--------------------------------------------------------------------+
| 13      | Envelope shape.                                                    |
|         | Bits 0-3 alter the behaviour of the envelope generator:            |
|         | BIT0: "Hold"; If 1 the envelope generator performs one cycle then  |
|         |       holds at the end value. If 0, it cycles continuously.        |
|         | BIT1: "Alternate"; If 1 the envelope generator alters direction    |
|         |       after each cycle. If 0, it resets after each cycle. If Hold  |
|         |       is set, this instead chooses if the value held is the final  |
|         |       value (0) or the initial value (1).                          |
|         | BIT2: "Attack"; if 1 the generator counts up. If 0 the generator   |
|         |       counts down.                                                 |
|         | BIT3: "Continue"; if 0, the envelope generator performs one cycle  |
|         |       then drops amplitude to 0 and stays there, overriding Hold.  |
|         |       If 1, Hold is followed.                           [----CAAH] |
+---------+--------------------------------------------------------------------+
@endcode
@param pState Pointer to device structure (initialized with "psg_open")
@param uiIndex Index of the PSG ("0" .. "2")
@return EOK = no error
*/
uint8_t psg_open(psgstate_t* pState, uint8_t uiIndex);

/*!
Set on of the PSGs to mono- or stereo-mode.
@code
  psgstate_t tState;
  psg_open(&tState, 0);
  psg_set_mono_mode(&tState, PSG_MODE_MONO);
  ...
  psg_close(&tState);
@endcode
@param pState Pointer to device structure
@param uiMode Mode to set: "0" = stereo, "1" = mono
*/
uint8_t psg_set_mono_mode(psgstate_t* pState, uint8_t uiMode);

/*!
Calculate the period value for a channel of the PSG from a given frequency.
@param uiFrequency Frequency of the tone in [Hz]
@return Period value for a channel of the PSG 
*/
uint16_t psg_calc_tone_period(uint16_t uiFrequency);

/*!
Set the period of the requested tone on a tone channel of the PSG.
@param pState Pointer to device structure
@param uiChannel Index of the channel to set ("0" = A, "1" = B, "2" = C)
@param uiPeriod Period of the requested tone  
@return EOK = no error
@remark
  period = f_clock / (16 * f_tone)
  f_clock = 1773447 [Hz]
*/
uint8_t psg_set_tone_period(psgstate_t* pState, uint8_t uiChannel, uint16_t uiPeriod);

/*!
Set amplitude of the specified channel.
@param pState Pointer to device structure
@param uiChannel Index of the channel to set ("0" = A, "1" = B, "2" = C)
@param uiAmplitude Amplitude to set (0 .. 15 or PSG_AMPL_ENVELOPE to use
                   the envelope generator)
@return EOK = no error
*/
uint8_t psg_set_amplitude(psgstate_t* pState, uint8_t uiChannel, uint8_t uiAmplitude);

/*!
Calculates the period value for the noise generator from a given frequency.
@param uiFrequency Frequency of the noise updates (3578 .. 110937 [Hz])
@return Period value for the noise generator ("1" .. "31") 
*/
uint8_t psg_calc_noise_period(uint16_t uiFrequency);

/*!
Set the period of the noise generator of the PSG.
@param pState Pointer to device structure
@param uiPeriod Period of the noise  
@return EOK = no error
@remark
period = f_clock / (16 * f_noise)
f_clock = 1773447 [Hz]
*/
uint8_t psg_set_noise_period(psgstate_t* pState, uint8_t uiPeriod);

/*!
Read the current value of the mixer of the PSG.
@param pState Pointer to device structure
@return Current value of the mixer register
*/
uint8_t psg_get_mixer(psgstate_t* pState) __z88dk_fastcall;

/*!
Set the value of the mixer register of the PSG
@param pState Pointer to device structure
@param uiMixer Setting of the register: 0b0|0|NC|NB|NA|TC|TB|TA
@return EOK = no error
*/
uint8_t psg_set_mixer(psgstate_t* pState, uint8_t uiMixer);

/*!
Calculate the period value for the envelope generator of the PSG from a given
frequency.
@param uiFrequency Frequency for the generator (0 .. 6933 [Hz])
@return Period value for envelope generator of the PSG 
*/
uint16_t psg_calc_envelope_period(uint16_t uiFrequency);

/*!
Calculate the period value for the envelope generator of the PSG from a given
period time in [ms].
@param uiTime Period time in (0 .. 9451 [ms])
@return Period value for envelope generator of the PSG 
*/
uint16_t psg_calc_envelope_period_ms(uint16_t uiTime);

/*!
Set the period of the envelope generator of the PSG.
@param pState Pointer to device structure
@param uiPeriod Period of the requested frequency  
@return EOK = no error
@remark
period = f_clock / (256 * f_env)
f_clock = 1773447 [Hz]
*/
uint8_t psg_set_envelope_period(psgstate_t* pState, uint16_t uiPeriod);

/*!
Get the shape of the envolpe.
@param pState Pointer to device structure
*/
uint8_t psg_get_envelope_shape(psgstate_t* pState) __z88dk_fastcall;

/*!
Set the shape of the amplitude envolpe.
@param pState Pointer to device structure
@return EOK = no error
*/
uint8_t psg_set_envelope_shape(psgstate_t* pState, uint8_t uiShape);

/*!
This function stops access to a Programmable Sound Generator.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t psg_close(psgstate_t* pState);

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

#endif /* __LIBPSG_H__ */
