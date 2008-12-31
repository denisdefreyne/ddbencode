#include <ddbencode/ddbencode.h>

#include <stdbool.h>
#include <stdlib.h>

BEDictionary *BEDictionaryCreate(void *args, ...)
{
	// TODO implement
	return NULL;
}

void BEDictionaryDelete(BEDictionary *aDictionary)
{
	// TODO implement
}

bool BEDictionaryEncode(BEDictionary *aiDictionary, void **aoData, size_t *aoDataLength)
{
	// Dictionaries are encoded as a 'd' followed by a list of alternating keys
	// and their corresponding values followed by an 'e'. For example,
	// d3:cow3:moo4:spam4:eggse corresponds to {'cow': 'moo', 'spam': 'eggs'} and
	// d4:spaml1:a1:bee corresponds to {'spam': ['a', 'b']}. Keys must be strings
	// and appear in sorted order (sorted as raw strings, not alphanumerics).

	// TODO implement
	return false;
}

size_t BEDictionaryGetEncodedLength(BEDictionary *aDictionary)
{
	// TODO implement
	return 0;
}
