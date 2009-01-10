/// @file ddbencode.h
///
/// @brief Provides general decoding functionality.

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <ddbencode/string.h>
#include <ddbencode/integer.h>
#include <ddbencode/list.h>
#include <ddbencode/dictionary.h>

/// @mainpage ddbencode source code documentation
///
/// Header files part of ddbencode:
/// - ddbencode.h
/// - string.h
/// - integer.h
/// - list.h
/// - dictionary.h
///
/// Encoding:
/// - BEStringEncode()
/// - BEIntegerEncode()
/// - BEListEncode()
/// - BEDictionaryEncode()
///
/// Decoding:
/// - BEDecode()
///
/// Creating strings, lists and dictionaries:
/// - BEStringCreate()
/// - BEListCreate()
/// - BEDictionaryCreate()

/// The item types that can be encoded and/or used in lists and dictionaries.
typedef enum {
	BE_STRING     = 1,
	BE_INTEGER    = 2,
	BE_LIST       = 3,
	BE_DICTIONARY = 4,
} BEType;

/// @brief Decodes the given data.
///
/// This function takes the actual data as well as its length as the first two
/// arguments. It will then decode the given data while performing sanity
/// checks to ensure that the given data is valid; if it is not valid, false
/// is returned and none of the outgoing arguments will be set. Depending on
/// the type of the decoded item, one of the four outgoing item arguments will
/// be set.
///
/// All parameters, with the exception of used length, are required and
/// assumed to be non-NULL.
///
/// The data returned by this function is newly allocated into memory and
/// should be cleaned up to prevent memory leaks. Strings should be free()d,
/// while strings, lists and dictionaries should be released using
/// CORelease().
///
/// Even though the data could possibly hold two or more encoded items, only
/// the first item will be decoded. The number of bytes used for decoding will
/// be returned in order to allow decoding the next item. This should usually
/// not be necessary, as the content of a torrent file consists of a single
/// bencoded dictionary.
///
/// @param[in]  aiData         A pointer to the encoded data that should be decoded.
/// @param[in]  aiLength       The length of the encoded data.
/// @param[out] aoType         The type of the decoded item.
/// @param[out] aoString       The decoded item, if the item is a string.
/// @param[out] aoInteger      The decoded item, if the item is a integer.
/// @param[out] aoList         The decoded item, if the item is a list.
/// @param[out] aoDictionary   The decoded item, if the item is a dictionary.
/// @param[out] aoUsedLength   The number of bytes that were necessary to decode the item. Can be NULL.
///
/// @return true on success, false on failure.
bool BEDecode(
	void *aiData, size_t aiLength,
	BEType *aoType,
	BEString **aoString, int *aoInteger, BEList **aoList, BEDictionary **aoDictionary,
	size_t *aoUsedLength
);
