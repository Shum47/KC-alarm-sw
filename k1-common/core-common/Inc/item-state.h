/// *****************************************************************************
/// @file           : item-state.h
/// @brief          : state of k1 bus address management
/// *****************************************************************************
/// created 01.06.2025
/// @author A. Shumilov
/// @attention
/// Copyright 2025 (c) KART CONTROLS
/// All rights reserved.
/// *****************************************************************************

/// KC_SD_v1.0(PCB) section 2
/// 5. Состояния и события (по K1)
/// - Состояние "Норма"
/// - Состояние "Внимание" (предтревожное)
/// - Состояние "Пожар"
/// - Потеря связи
/// - Адрес не присвоен
/// - Дублирующий адрес
/// - Требуется обслуживание (по запыленности)
/// - Режим ТЕСТ

#include "main.h"

#ifndef INC_ITEM_STATE_H_
#define INC_ITEM_STATE_H_

typedef enum
{
  ITEM_STATE_UNDEFINED,
  ITEM_STATE_NORM,
  ITEM_STATE_ATTENTION,
  ITEM_STATE_FIRE,
  ITEM_STATE_MAX = ITEM_STATE_FIRE
} ITEM_STATE_TYPE;

/// Set state for item
/// @param state state of the item, range ITEM_STATE_TYPE
/// @param item item's number in the device [0 - K1_NUM_OF_ITEMS)
void item_state_set(ITEM_STATE_TYPE state, uint8_t item);

/// Get state for item
/// @param item item's number in the device [0 - K1_NUM_OF_ITEMS)
/// @return state of the item, range ITEM_STATE_TYPE
ITEM_STATE_TYPE item_state_get(uint8_t item);



#endif /* INC_ITEM_STATE_H_ */
