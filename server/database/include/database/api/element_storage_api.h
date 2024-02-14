#pragma once

#ifndef _STORAGE_API_H_
#define _STORAGE_API_H_

#include "element.h"
#include "error_code.h"
#include "schema.h"
#include "storage_iterator_api.h"

#include <stdbool.h>

struct element_storage;

bool element_storage_alloc(struct element_storage** ptr);

bool element_storage_ctor(struct element_storage* storage, const char* filename, size_t page_size);
bool element_storage_read(struct element_storage* storage, const char* filename, size_t page_size);
void element_storage_dtor(struct element_storage* storage);

/**
 * @brief Adds element type to storage's schema
 * 
 * @param storage 
 * @param type 
 * @param type_iter [optional], if != NULL, then will contain iter, to added type
 * @return error_code 
 */
error_code element_storage_add_element_type(struct element_storage* storage, const struct element_type* type,
                                            struct storage_iterator* type_iter);

bool element_storage_element_type_list_is_empty(const struct element_storage* storage);
error_code element_storage_get_element_type_iter(const struct element_storage* storage,
                                                 struct storage_iterator* target);
/**
 * @brief Deletes element_type under given iterator, invalidates given iterator
 * If there are elements with given type in storage, return ERROR_TYPE_IS_NOT_EMPTY
 * 
 * @param storage 
 * @param type 
 * @return error_code
 */
error_code element_storage_remove_element_type(struct element_storage* storage, struct storage_iterator* type);

error_code element_storage_get_element_type(const struct element_storage* storage, const struct storage_iterator* iter,
                                            struct element_type* target);

error_code element_storage_add_link_type(struct element_storage* storage, const struct link_type* type);

bool element_storage_link_type_list_is_empty(const struct element_storage* storage);
error_code element_storage_get_link_type_iter(const struct element_storage* storage, struct storage_iterator* target);
/**
 * @brief Deletes link_type under given iterator, invalidates given iterator
 * You need to make sure there is no links with given type in storage before calling this method
 * Otherwise storage would come into undefined state
 * 
 * @param storage 
 * @param type 
 * @return error_code 
 */
error_code element_storage_remove_link_type(struct element_storage* storage, struct storage_iterator* type);

error_code element_storage_get_link_type(const struct element_storage* storage, const struct storage_iterator* iter,
                                         struct link_type* target);

/**
 * @brief Adds given element without links to storage
 * 
 * Element's type is ignored and might be NULL
 * Element's links are ignored and might be NULL
 * Type is taken from iterator that points to element_type
 * 
 * @param storage 
 * @param iter
 * @param element 
 * @return error_code 
 */
error_code element_storage_add_element_of_type(struct element_storage* storage, struct storage_iterator* type_iter,
                                               const struct element* element);

/**
 * @brief Creates an iterator for element's of given type
 * 
 * @param storage 
 * @param type_iter 
 * @param target 
 * @return error_code 
 */
error_code element_storage_get_element_iter(const struct element_storage* storage,
                                            const struct storage_iterator* type_iter, struct storage_iterator* target);

/**
 * @brief Deletes element of given type by given iterator
 * Also deletes all links that was incident to given element
 * WARNING: Invalidates given iterotor
 * 
 * @param storage 
 * @param element_iter 
 * @return error_code 
 */
error_code element_storage_remove_element(struct element_storage* storage, struct storage_iterator* type_iter,
                                          struct storage_iterator* element_iter);

/**
 * @brief Fills the element's type and attributes
 * 
 * @param storage 
 * @param element_iter 
 * @param target 
 * @return error_code 
 */
error_code element_storage_get_element(const struct element_storage* storage,
                                       const struct storage_iterator* element_iter, struct element* target);

/** 
 * @brief Fills the element's attributes
 * 
 * @param storage 
 * @param element_iter 
 * @param target 
 * @return error_code 
 */
error_code element_storage_get_element_attrs(const struct element_storage* storage,
                                             const struct storage_iterator* element_iter, struct element* target);

/**
 * @brief Updates the element's attributes
 * 
 * @param storage 
 * @param element_iter 
 * @param attribute_count 
 * @param attrs 
 * @return error_code 
 */
error_code element_storage_rewrite_element_attrs(struct element_storage* storage, struct storage_iterator* element_iter,
                                                 const struct attribute* attrs, attribute_count_t attribute_count);

error_code element_storage_get_element_links_out_iter(const struct element_storage* storage,
                                                      const struct storage_iterator* element_iter,
                                                      struct storage_iterator* target);
error_code element_storage_get_element_links_in_iter(const struct element_storage* storage,
                                                     const struct storage_iterator* element_iter,
                                                     struct storage_iterator* target);

/**
 * @brief Fills the link_type
 * 
 * @param storage 
 * @param link_iter 
 * @param link_type 
 * @return error_code 
 */
error_code element_storage_get_type_of_link(const struct element_storage* storage,
                                            const struct storage_iterator* link_iter, link_type_id_t* type_id);

error_code element_storage_get_type_of_link_dst_element(const struct element_storage* storage,
                                                        const struct storage_iterator* link_iter,
                                                        element_type_id_t* target);

/**
 * @brief Fills the iterator to dst element
 * 
 * @param storage 
 * @param link_iter 
 * @param element_iter will contain iterator to dst element (DON'T call next or prev on it)
 * @return error_code 
 */
error_code element_storage_get_link_dst_element_iter(const struct element_storage* storage,
                                                     const struct storage_iterator* link_iter,
                                                     struct storage_iterator* element_iter);

/**
 * @brief Adds link between two given elements
 * 
 * @param storage 
 * @param src_element_iter 
 * @param dst_element_iter 
 * @param link 
 * @return error_code 
 */
error_code element_storage_add_link(struct element_storage* storage, struct storage_iterator* src_element_iter,
                                    struct storage_iterator* dst_element_iter, link_type_id_t link_type);
#endif /* _STORAGE_API_H_ */