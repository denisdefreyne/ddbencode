/// @file string.h
///
/// @brief Provides string encoding functionality.

#include <stdbool.h>
#include <stdlib.h>

/// @brief A string.
///
/// This structure is \em not meant to be used as a general-purpose string as
/// it has not been optimized, and likely never will be.
typedef struct _BEString BEString;

/// @brief Creates a new string with the given C string and length.
///
/// The given string can contain "null" characters. These do not indicate the
/// length of the string; the length of the string is determined by the length
/// argument.
///
/// @param[in] aCString The C string from which the string should be created.
/// @param[in] aLength	The length of the given C string.
///
/// Strings created with BEStringCreate() should be released using
/// CORelease().
///
/// @return The newly created string.
BEString *BEStringCreate(char *aCString, size_t aLength);

/// @brief Encodes the given string.
///
/// This function allocates memory for the encoded data; this memory should be
/// free()d once it is no longer necessary.
///
/// @param[in]  aiString       The string that should be encoded.
/// @param[out] aoData         A pointer to where the encoded string should be stored.
/// @param[out] aoDataLength   The length of the encoded string.
///
/// @return true on success, false on failure.
bool BEStringEncode(BEString *aiString, void **aoData, size_t *aoDataLength);

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
size_t BEStringGetEncodedLength(BEString *aString);

/// @brief Prints the given string to stdout.
///
/// @param[in] aString The string to print.
void BEStringPrint(BEString *aString);
