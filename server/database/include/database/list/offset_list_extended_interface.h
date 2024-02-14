#pragma once

#ifndef _OFFSET_LIST_EXTENDED_INTERFACE_H_
#define _OFFSET_LIST_EXTENDED_INTERFACE_H_

/**
 * This file consists of extra functions
 * to work with offset_list without data(data_size=0)
 */

#include "offset_list_interface.h"

/**
 * @brief Creates tail elements in specific place
 * 
 * @param list 
 * @param place 
 */
void offset_list_push_back_inplace(struct offset_list* list, mem_offset_t place, mem_size_t buffer_size,
                                   const void* buffer);
void offset_list_push_front_inplace(struct offset_list* list, mem_offset_t place, mem_size_t buffer_size,
                                    const void* buffer);

mem_offset_t offset_list_iterator_get_node_offset(struct offset_list_iterator* iter);

#endif /* _OFFSET_LIST_EXTENDED_INTERFACE_H_ */