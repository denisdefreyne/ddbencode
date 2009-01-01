#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

BEDictionary *BEDictionaryCreate(size_t aSize, ...)
{
	va_list ap;

	// Create dictionary
	BEDictionary *dictionary = malloc(sizeof (BEDictionary));
	if(!dictionary)
		return NULL;
	dictionary->entries = malloc(aSize * (sizeof (struct _BEDictionaryEntry)));
	if(!dictionary->entries)
		return NULL;
	dictionary->size = aSize;

	va_start(ap, aSize);
	for(size_t i = 0; i < aSize; ++i)
	{
		// Set key
		dictionary->entries[i].key = va_arg(ap, char *);

		// Set value
		switch(va_arg(ap, int))
		{
			case BE_STRING:
				dictionary->entries[i].type = BE_STRING;
				dictionary->entries[i].data.string = va_arg(ap, char *);
				dictionary->entries[i].stringLength = va_arg(ap, size_t);
				break;

			case BE_INTEGER:
				dictionary->entries[i].type = BE_INTEGER;
				dictionary->entries[i].data.integer = va_arg(ap, int);
				break;

			case BE_LIST:
				dictionary->entries[i].type = BE_LIST;
				dictionary->entries[i].data.list = va_arg(ap, BEList *);
				break;

			case BE_DICTIONARY:
				dictionary->entries[i].type = BE_DICTIONARY;
				dictionary->entries[i].data.dictionary = va_arg(ap, BEDictionary *);
				break;

			default:
				// FIXME delete everything properly
				free(dictionary->entries);
				free(dictionary);
				return NULL;
		}
	}
	va_end(ap);

	// Done
	return dictionary;
}

void BEDictionaryDelete(BEDictionary *aDictionary)
{
	free(aDictionary->entries);
	free(aDictionary);
}

void BEDictionaryDeleteDeep(BEDictionary *aDictionary)
{
	// Delete entries
	for(size_t i = 0; i < aDictionary->size; ++i)
	{
		struct _BEDictionaryEntry entry = aDictionary->entries[i];
		free(entry.key);
		switch(entry.type)
		{
			case BE_STRING:
				free(entry.data.string);
				break;

			case BE_LIST:
				BEListDeleteDeep(entry.data.list);
				break;

			case BE_DICTIONARY:
				BEDictionaryDeleteDeep(entry.data.dictionary);
				break;
		}
	}

	// Delete dictionary itself
	BEDictionaryDelete(aDictionary);
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
