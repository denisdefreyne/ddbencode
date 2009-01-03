/// @file dictionary.h
///
/// @brief Provides dictionary management and encoding functionality.

#include <stdbool.h>
#include <stdlib.h>

/// @brief A dictionary.
///
/// This structure is \em not meant to be used as a general-purpose dictionary as it has not been optimized, and likely never will be.
typedef struct _BEDictionary BEDictionary;

/// @brief Creates a new dictionary with the given keys and values.
///
/// The first argument contains the size of the dictionary, which can be zero.
/// The next arguments are grouped. Each group consists of an argument
/// containing the key, which is a string, followed by an argument indicating
/// the dictionary value type (BE_STRING, BE_INTEGER, BE_LIST, BE_DICTIONARY)
/// and an argument containing the actual value itself. String argument groups
/// have a fourth argument containing the string length.
///
/// For example, the following piece of code creates a dictionary with three
/// elements:
///
/// @code
/// // create a dictionary
/// BEDictionary *dictionary = BEDictionaryCreate(
///     3,                                    // number of elements
///     "name",    BE_STRING,  "denis",    5, // argument group 0
///     "age",     BE_INTEGER, 22,            // argument group 1
///     "hobbies", BE_LIST,    hobbiesList    // argument group 2
/// );
/// @endcode
///
/// Dictionaries created with BEDictionaryCreate() should be deallocated by using BEDictionaryDelete().
///
/// @return The newly created dictionary.
BEDictionary *BEDictionaryCreate(size_t aSize, ...);

/// @brief Deletes the given dictionary.
///
/// The given ditionary will be free()d, but its dictionary items will not.
/// Deleting a dictionary may therefore create a memory leak.
/// BEDictionaryDeleteDeep() deletes a dictionary as well as its dictionary
/// items recursively.
///
/// @param[in] aDictionary The dictionary to delete.
void BEDictionaryDelete(BEDictionary *aDictionary);

/// @brief Deletes the given dictionary along with its dictionary items.
///
/// The given dictionary will be free()d. Each dictionary item will be free()d
/// recursively as well; deleting a dictionary recursively can therefore cause
/// non-allocated dictionary items to be inadvertently free()d. For example, the
/// following piece of code is invalid, as it will cause a constant string to
/// be free()d:
///
/// @code
/// // create a dictionary
/// BEDictionary *dictionary = BEDictionaryCreate(
///     1,                         // a dictionary with one item
///     "bar", BE_STRING, "foo", 3 // first item is the string "foo"
/// );
/// // delete the dictionary recursively (INVALID!)
/// BEDictionaryDeleteDeep(dictionary);
/// @endcode
///
/// @param[in] aDictionary The dictionary to delete recursively.
void BEDictionaryDeleteDeep(BEDictionary *aDictionary);

/// @brief Encodes the given dictionary.
///
/// This function allocates memory for the encoded data; this memory should be
/// free()d once it is no longer necessary.
///
/// @param[in]  aiDictionary The dictionary that should be encoded.
/// @param[out] aoData       A pointer to where the encoded dictionary should be stored.
/// @param[out] aoDataLength The length of the encoded dictionary.
///
/// @return true on success, false on failure.
bool BEDictionaryEncode(BEDictionary *aiDictionary, void **aoData, size_t *aoDataLength);

/// @brief Returns the length of the encoded dictionary.
///
/// This function does not create the encoded dictionary; use
/// BEDictionaryEncode() for that. This function is used by
/// BEDictionaryEncode() to find the amount of memory necessary for encoding
/// the given dictionary. Under normal circumstances, this function should not
/// need to be called directly.
///
/// @param[in] aDictionary The dictionary from which to get the encoded data length.
///
/// @return The given dictionary's encoded data length.
size_t BEDictionaryGetEncodedLength(BEDictionary *aDictionary);
