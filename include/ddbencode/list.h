/// @file list.h
///
/// @brief Provides list management and encoding functionality.

#include <stdbool.h>
#include <stdlib.h>

/// @brief A list.
///
/// This structure is \em not meant to be used as a general-purpose list as it
/// has not been optimized, and likely never will be.
typedef struct _BEList BEList;

/// @brief Creates a new list with the given elements.
///
/// The first argument contains the size of the list, which can be zero. The
/// next arguments are grouped. Each group consists of an argument containing
/// the list item type (BE_STRING, BE_INTEGER, BE_LIST, BE_DICTIONARY) and an
/// argument containing the actual item itself.
///
/// For example, the following piece of code creates a list with three
/// elements:
///
/// @code
/// // create a list
/// // someString is a BEString *
/// BEList *list = BEListCreate(
///     3,                            // number of elements
///     BE_STRING,     someString,    // argument group 0
///     BE_INTEGER,    123,           // argument group 1
///     BE_DICTIONARY, someDictionary // argument group 2
/// );
/// @endcode
/// Lists created with BEListCreate() should be released using
/// CORelease(). All strings, lists and dictionaries passed to
/// BEListCreate() are retained by the list.
///
/// @return The newly created list.
BEList *BEListCreate(size_t aSize, ...);

/// @brief Encodes the given list.
///
/// This function allocates memory for the encoded data; this memory should be
/// free()d once it is no longer necessary.
///
/// @param[in]  aiList       The list that should be encoded.
/// @param[out] aoData       A pointer to where the encoded list should be stored.
/// @param[out] aoDataLength The length of the encoded list.
///
/// @return true on success, false on failure.
bool BEListEncode(BEList *aiList, void **aoData, size_t *aoDataLength);

/// @brief Returns the length of the encoded list.
///
/// This function does not create the encoded list; use BEListEncode() for
/// that. This function is used by BEListEncode() to find the amount of memory
/// necessary for encoding the given list. Under normal circumstances, this
/// function should not need to be called directly.
///
/// @param[in] aList The list from which to get the encoded data length.
///
/// @return The given list's encoded data length.
size_t BEListGetEncodedLength(BEList *aList);

/// @brief Prints the given list to stdout.
///
/// @param[in] aList The list to print.
void BEListPrint(BEList *aList);
