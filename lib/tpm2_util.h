#ifndef STRING_BYTES_H
#define STRING_BYTES_H

#include <stdbool.h>
#include <stdint.h>

#include <sapi/tpm20.h>

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

#define BUFFER_SIZE(type, field) (sizeof((((type *)NULL)->t.field)))

#define TPM2B_TYPE_INIT(type, field) { .t = { .size = BUFFER_SIZE(type, field), }, }
#define TPM2B_EMPTY_INIT { .t = { .size = 0, }, }
#define SESSION_ATTRIBUTES_INIT(mask) { .val = mask }

#define TPMS_AUTH_COMMAND_INIT(session_handle) { \
        .sessionHandle = session_handle,\
	    .nonce = TPM2B_EMPTY_INIT, \
	    .sessionAttributes = { .val = 0 }, \
	    .hmac = TPM2B_EMPTY_INIT \
    }

#define TPMS_AUTH_COMMAND_EMPTY_INIT TPMS_AUTH_COMMAND_INIT(0)


#define TPMT_TK_CREATION_EMPTY_INIT { \
        .tag = 0, \
		.hierarchy = 0, \
		.digest = TPM2B_EMPTY_INIT \
    }

#define TPML_PCR_SELECTION_EMPTY_INIT { \
        .count = 0, \
    } //ignore pcrSelections since count is 0.

#define TPMS_CAPABILITY_DATA_EMPTY_INIT { \
        .capability = 0, \
    } // ignore data since capability is 0.

#define TPMT_TK_HASHCHECK_EMPTY_INIT { \
		.tag = 0, \
		.hierarchy = 0, \
		.digest = TPM2B_EMPTY_INIT \
    }

int tpm2_util_hex_to_byte_structure(const char *inStr, UINT16 *byteLenth, BYTE *byteBuffer);

/**
 * Appends a TPM2B buffer to a MAX buffer.
 * @param result
 *  The MAX buffer to append to
 * @param append
 *  The buffer to append to result.
 * @return
 *  true on success, false otherwise.
 */
bool tpm2_util_concat_buffer(TPM2B_MAX_BUFFER *result, TPM2B *append);

/**
 * Converts a numerical string into a uint32 value.
 * @param str
 *  The numerical string to convert.
 * @param value
 *  The value to store the conversion into.
 * @return
 *  true on success, false otherwise.
 */
bool tpm2_util_string_to_uint32(const char *str, uint32_t *value);

/**
 * Converts a numerical string into a uint16 value.
 * @param str
 *  The numerical string to convert.
 * @param value
 *  The value to store the conversion into.
 * @return
 *  true on success, false otherwise.
 */
bool tpm2_util_string_to_uint16(const char *str, uint16_t *value);

/**
 * Prints a TPM2B as a hex dump
 * @param buffer the TPM2B to print.
 */
void tpm2_util_print_tpm2b(TPM2B *buffer);

/**
 * Copies a tpm2b from dest to src and clears dest if src is NULL.
 * If src is NULL, it is a NOP.
 * @param dest
 *  The destination TPM2B
 * @param src
 *  The source TPM2B
 * @return
 *  The number of bytes copied.
 */
UINT16 tpm2_util_copy_tpm2b(TPM2B *dest, TPM2B *src);

/**
 * Checks if the host is big endian
 * @return
 *  True of the host is big endian false otherwise.
 */
bool tpm2_util_is_big_endian(void);

/**
 * Swaps the endianess of 16 bit value.
 * @param data
 *  A 16 bit value to swap the endianess on.
 * @return
 * The 16 bit value with the endianess swapped.
 */
UINT16 tpm2_util_endian_swap_16(UINT16 data);

/**
 * Just like string_bytes_endian_convert_16 but for 32 bit values.
 */
UINT32 tpm2_util_endian_swap_32(UINT32 data);

/**
 * Just like string_bytes_endian_convert_16 but for 64 bit values.
 */
UINT64 tpm2_util_endian_swap_64(UINT64 data);

/**
 * Converts a 16 bit value from host endianess to network endianess.
 * @param data
 *  The data to possibly swap endianess.
 * @return
 *  The swapped data.
 */
UINT16 tpm2_util_hton_16(UINT16 data);

/**
 * Just like string_bytes_endian_hton_16 but for 32 bit values.
 */
UINT32 tpm2_util_hton_32(UINT32 data);

/**
 * Just like string_bytes_endian_hton_16 but for 64 bit values.
 */
UINT64 tpm2_util_hton_64(UINT64 data);

/**
 * Converts a 16 bit value from network endianess to host endianess.
 * @param data
 *  The data to possibly swap endianess.
 * @return
 *  The swapped data.
 */
UINT16 tpm2_util_ntoh_16(UINT16 data);

/**
 * Just like string_bytes_endian_ntoh_16 but for 32 bit values.
 */
UINT32 tpm2_util_ntoh_32(UINT32 data);

/**
 * Just like string_bytes_endian_ntoh_16 but for 64 bit values.
 */
UINT64 tpm2_util_ntoh_64(UINT64 data);

#endif /* STRING_BYTES_H */
