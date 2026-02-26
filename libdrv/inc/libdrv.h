/*-----------------------------------------------------------------------------+
|                                                                              |
| filename: libdrv.h                                                           |
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

#if !defined(__LIBDRV_H__)
  #define __LIBDRV_H__

/*============================================================================*/
/*                               Includes                                     */
/*============================================================================*/
#include "libzxn.h"

/*============================================================================*/
/*                               Macros                                       */
/*============================================================================*/
/*!
Version information of the library
*/
#define DRV_VERSION_MAJOR       0
#define DRV_VERSION_MINOR       0
#define DRV_VERSION_PATCH       5
#define DRV_PRODUCTNAME_STR     "libdrv"
#define DRV_COMPANYNAME_STR     "STZ Engineering"
#define DRV_LEGALCOPYRIGHT_STR  "\x7F 2026 " DRV_COMPANYNAME_STR

/*!
This macro can be used to check, if a joystick is pushed to RIGHT.
*/
#define JOYSTICK_DIR_RI (0x01)

/*!
This macro can be used to check, if a joystick is pushed to LEFT.
*/
#define JOYSTICK_DIR_LE (0x02)

/*!
This macro can be used to check, if a joystick is pushed DOWN.
*/
#define JOYSTICK_DIR_DN (0x04)

/*!
This macro can be used to check, if a joystick is pushed UP.
*/
#define JOYSTICK_DIR_UP (0x08)

/*!
This macro can be used to check, if the B-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_B (0x01)

/*!
This macro can be used to check, if the C-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_C (0x02)

/*!
This macro can be used to check, if the A-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_A (0x04)

/*!
This macro can be used to check, if the START-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_S (0x08)

/*!
This macro can be used to check, if the MODE-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_M (0x10)

/*!
This macro can be used to check, if the Y-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_Y (0x20)

/*!
This macro can be used to check, if the Z-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_Z (0x40)

/*!
This macro can be used to check, if the X-button of a joystick is pressed.
*/
#define JOYSTICK_BTN_X (0x80)

/*!
Value to set mouse sensitivity to LOW
*/
#define MOUSE_SENSITIVITY_LOW (0x00)

/*!
Value to set mouse sensitivity to the DEFAULT value
*/
#define MOUSE_SENSITIVITY_DEFAULT (0x01)

/*!
Value to set mouse sensitivity to MEDIUM
*/
#define MOUSE_SENSITIVITY_MEDIUM (0x02)

/*!
Value to set mouse sensitivity to HIGH
*/
#define MOUSE_SENSITIVITY_HIGH (0x03)

/*!
Number of next-reg "PERIPHERAL5"
*/
#if !defined(REG_PERIPHERAL_5)
  #define REG_PERIPHERAL_5 (0x0A)
#endif

/*!
This macro delivers the version number of the library as a string literal
*/
#define DRV_VERSION_STR ZXN_VER_STR(DRV_VERSION_MAJOR) "." \
                        ZXN_VER_STR(DRV_VERSION_MINOR) "." \
                        ZXN_VER_STR(DRV_VERSION_PATCH)

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
This structure is used to manage and read the state of a joystick/gamepad
*/
typedef struct _joystickstate
{
  /*!
  Index of the opened joystick/gamepad:
  - "0" = left joystick/gamepad
  - "1" = right joystick/gamepad
  */
  uint8_t uiIndex;

  /*!
  Current state of the direction (RI, LE, DN, UP)
  @code
  BIT0  DIR-RIGHT
  BIT1  DIR-LEFT
  BIT2  DIR-DOWN
  BIT3  DIR-UP
  @endcode
  */
  uint8_t uiDir;

  /*!
  Current state of the buttons (A, B, C, X, Y, Z, START, MODE
  @code
  BIT0  BTN-B
  BIT1  BTN-C
  BIT2  BTN-A
  BIT3  BTN-START
  BIT4  BTN-MODE
  BIT5  BTN-Y
  BIT6  BTN-Z
  BIT7  BTN-X
  @endcode
  */
  uint8_t uiBtn;

  /*!
  Internal use only: Decoding raw values
  */
  uint8_t uiScratch;
} joystickstate_t;

/*!
This structure is used to manage and read the state of a mouse/trackball
Current cursor position (x = 0, y = 0: screen left bottom). These coordinates
are indepenant from screen resolution.
*/
typedef struct _mousestate
{
  /*!
  Index of the opened joystick/gamepad:
  - "0" = first mouse/trackball
  - "1" = second mouse/trackball
  - ...
  */
  uint8_t uiIndex;

  /*!
  Current X-position (-32768 .. +32767)
  */
  int16_t iX;

  /*!
  Current Y-position (-32768 .. +32767)
  */
  int16_t iY;

  /*!
  Current state of the scroll wheel
  */
  uint8_t uiWhl;

  /*!
  Current state of the buttons
  */
  uint8_t uiBtn;

  /*!
  In this internal structure are all the variables, that are required to do the
  position calculations. This part is not part of the official API and can be
  changed in future releases.
  */
  struct
  {
    /*!
    Current X-value from mouse
    */
    uint8_t uiCurrX;

    /*!
    Current Y-value from mouse
    */
    uint8_t uiCurrY;

    /*!
    Previous X-value from mouse
    */
    uint8_t uiPrevX;

    /*!
    Previous Y-value from mouse
    */
    uint8_t uiPrevY;

    /*!
    Internal buffer for calculations, ...
    */
    uint8_t uiScratch;
  } tPriv;
} mousestate_t;

/*============================================================================*/
/*                               Prototypes                                   */
/*============================================================================*/
/*!
With this function returns the version information of the library.
@return version information of the library (major, minor, patch)
*/
version_t zxn_version(void);

/*!
This function opens access to a joaystick/gamepad
@param pState Pointer to device-structure
@param uiIndex Index of the joystick ("0" = left, "1" = right)
@return EOK = no error
*/
uint8_t joystick_open(joystickstate_t* pState, uint8_t uiIndex);

/*!
This function reads the current state of a joystick/gamepad. The current
direction and the state of the buttons can be read from the device structure.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t joystick_read(joystickstate_t* pState) __z88dk_fastcall;

/*!
This function closes access to a previously opened joystick.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t joystick_close(joystickstate_t* pState);

/*!
This function opens access to a mouse/trackball.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t mouse_open(mousestate_t* pState, uint8_t uiIndex);

/*!
Set if mouse buttons should be swapped (left- or right-handed)
@param pState Pointer to device-structure
@param uiSwap If value is not "0" buttons are swapped
@return EOK = no error
*/
uint8_t mouse_set_buttonswap(mousestate_t* pState, uint8_t uiSwap);

/*!
Read the current setting if the button swap function
@param pState Pointer to device-structure
@return Current setting; on errors "0xFF" 
*/
uint8_t mouse_get_buttonswap(mousestate_t* pState) __z88dk_fastcall;

/*!
Set the sensitivity of the movement detection of the mouse.
@param pState Pointer to device-structure
@param uiSensitivity Sensitivity of the mouse movement
                     (i.e. "MOUSE_SENSITIVITY_LOW")
@return EOK = no error
*/
uint8_t mouse_set_sensitivity(mousestate_t* pState, uint8_t uiSensitivity);

/*!
Read the current setting of mouse sensitivity
@param pState Pointer to device-structure
@return Current setting; on errors "0xFF" 
*/
uint8_t mouse_get_sensitivity(mousestate_t* pState) __z88dk_fastcall;

/*!
The current position of the mouse can be reset with this function.
@param pState Pointer to device-structure
@param iX New X-position of the mouse
@param iY New Y-position of the mouse
@return EOK = no error
*/
uint8_t mouse_reset(mousestate_t* pState, int16_t iX, int16_t iY);

/*!
This function reads the current state of a mouse/trackball. The current position
and the state of buttons and the scroll wheel can be read from the device state
structure.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t mouse_read(mousestate_t* pState) __z88dk_fastcall;

/*!
This function closes access to a mouse/trackball.
@param pState Pointer to device-structure
@return EOK = no error
*/
uint8_t mouse_close(mousestate_t* pState);

/*============================================================================*/
/*                               Implementation                               */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

#endif /* __LIBDRV_H__ */
