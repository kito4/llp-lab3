#pragma once

#ifndef _QUERY_PROCESSOR_H_
#define _QUERY_PROCESSOR_H_

#include "element.h"
#include "element_storage_api.h"
#include "error_code.h"
#include "query.h"

#include <stdbool.h>

struct query_result;

bool query_result_alloc(struct query_result** ptr);

/**
 * @brief Moves query_result to next element, if has no next element, returns ERROR_HAS_NO_NEXT_ELEMENT
 * 
 * @param res 
 * @return error_code 
 */
error_code query_result_next(struct query_result* res);
error_code query_result_get_data(struct query_result* res, struct element** target);
error_code query_result_reset(struct query_result* res);

void query_result_dtor(struct query_result* res);

error_code process_query(struct element_storage* storage, struct query* query, struct query_result* res);

#endif /* _QUERY_PROCESSOR_H_ */