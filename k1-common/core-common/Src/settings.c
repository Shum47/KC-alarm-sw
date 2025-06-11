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

#include "settings.h"
#include "main.h"
#include "device-config.h"

// interface for CRC calculating
static CRC_HandleTypeDef * settings_crc_interface = 0;

// RAM copy of settings
static settings_type settings = {0};

// stored settings CRC (read after power on)
static uint32_t settings_stored_crc = 0;

enum
{
  SETS_MAIN_COPY,
  SETS_SPARE_COPY
};

/// @name settings_read
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function reads settings from main or copy area in flash.
/// @brief Checks CRC.
/// @param copy_num SETS_MAIN_COPY or SETS_SPARE_COPY
/// @return SETS_OK or error code
static settings_err_code_type settings_read(uint32_t copy_num)
{
  settings_err_code_type ret_val = SETS_OK;
  uint32_t * copy_addr = (copy_num == SETS_MAIN_COPY) ? (uint32_t *)FLASH_SETS_MAIN_ADDR : (uint32_t *)FLASH_SETS_COPY_ADDR;
  // reading settings from flash is successful
  for(uint8_t word = 0; word < sizeof(settings_type)/4; ++word)
  {
    settings.by_words[word] = copy_addr[word];
  }
  // check the CRC
  if(settings.crc32 != HAL_CRC_Calculate(settings_crc_interface, settings.by_words, sizeof(settings.by_words)))
  {
    ret_val = SETS_CRC_FAIL;
  }
  else if(settings.version != SETS_VERSION)
  {
    ret_val = SETS_VERSION_FAIL;
  }
  settings_stored_crc = settings.crc32;
  return ret_val;
}

/// @name settings_verify
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function reads the copy  of  settings  from  FLASH  and
/// @brief compares it to current settings.
/// @param copy_num SETS_MAIN_COPY or SETS_SPARE_COPY
/// @return SETS_OK or error code
static settings_err_code_type settings_verify(uint32_t copy_num)
{
  settings_err_code_type ret_val = SETS_OK;
  const uint32_t * copy_addr = (copy_num == SETS_MAIN_COPY) ? (uint32_t *)FLASH_SETS_MAIN_ADDR : (uint32_t *)FLASH_SETS_COPY_ADDR;
  // compare to current settings
  for(uint32_t i = 0; i < (sizeof(settings.by_words) / 4); ++i)
  {
    if(settings.by_words[i] != copy_addr[i])
    {
      ret_val = SETS_ERR;
    }
  }
  if(settings.crc32 != copy_addr[sizeof(settings.by_words) / 4])
  {
    ret_val = SETS_CRC_FAIL;
  }
  return ret_val;
}

/// @name settings_write
/// @author Aleksandr Shumilov
/// created 03.06.2025
/// @brief The function calculates CRC and writes settings  to  FRAM.
/// @brief copy_num - number of record SETS_MAIN_COPY,SETS_SPARE_COPY
/// @param copy_num SETS_MAIN_COPY or SETS_SPARE_COPY
/// @return SETS_OK or error code
static settings_err_code_type settings_write (uint32_t copy_num)
{
  settings_err_code_type ret_val = SETS_ERR;
  uint32_t copy_addr =
      (copy_num == SETS_MAIN_COPY) ?
          FLASH_SETS_MAIN_ADDR : FLASH_SETS_COPY_ADDR;
  // settings version
  settings.version = SETS_VERSION;
  // CRC calculating
  settings.crc32 = HAL_CRC_Calculate (settings_crc_interface, settings.by_words,
                                      sizeof(settings.by_words));
  // unlock flash
  if (HAL_FLASH_Unlock () == HAL_OK)
  {
    // erase
    FLASH_EraseInitTypeDef erase_str =
      {
      FLASH_TYPEERASE_PAGES,
      FLASH_BANK_1, copy_addr, 1 };
    uint32_t err_code = 0;
    if (HAL_OK == HAL_FLASHEx_Erase (&erase_str, &err_code))
    {
      for (uint32_t i = 0; i < (sizeof(settings_type) / 4); ++i)
      {
        // programm
        HAL_FLASH_Unlock ();
        HAL_FLASH_Program (FLASH_TYPEPROGRAM_WORD, ((uint32_t*)copy_addr)[i],
                           settings.by_words[i]);
        HAL_FLASH_Lock ();
      }
      // verifying
      ret_val = settings_verify (copy_num);
    }
  }
  return ret_val;
}

settings_err_code_type settings_init(CRC_HandleTypeDef * crc_interface)
{
  settings_err_code_type ret_val = SETS_OK;
  if(crc_interface == 0)
    ret_val = SETS_NO_INTERFACE_FAIL;
  else
  {
    // initialize the CRC interface pointer
    settings_crc_interface = crc_interface;
    // reading the main copy of settings from FRAM is successful
    ret_val = settings_read(SETS_MAIN_COPY);

    // read the spare copy of settings
    if(ret_val != SETS_OK)
    {
      // reading the spare copy of settings from FRAM is successful
      ret_val = settings_read(SETS_SPARE_COPY);

      // if spare copy is valid we should rewrite the main copy
      if(ret_val == SETS_OK)
      {
        ret_val = settings_write(SETS_MAIN_COPY);
      }
    }
    // rewrite spare copy
    else
    {
      ret_val = settings_write(SETS_SPARE_COPY);
    }
  }
  return ret_val;
}

uint8_t settings_get_device_type(){return settings.device_type;}
uint8_t settings_get_k1_address(uint8_t index)
{
  if(index < K1_NUM_OF_ITEMS)
    return settings.k1_address[index];
  else
    return settings.k1_address[0];
}

settings_err_code_type settings_set_device_type(uint8_t val)
{
  settings.device_type = val;
  return settings_write(SETS_MAIN_COPY) | settings_write(SETS_SPARE_COPY);
}
settings_err_code_type settings_set_k1_address(uint8_t val, uint8_t index)
{
  if(index < K1_NUM_OF_ITEMS)
  {
    settings.k1_address[index] = val;
    return settings_write(SETS_MAIN_COPY) | settings_write(SETS_SPARE_COPY);
  }
  else
  {
    return SETS_ERR;
  }
}
