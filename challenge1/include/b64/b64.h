#ifndef CHALLENGE1_B64_B64_H
#define CHALLENGE1_B64_B64_H

#include <stddef.h>
#include <stdint.h>

size_t b64_encode(const uint8_t *const restrict src, const size_t src_length, 
    uint8_t *restrict *dest);
size_t b64_encode_to_string(const uint8_t *const restrict src, 
    const size_t src_length, char *restrict *dest);
size_t b64_decode(const uint8_t *const restrict src, const size_t src_length,
    uint8_t *restrict *dest);
size_t b64_decode_from_string(const char *const restrict src, 
    uint8_t *restrict *dest);
short is_b64(const uint8_t *const bytes, const size_t bytes_count);
short is_b64_string(const char *const string);

#endif
