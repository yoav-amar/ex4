#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef enum {
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0,
    ERROR_NOT_POSITIVE_WIDTH,
    ERROR_NOT_POSITIVE_HIGHT,
    ERROR_FAILED_ALOCATE_MEM,
    ERROR_MATRIX_IS_NULL,
    ERROR_INDEX_OUT_OF_LIMITS,
    ERROR_CANT_ADD,
    ERROR_CANT_MULT,
    ERROR_GET_NULL_PTR
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);

#ifdef __cplusplus
}
#endif