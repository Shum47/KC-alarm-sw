/// *****************************************************************************
/// @file           : k1-addr.c
/// @brief          : k1 bus address management
/// *****************************************************************************
/// created 01.06.2025
/// @author A. Shumilov
/// @attention
/// Copyright 2025 (c) KART CONTROLS
/// All rights reserved.
/// *****************************************************************************

#include "device-config.h"
#include "k1-addr.h"

/// K1 addresses of all items in our device
static uint8_t k1_addr[K1_NUM_OF_ITEMS] = {0};

K1_ADDR_ERR_CODES k1_addr_set(uint8_t addr, uint8_t item)
{
	K1_ADDR_ERR_CODES ret_val = K1_ADDR_OK;
	// correctness of item number
	if(item < K1_NUM_OF_ITEMS)
	{
		// correctness of address
		if(addr > 0U)
		{
			// set address
			k1_addr[item] = addr;
		}
	}
	else
	{
		ret_val = K1_ADDR_ERR;
	}
	return ret_val;
}

/// Get address for item
/// @param item item's number in the device [0 - K1_NUM_OF_ITEMS)
/// @return address of the item or 0 when it's not defined
uint8_t k1_addr_get(uint8_t item)
{
	// correctness of item number
	if(item < K1_NUM_OF_ITEMS)
	{
		return k1_addr[item];
	}
	else
	{
		return 0U;
	}
}



