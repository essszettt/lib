/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: libkbd.h                                                           |
| project:  ZX Spectrum Next - libkbd                                          |
| author:   S. Zell                                                            |
| date:     02/02/2026                                                         |
|                                                                              |
+------------------------------------------------------------------------------+
|                                                                              |
| description:                                                                 |
|                                                                              |
| Driver for keyboard of ZX Spectrum Next                                      |
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

#if !defined(__LIBKBD_H__)
  #define __LIBKBD_H__

/*============================================================================*/
/*                               Includes                                     */
/*============================================================================*/

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/

/*!
*/
#define uiMAX_KBDROWS (8)
/*!
This enumeration describes all the key of the keyboard of ZX SPectrum (Next).
Each key has his own individual code, that can be used, i.e. to check if a
specific key is pressed.

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
#if 1
enum
{
  /* ROW 0 */
  KBD_SCANCODE_CPS = 0x0001, /*!< CAPS SHIFT */
  KBD_SCANCODE_Z   = 0x0002,
  KBD_SCANCODE_X   = 0x0004,
  KBD_SCANCODE_C   = 0x0008,
  KBD_SCANCODE_V   = 0x0010,
  /* ROW 1 */
  KBD_SCANCODE_A   = 0x0101,
  KBD_SCANCODE_S   = 0x0102,
  KBD_SCANCODE_D   = 0x0104,
  KBD_SCANCODE_F   = 0x0108,
  KBD_SCANCODE_G   = 0x0110,
  /* ROW 2 */
  KBD_SCANCODE_Q   = 0x0201,
  KBD_SCANCODE_W   = 0x0202,
  KBD_SCANCODE_E   = 0x0204,
  KBD_SCANCODE_R   = 0x0208,
  KBD_SCANCODE_T   = 0x0210,
  /* ROW 3 */
  KBD_SCANCODE_1   = 0x0301,
  KBD_SCANCODE_2   = 0x0302,
  KBD_SCANCODE_3   = 0x0304,
  KBD_SCANCODE_4   = 0x0308,
  KBD_SCANCODE_5   = 0x0310,
  /* ROW 4 */
  KBD_SCANCODE_0   = 0x0401,
  KBD_SCANCODE_9   = 0x0402,
  KBD_SCANCODE_8   = 0x0404,
  KBD_SCANCODE_7   = 0x0408,
  KBD_SCANCODE_6   = 0x0410,
  /* ROW 5 */
  KBD_SCANCODE_P   = 0x0501,
  KBD_SCANCODE_O   = 0x0502,
  KBD_SCANCODE_I   = 0x0504,
  KBD_SCANCODE_U   = 0x0508,
  KBD_SCANCODE_Y   = 0x0510,
  /* ROW 6 */
  KBD_SCANCODE_ENT = 0x0601, /*!< ENTER */
  KBD_SCANCODE_L   = 0x0602,
  KBD_SCANCODE_K   = 0x0604,
  KBD_SCANCODE_J   = 0x0608,
  KBD_SCANCODE_H   = 0x0610,
  /* ROW 7 */
  KBD_SCANCODE_SPC = 0x0701, /*!< SPACE */
  KBD_SCANCODE_SYM = 0x0702, /*!< SYMBOL SHIFT */
  KBD_SCANCODE_M   = 0x0704,
  KBD_SCANCODE_N   = 0x0708,
  KBD_SCANCODE_B   = 0x0710
};
#else
#define KBD_SCANCODE_CPS  (0x0001)
#define KBD_SCANCODE_Z    (0x0002)
#define KBD_SCANCODE_X    (0x0004)
#define KBD_SCANCODE_C    (0x0008)
#define KBD_SCANCODE_V    (0x0010)

#define KBD_SCANCODE_A    (0x0101)
#define KBD_SCANCODE_S    (0x0102)
#define KBD_SCANCODE_D    (0x0104)
#define KBD_SCANCODE_F    (0x0108)
#define KBD_SCANCODE_G    (0x0110)

#define KBD_SCANCODE_Q    (0x0201)
#define KBD_SCANCODE_W    (0x0202)
#define KBD_SCANCODE_E    (0x0204)
#define KBD_SCANCODE_R    (0x0208)
#define KBD_SCANCODE_T    (0x0210)

#define KBD_SCANCODE_1    (0x0301)
#define KBD_SCANCODE_2    (0x0302)
#define KBD_SCANCODE_3    (0x0304)
#define KBD_SCANCODE_4    (0x0308)
#define KBD_SCANCODE_5    (0x0310)

#define KBD_SCANCODE_0    (0x0401)
#define KBD_SCANCODE_9    (0x0402)
#define KBD_SCANCODE_8    (0x0404)
#define KBD_SCANCODE_7    (0x0408)
#define KBD_SCANCODE_6    (0x0410)

#define KBD_SCANCODE_P    (0x0501)
#define KBD_SCANCODE_O    (0x0502)
#define KBD_SCANCODE_I    (0x0504)
#define KBD_SCANCODE_U    (0x0508)
#define KBD_SCANCODE_Y    (0x0510)

#define KBD_SCANCODE_ENT  (0x0601)
#define KBD_SCANCODE_L    (0x0602)
#define KBD_SCANCODE_K    (0x0604)
#define KBD_SCANCODE_J    (0x0608)
#define KBD_SCANCODE_H    (0x0610)

#define KBD_SCANCODE_SPC  (0x0701)
#define KBD_SCANCODE_SYM  (0x0702)
#define KBD_SCANCODE_M    (0x0704)
#define KBD_SCANCODE_N    (0x0708)
#define KBD_SCANCODE_B    (0x0710)
#endif

#if defined(__SDCC)
  #define _KBD_FASTCALL __z88dk_fastcall
#else
  #define _KBD_FASTCALL
#endif

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

/*!
*/
typedef union _kbdrows
{
  uint8_t  uiRaw8[uiMAX_KBDROWS / sizeof(uint8_t)];
  uint16_t uiRaw16[uiMAX_KBDROWS / sizeof(uint16_t)];
  uint32_t uiRaw32[uiMAX_KBDROWS / sizeof(uint32_t)];
} kbdrows_t;

/*!
Device structure for a keyboard.
*/
typedef struct _kbdstate
{
  /*!
  Index of the opened keyboard ( should always be "0" ;-) )
  */
  uint8_t uiIndex;

  /*!
  Raw state of the keyboard as it is read by "kbd_read()".
  */
  kbdrows_t tRows;
  
  /*!
  Buffer that is used internally.
  */
  struct
  {
    /*!
    IO-port of a row while reading the current state
    */
    uint16_t uiAddr;

    /*!
    Buffer for internal use.
    */
    uint8_t uiScratch;

    /*!
    */
    uint8_t uiPressed;

    /*!
    */
    uint8_t uiReleased;

    /*!
    Raw keyboard state of the last reading. Required to detect changes ... 
    */
    kbdrows_t tRows;
  } tPriv;
  
} kbdstate_t;

/*============================================================================*/
/*                               Prototypes                                   */
/*============================================================================*/
/*!
This function opens access to a keyboard.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t kbd_open(kbdstate_t* pState, uint8_t uiIndex);

/*!
This function reads the current state of a keyboard.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t kbd_read(kbdstate_t* pState) _KBD_FASTCALL;

/*!
With this function it can be checked, if a key is pressed.
@param pState Pointer to device-structure
@param uiScanCode Code of the key that should be checked
@return "0" = key is not pressed; "!=0" = key is pressed   
*/
uint8_t kbd_pressed(kbdstate_t* pState, uint16_t uiScanCode);

/*!
This function closes access to a keyboard.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t kbd_close(kbdstate_t* pState) _KBD_FASTCALL;

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

#endif /* __LIBKBD_H__ */
