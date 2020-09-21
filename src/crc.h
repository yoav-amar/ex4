#pragma once
#include <stdint.h>
/**
 * @brief calculate hash by the crc32 algorithem.
 * 
 * @param crc32c should be 0
 * @param buffer the string we operate the crc.
 * @param length the lenght of the buffer0
 * @return uint32_t the hash code
 */
uint32_t
calculate_crc32c(uint32_t crc32c,
    const unsigned char *buffer,
    unsigned int length);