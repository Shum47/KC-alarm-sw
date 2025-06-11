/// *****************************************************************************
/// @file           : buttons.h
/// @brief          : buttons management
/// *****************************************************************************
/// created 01.06.2025
/// @author A. Shumilov
/// @attention
/// Copyright 2025 (c) KART CONTROLS
/// All rights reserved.
/// *****************************************************************************

/// KC_SD_v1.0(PCB) section 4
/// 4. Интерфейсы и подключения
/// - Адресная линия K1
/// - Кнопка адресации (внутри корпуса)

#ifndef SRC_PERIPHERY_BUTTONS_H_
#define SRC_PERIPHERY_BUTTONS_H_

#include "stdint.h"
#include "stddef.h"
#include "main.h"

// type to return fail codes of Buttons module
typedef enum
{
  BUTTONS_OK,
  BUTTONS_FAIL
} BUTTONS_FAIL_TYPE;


// supported modes for the button
#define BUTTONS_MODE_SHORT_PUSH_EN  (0x1U << 0)
#define BUTTONS_MODE_LONG_PUSH_EN   (0x1U << 1)

// timestamps for buttons counters
#define BUTTONS_SHORT_PUSH_VAL_MS      60
#define BUTTONS_LONG_PUSH_VAL_MS       1900
#define BUTTONS_RELEASE_VAL_MS         30

/// buttons by functionality
enum
{
  BUTTON_FUNC_ADDR = 0,
  BUTTON_FUNC_DUMMY1,
  BUTTON_FUNC_DUMMY2,
  BUTTON_FUNC_DUMMY3,
  BUTTONS_FUNC_AMOUNT
};

/// buttons by schematic
enum
{
  BUTTON_1 = 0,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTONS_AMOUNT
};

// type to store Buttons constants
typedef struct
{
  GPIO_TypeDef* BASE;       // base address of the registers for the button
  uint16_t PIN;             // pin number of the button
  uint8_t MODE_FLAGS_SET;   // set of BUTTONS_MODE for the button
}buttons_hw_type;

// type to store Buttons work values
typedef struct
{
  uint32_t push_counter;         // upward counts during pushing
  uint32_t release_counter;      // upward counts during releasing
  uint32_t short_push_flag  : 1; // button short pushing flag
                                 // 1 - button was short pushed
  uint32_t long_push_flag   : 1; // button long pushing flag
                                 // 1 - button was long pushed
  uint32_t release_flag     : 1; // button long pushing flag
                                 // 1 - button was long pushed
}buttons_vals_type;


/// @name buttons_init
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function initializes Buttons module
/// @return BUTTONS_OK    - Buttons module was initialized without faults
/// @return BUTTONS_FAIL - Buttons module was initialized with faults
BUTTONS_FAIL_TYPE buttons_init();

/// @name buttons_handler
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function provides updating of buttons module data
/// @brief For correct work period of the runtime should be less than 10 ms
/// @return BUTTONS_OK, BUTTONS_FAIL
BUTTONS_FAIL_TYPE buttons_handler();

/// @name buttons_get_short_push_flags
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function returns flags for short pushing events
/// @return Correspond bit is set to 1 if short pushing event is active for the
/// @return button. Numbers of the bits correspond to
/// @return         enum
/// @return         {
/// @return           BUTTON_FUNC_ADDR = 0,
/// @return           BUTTON_FUNC_DUMMY1,
/// @return           BUTTON_FUNC_DUMMY2,
/// @return           BUTTON_FUNC_DUMMY3,
/// @return           BUTTON_FUNC_DUMMY4,
/// @return           BUTTONS_FUNC_AMOUNT
/// @return         };
uint32_t buttons_get_short_push_flags();


/// @name buttons_get_long_push_flags
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function returns flags for long pushing events
/// @return Correspond bit is set to 1 if long pushing event is active for the
/// @return button. Numbers of the bits correspond to
/// @return         enum
/// @return         {
/// @return           BUTTON_FUNC_ADDR = 0,
/// @return           BUTTON_FUNC_DUMMY1,
/// @return           BUTTON_FUNC_DUMMY2,
/// @return           BUTTON_FUNC_DUMMY3,
/// @return           BUTTON_FUNC_DUMMY4,
/// @return           BUTTONS_FUNC_AMOUNT
/// @return         };
uint32_t buttons_get_long_push_flags();

/// @name buttons_get_raw_state
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function returns raw state of button, pushed/released.
/// @param button_num
/// @param enum
/// @param {
/// @param   BUTTON_FUNC_ADDR = 0,
/// @param   BUTTON_FUNC_DUMMY1,
/// @param   BUTTON_FUNC_DUMMY2,
/// @param   BUTTON_FUNC_DUMMY3,
/// @param   BUTTON_FUNC_DUMMY4,
/// @param   BUTTONS_FUNC_AMOUNT
/// @param };
/// @return 1 - button is pushed, 0 - released
uint8_t buttons_get_raw_state(uint32_t button_num);

#endif /* SRC_PERIPHERY_BUTTONS_H_ */
