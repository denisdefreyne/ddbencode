/// @file string.h
///
/// @brief Provides string encoding functionality.

#include <stdbool.h>
#include <stdlib.h>

/// @brief Encodes the given string.
///
/// This function allocates memory for the encoded data; this memory should be
/// free()d once it is no longer necessary.
///
/// @param[in]  aiString       The byte string that should be encoded.
/// @param[in]  aiStringLength The length of the byte string that should be encoded.
/// @param[out] aoData         A pointer to where the encoded string should be stored.
/// @param[out] aoDataLength   The length of the encoded string.
///
/// @return true on success, false on failure.
bool BEStringEncode(void *aiString, size_t aiStringLength, void **aoData, size_t *aoDataLength);

/// @brief Returns the length of the encoded string.
///
/// This function does not create the encoded string; use BEStringEncode() for
/// that. This function is used by BEStringEncode() to find the amount of
/// memory necessary for encoding the given string. Under normal
/// circumstances, this function should not need to be called directly.
///
/// @param[in] aString The string from which to get the encoded data length.
///
/// @return The given string's encoded data length.
size_t BEStringGetEncodedLength(void *aString);

/// @brief Prints the given string to stdout.
///
/// @param[in] aString The string to print.
void BEStringPrint(char *aString);
