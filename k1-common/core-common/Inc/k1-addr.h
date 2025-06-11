/// *****************************************************************************
/// @file           : k1-addr.h
/// @brief          : k1 bus address management
/// *****************************************************************************
/// created 01.06.2025
/// @author A. Shumilov
/// @attention
/// Copyright 2025 (c) KART CONTROLS
/// All rights reserved.
/// *****************************************************************************

/// KC_SD_v1.0(PCB) section 2
/// 2. Адресация
/// - Использует 1 адрес в системе K1
/// - Встроенный UID
/// - Контроль дублирующего адреса

#include "main.h"

#ifndef INC_K1_ADDR_H_
#define INC_K1_ADDR_H_
typedef enum
{
	K1_ADDR_OK,
	K1_ADDR_ERR
}K1_ADDR_ERR_CODES;

/// Set address for item
/// @param addr address of the item, range [1 - 255]
/// @param item item's number in the device [0 - K1_NUM_OF_ITEMS)
/// @return K1_ADDR_OK when addrss added, K1_ADDR_ERR when address is not added
K1_ADDR_ERR_CODES k1_addr_set(uint8_t addr, uint8_t item);

/// Get address for item
/// @param item item's number in the device [0 - K1_NUM_OF_ITEMS)
/// @return address of the item or 0 when it's not defined
uint8_t k1_addr_get(uint8_t item);

#endif // #ifndef INC_K1_ADDR_H_
