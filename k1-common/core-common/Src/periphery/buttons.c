/// *****************************************************************************
/// @file           : buttons.c
/// @brief          : buttons management
/// *****************************************************************************
/// created 01.06.2025
/// @author A. Shumilov
/// @attention
/// Copyright 2025 (c) KART CONTROLS
/// All rights reserved.
/// *****************************************************************************

#include "buttons.h"
#include "device-config.h"

const buttons_hw_type BUTTONS_HW[BUTTONS_AMOUNT] =
{
  {BTN_1_GPIO_Port, BTN_1_Pin, BUTTONS_MODE_SHORT_PUSH_EN | BUTTONS_MODE_LONG_PUSH_EN}, // corresponds to BUTTON_FUNC_ADDR
  {BTN_2_GPIO_Port, BTN_2_Pin, BUTTONS_MODE_SHORT_PUSH_EN | BUTTONS_MODE_LONG_PUSH_EN}, // corresponds to BUTTON_FUNC_DUMMY1
  {BTN_3_GPIO_Port, BTN_3_Pin, BUTTONS_MODE_SHORT_PUSH_EN | BUTTONS_MODE_LONG_PUSH_EN}, // corresponds to BUTTON_FUNC_DUMMY2
  {BTN_4_GPIO_Port, BTN_4_Pin, BUTTONS_MODE_SHORT_PUSH_EN | BUTTONS_MODE_LONG_PUSH_EN}, // corresponds to BUTTON_FUNC_DUMMY3
  {BTN_5_GPIO_Port, BTN_5_Pin, BUTTONS_MODE_SHORT_PUSH_EN | BUTTONS_MODE_LONG_PUSH_EN}, // corresponds to BUTTON_FUNC_DUMMY4
};

// type to store Buttons work values
static buttons_vals_type buttons_vals[BUTTONS_AMOUNT] = {0};

BUTTONS_FAIL_TYPE buttons_init()
{
  for(uint32_t i = 0; i < BUTTONS_AMOUNT; ++i)
  {
    buttons_vals[i].push_counter = 0;
    buttons_vals[i].release_counter = 0;
    buttons_vals[i].short_push_flag = 0;
    buttons_vals[i].long_push_flag = 0;
    buttons_vals[i].release_flag = 0;
  }
  return BUTTONS_OK;
}

BUTTONS_FAIL_TYPE buttons_handler()
{
  static uint32_t prev_ms_counter = 0;
  uint32_t period_ms = HAL_GetTick() - prev_ms_counter;
  BUTTONS_FAIL_TYPE ret_val = BUTTONS_FAIL;
  if(period_ms < 500)
  {
    for(uint32_t btn = 0; btn < BUTTONS_AMOUNT; ++btn)
    {
      // button is pushed
      if(HAL_GPIO_ReadPin(BUTTONS_HW[btn].BASE, BUTTONS_HW[btn].PIN) == GPIO_PIN_RESET)
      {
        if(buttons_vals[btn].push_counter < BUTTONS_LONG_PUSH_VAL_MS)
        {
          buttons_vals[btn].push_counter += period_ms;
        }
        // long pushing events
        else if((BUTTONS_HW[btn].MODE_FLAGS_SET & BUTTONS_MODE_LONG_PUSH_EN) && (buttons_vals[btn].release_flag == 1))
        {
          buttons_vals[btn].long_push_flag = 1;
          buttons_vals[btn].release_flag = 0;
        }

        // reset release_counter
        if(buttons_vals[btn].push_counter > BUTTONS_RELEASE_VAL_MS)
          buttons_vals[btn].release_counter = 0;
      }
      // button is released
      else
      {
        // anti debouncing filter
        if(buttons_vals[btn].release_counter < BUTTONS_RELEASE_VAL_MS)
        {
          buttons_vals[btn].release_counter += period_ms;
        }
        // the event "button was released"
        else
        {
          // short pushing events
          if(BUTTONS_HW[btn].MODE_FLAGS_SET & BUTTONS_MODE_SHORT_PUSH_EN)
          {
            // for buttons with possibility of long pushing
            if(BUTTONS_HW[btn].MODE_FLAGS_SET & BUTTONS_MODE_LONG_PUSH_EN)
            {
              if((buttons_vals[btn].push_counter > BUTTONS_SHORT_PUSH_VAL_MS) && (buttons_vals[btn].push_counter < BUTTONS_LONG_PUSH_VAL_MS))
                buttons_vals[btn].short_push_flag = 1;
            }
            // for buttons without possibility of long pushing
            else
            {
              if(buttons_vals[btn].push_counter > BUTTONS_SHORT_PUSH_VAL_MS)
                buttons_vals[btn].short_push_flag = 1;
            }
          } // short pushing events

          buttons_vals[btn].release_flag = 1;
          buttons_vals[btn].push_counter = 0;
        } // the event "button was released"
      } // button is released
    }
    ret_val = BUTTONS_OK;
  }
  prev_ms_counter = HAL_GetTick();
  return ret_val;
}

uint32_t buttons_get_short_push_flags()
{
  uint32_t ret_flags = 0;

  for(uint32_t btn = 0; btn < BUTTONS_AMOUNT; ++btn)
  {
    if(buttons_vals[btn].short_push_flag == 1)
      ret_flags |= 0x1UL << btn;
    buttons_vals[btn].short_push_flag = 0;
  }
  return ret_flags;
}

uint32_t buttons_get_long_push_flags()
{
  uint32_t ret_flags = 0;
  for(uint32_t btn = 0; btn < BUTTONS_AMOUNT; ++btn)
  {
    if(buttons_vals[btn].long_push_flag == 1)
      ret_flags |= 0x1UL << btn;
    buttons_vals[btn].long_push_flag = 0;
  }
  return ret_flags;
}

uint8_t buttons_get_raw_state(uint32_t button_num)
{
  uint8_t ret_val = 0;
  if(button_num < BUTTONS_FUNC_AMOUNT)
  {
    ret_val = (HAL_GPIO_ReadPin(BUTTONS_HW[button_num].BASE, BUTTONS_HW[button_num].PIN) == GPIO_PIN_RESET) ? 1 : 0;
  }
  return ret_val;
}
