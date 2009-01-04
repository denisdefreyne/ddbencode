/// @file integer.h
///
/// @brief Provides integer encoding functionality.

#include <stdbool.h>
#include <stdlib.h>

/// @brief Encodes the given integer.
///
/// This function allocates memory for the encoded data; this memory should be
/// free()d once it is no longer necessary.
///
/// @param[in]  aiInteger    The integer that should be encoded.
/// @param[out] aoData       A pointer to where the encoded integer should be stored.
/// @param[out] aoDataLength The length of the encoded integer.
///
/// @return true on success, false on failure.
bool BEIntegerEncode(int aiInteger, void **aoData, size_t *aoDataLength);

/// @brief Returns the length of the encoded integer.
///
/// This function does not create the encoded integer; use BEIntegerEncode()
/// for that. This function is used by BEIntegerEncode() to find the amount of
/// memory necessary for encoding the given integer. Under normal
/// circumstances, this function should not need to be called directly.
///
/// @param[in] aInteger The integer from which to get the encoded data length.
///
/// @return The given integer's encoded data length.
size_t BEIntegerGetEncodedLength(int aInteger);

/// @brief Prints the given integer to stdout.
///
/// @param[in] aInteger The integer to print.
void BEIntegerPrint(int aInteger);
