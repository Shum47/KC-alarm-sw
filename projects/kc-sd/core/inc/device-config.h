/// *****************************************************************************
///  @file           : device-config.h
///  @brief          : configuration of the device
/// *****************************************************************************
///  @author A. Shumilov
///  @attention
///  Copyright 2025 (c) KART CONTROLS
///  All rights reserved.
/// *****************************************************************************

#ifndef INC_DEVICE_CONFIG_H_
#define INC_DEVICE_CONFIG_H_

/// number of K1 addresses in the device
#define K1_NUM_OF_ITEMS 1U

/// main short cycle period in ms
#define MAIN_SHORT_CYCLE_PERIOD_MS  10U

/// address for device settings in MCU Flash
#define FLASH_SETS_MAIN_ADDR 0x0800F800 // page 62, 1KB
#define FLASH_SETS_COPY_ADDR 0x0800FC00 // page 63, 1KB

/// MCU pin-out for the device

#define k1_pwm3_Pin GPIO_PIN_0
#define k1_pwm3_GPIO_Port GPIOA

#define v_in_mon_Pin GPIO_PIN_1
#define v_in_mon_GPIO_Port GPIOA

#define K1_TX_Pin GPIO_PIN_2
#define K1_TX_GPIO_Port GPIOA
#define K1_RX_Pin GPIO_PIN_3
#define K1_RX_GPIO_Port GPIOA

#define security1_Pin GPIO_PIN_4
#define security1_GPIO_Port GPIOA
#define security2_Pin GPIO_PIN_5
#define security2_GPIO_Port GPIOA
#define security3_Pin GPIO_PIN_6
#define security3_GPIO_Port GPIOA
#define security4_Pin GPIO_PIN_7
#define security4_GPIO_Port GPIOA
#define security5_Pin GPIO_PIN_0
#define security5_GPIO_Port GPIOB
#define security6_Pin GPIO_PIN_1
#define security6_GPIO_Port GPIOB

// buttons
#define addr_button_Pin GPIO_PIN_13
#define addr_button_GPIO_Port GPIOB
#define BTN_1_Pin addr_button_Pin
#define BTN_1_GPIO_Port addr_button_GPIO_Port
#define BTN_2_Pin addr_button_Pin
#define BTN_2_GPIO_Port addr_button_GPIO_Port
#define BTN_3_Pin addr_button_Pin
#define BTN_3_GPIO_Port addr_button_GPIO_Port
#define BTN_4_Pin addr_button_Pin
#define BTN_4_GPIO_Port addr_button_GPIO_Port
#define BTN_5_Pin addr_button_Pin
#define BTN_5_GPIO_Port addr_button_GPIO_Port

#define k1_pwm1_Pin GPIO_PIN_8
#define k1_pwm1_GPIO_Port GPIOA

#define console_tx_Pin GPIO_PIN_9
#define console_tx_GPIO_Port GPIOA
#define console_rx_Pin GPIO_PIN_10
#define console_rx_GPIO_Port GPIOA

#define k1_pwm2_Pin GPIO_PIN_11
#define k1_pwm2_GPIO_Port GPIOA
#define k1_capture_Pin GPIO_PIN_6
#define k1_capture_GPIO_Port GPIOB


#endif /* INC_DEVICE_CONFIG_H_ */
