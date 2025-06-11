/// *****************************************************************************
/// @file           : settings.h
/// @brief          : settings management
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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "main.h"
#include "device-config.h"

// the version of settings structure
#define SETS_VERSION  1U

// Types of devices
#define SETS_DEV_TYPE_UNDEFINED     0U
#define SETS_DEV_TYPE_SD            1U // SMOKE DETECTOR
#define SETS_DEV_TYPE_HD            2U // HEAT DETECTOR
#define SETS_DEV_TYPE_SHD           3U // COMBINED (SMOKE-HEAT) DETECTOR
#define SETS_DEV_TYPE_AL2           4U // ADDRESS LABEL 2 INPUTS
#define SETS_DEV_TYPE_AL6           5U // ADDRESS LABEL 6 INPUTS
#define SETS_DEV_TYPE_SEAM          6U // VALVE CONTROL MODULE
#define SETS_DEV_TYPE_ARM2R         7U // RELAY MODULE 2 R OUTPUTS
#define SETS_DEV_TYPE_ARM6R         8U // RELAY MODULE 6 R OUTPUTS
#define SETS_DEV_TYPE_SCI           9U // SHORT CIRCUIT ISOLATOR
#define SETS_DEV_TYPE_BVA          10U // BUZZER PLUS LIGHT INDICATOR
#define SETS_DEV_TYPE_AEL          11U // ALARM EXIT LABEL
#define SETS_DEV_TYPE_FSRSD        12U // удп пуск пожаротушения
#define SETS_DEV_TYPE_SERSD        13U // удп пуск дымоудуланиея
#define SETS_DEV_TYPE_MCP          14U // ручной извещатель
#define SETS_DEV_TYPE_SHUN         15U // шкаф управления вентилятором
#define SETS_DEV_TYPE_EVC          16U // шкаф управления электрозадвижкой
#define SETS_DEV_TYPE_AMU5         17U // адресный модуль пожарной сигнализации
#define SETS_DEV_TYPE_ARM2         18U // релейный модуль на 2 выхода
#define SETS_DEV_TYPE_ARM6         19U // релйный модуль на 6 выходов
#define SETS_DEV_TYPE_MCD          20U // адресный магнитоконтакт
#define SETS_DEV_TYPE_PS           21U // источник питания 220/12в
#define SETS_DEV_TYPE_MS           22U // датчик движения


// ADDRESSES
#define SETS_K1_ADDR_BROADCAST     0x00 // широковещательный запрос
#define SETS_K1_ADDR_MIN           0x01
#define SETS_K1_ADDR_MAX           0xFE
#define SETS_K1_ADDR_PULT          0xFF // CENTRAL PULT ADDRESS

// structure to store all settings
typedef struct
{
  union
  {
    struct
    {
      uint32_t version; // version of settings structure
      uint8_t  device_type; // type of this device
      uint8_t  k1_address[K1_NUM_OF_ITEMS]; // addresses of this device
    };
    uint8_t * by_chars;
    uint32_t * by_words;
  };
  uint32_t crc32;
} settings_type;

// error codes could be used also as OR combination
typedef enum
{
  SETS_OK                 = 0x00, // successful operation
  SETS_ERR                = 0x01, // unknown error
  SETS_NO_INTERFACE_FAIL  = 0x02, // there is no CRC interface pointer
  SETS_TIMEOUT_FAIL       = 0x04, // I2C transaction timeout
  SETS_FLASH_FAIL         = 0x10, // FLASH read/write error
  SETS_CRC_FAIL           = 0x20, // wrong CRC
  SETS_VERSION_FAIL       = 0x40, // wrong version
} settings_err_code_type;


/// @name settings_init
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function initializes the  module.  It  reads  settings
/// @brief from FLASH (main and spare areas), checks CRC.
/// @param crc_interface pointer to CRC_HandleTypeDef type
/// @return SETS_OK or error code
settings_err_code_type settings_init(CRC_HandleTypeDef * crc_interface);

uint8_t settings_get_device_type();
uint8_t settings_get_k1_address(uint8_t index);

settings_err_code_type settings_set_device_type(uint8_t val);
settings_err_code_type settings_set_k1_address (uint8_t val, uint8_t index);

#endif /* SETTINGS_H_ */
