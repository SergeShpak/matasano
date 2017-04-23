#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char *b64_alphabet = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char pad = '=';

size_t b64_encode(const uint8_t *const restrict src, const size_t src_length,
    uint8_t *restrict *dest) {
  if (!src) {
    *dest = NULL;
    return 0;
  }
  if (0 == src_length) {
    return 0;
  }
  // 11111100b
  const uint8_t six_msb_mask = 0xfc;
  const uint8_t four_msb_mask = 0xf0;
  const uint8_t four_lsb_mask = 0x0f;
  const uint8_t two_lsb_mask = 0x03;
  // 11000000b
  const uint8_t two_msb_mask = 0xC0;
  const uint8_t six_lsb_mask = 0x3f;
  const size_t triplets_number = src_length / 3;
  const size_t triplets_residual = src_length % 3;
  const size_t encoding_size = triplets_residual ? 
    (triplets_number + 1) * 4 : triplets_number * 4;
  const size_t paddings_count = 3 - triplets_residual;
  *dest = (uint8_t*) malloc(sizeof(uint8_t) * encoding_size);
  if (paddings_count != 0 && paddings_count != 3) {
    memset(*dest + (encoding_size - paddings_count), pad, paddings_count); 
  }
  size_t b64_elements_count_from_triplets = triplets_number * 4;
  size_t src_index = 0;
  for (int i = 0; i < b64_elements_count_from_triplets; i += 4) {
    (*dest)[i] = b64_alphabet[(src[src_index] & six_msb_mask) >> 2];
    (*dest)[i + 1] = b64_alphabet[((src[src_index] & two_lsb_mask) << 4) | 
      ((src[src_index + 1] & four_msb_mask) >> 4)];
    (*dest)[i + 2] = b64_alphabet[((src[src_index + 1] & four_lsb_mask) << 2) |
      ((src[src_index + 2] & two_msb_mask) >> 6)];
    (*dest)[i + 3] = b64_alphabet[src[src_index + 2] & six_lsb_mask];
    src_index += 3;
  }
  if (0 == triplets_residual) {
    return encoding_size;
  }
  size_t dest_residual_index = triplets_number * 4;
  size_t src_residual_index = triplets_number * 3;
  (*dest)[dest_residual_index] = b64_alphabet[(src[src_residual_index] >> 2)];
  if (1 == triplets_residual) {
    (*dest)[dest_residual_index + 1] = 
      b64_alphabet[(src[src_residual_index] & two_lsb_mask) << 4]; 
    return encoding_size;
  }
  (*dest)[dest_residual_index + 1] = 
    b64_alphabet[((src[src_residual_index] & two_lsb_mask) << 4) |
    ((src[src_residual_index + 1] & four_msb_mask) >> 4)];
  (*dest)[dest_residual_index + 2] = 
    b64_alphabet[(src[src_residual_index + 1] & four_lsb_mask) << 2];
  return encoding_size;
}

size_t b64_encode_to_string(const uint8_t *const restrict src,
    const size_t src_length, char *restrict *dest) {
  if (NULL == src) {
    *dest = NULL;
    return -1;
  }
  if (0 == src_length) {
    *dest = "";
    return 0;
  }
  uint8_t *result;
  size_t result_length;
  result_length = b64_encode(src, src_length, &result);
  *dest = (char*) result;
  return result_length;
}

size_t b64_decode(const uint8_t *const restrict src, const size_t src_length,
    uint8_t *restrict *dest) {
  return -1;
}

size_t b64_decode_from_string(const char *const restrict src, 
    uint8_t *restrict *dest);

short is_b64(const uint8_t *const bytes, const size_t bytes_count) {
  return -1;
}

short is_b64_string(const char *const string) {
  return -1;
}
