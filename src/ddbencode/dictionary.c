#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BEDictionary *BEDictionaryCreate(size_t aSize, ...)
{
	va_list ap;

	// Create dictionary
	BEDictionary *dictionary = malloc(sizeof (BEDictionary));
	if(!dictionary)
		return NULL;
	dictionary->entries = malloc(aSize * (sizeof (struct _BEDictionaryEntry)));
	if(!dictionary->entries)
	{
		free(dictionary);
		return NULL;
	}
	dictionary->size = aSize;

	// Initialize
	COInitialize(dictionary);
	COSetDestructor(dictionary, &_BEDictionaryDelete);

	va_start(ap, aSize);
	for(size_t i = 0; i < aSize; ++i)
	{
		// Set key
		char *key = va_arg(ap, char *);
		dictionary->entries[i].key = BEStringCreate(key, strlen(key));

		// Set value
		switch(va_arg(ap, int))
		{
			case BE_STRING:
				dictionary->entries[i].type = BE_STRING;
				dictionary->entries[i].data.string = va_arg(ap, BEString *);
				CORetain(dictionary->entries[i].data.string);
				break;

			case BE_INTEGER:
				dictionary->entries[i].type = BE_INTEGER;
				dictionary->entries[i].data.integer = va_arg(ap, int);
				break;

			case BE_LIST:
				dictionary->entries[i].type = BE_LIST;
				dictionary->entries[i].data.list = va_arg(ap, BEList *);
				CORetain(dictionary->entries[i].data.list);
				break;

			case BE_DICTIONARY:
				dictionary->entries[i].type = BE_DICTIONARY;
				dictionary->entries[i].data.dictionary = va_arg(ap, BEDictionary *);
				CORetain(dictionary->entries[i].data.dictionary);
				break;

			default:
				CORelease(dictionary);
				return NULL;
		}
	}
	va_end(ap);

	// Done
	return dictionary;
}

bool BEDictionaryEncode(BEDictionary *aiDictionary, void **aoData, size_t *aoDataLength)
{
	// Dictionaries are encoded as a 'd' followed by a list of alternating keys
	// and their corresponding values followed by an 'e'. For example,
	// d3:cow3:moo4:spam4:eggse corresponds to {'cow': 'moo', 'spam': 'eggs'} and
	// d4:spaml1:a1:bee corresponds to {'spam': ['a', 'b']}. Keys must be strings
	// and appear in sorted order (sorted as raw strings, not alphanumerics).

	// Calculate the length of the encoded dictionary
	size_t encodedLength = BEDictionaryGetEncodedLength(aiDictionary);

	// Create data
	void *data = malloc(encodedLength*(sizeof data));
	if(!data)
		return false;

	// Fill data
	((char *)data)[0] = 'd';
	void *currentEnd = data+1;
	for(size_t i = 0; i < aiDictionary->size; ++i)
	{
		// Get entry
		struct _BEDictionaryEntry entry = aiDictionary->entries[i];

		// Encode key
		void   *keyData;
		size_t keyDataLength;
		BEStringEncode(entry.key, &keyData, &keyDataLength);

		// Append encoded key
		memcpy(currentEnd, keyData, keyDataLength);
		currentEnd += keyDataLength;

		// Cleanup
		free(keyData);

		// Encode value
		void   *valueData;
		size_t valueDataLength;
		switch(entry.type)
		{
			case BE_STRING:
				BEStringEncode(entry.data.string, &valueData, &valueDataLength);
				break;

			case BE_INTEGER:
				BEIntegerEncode(entry.data.integer, &valueData, &valueDataLength);
				break;

			case BE_LIST:
				BEListEncode(entry.data.list, &valueData, &valueDataLength);
				break;

			case BE_DICTIONARY:
				BEDictionaryEncode(entry.data.dictionary, &valueData, &valueDataLength);
				break;

			default:
				return false;
		}

		// Append encoded value
		memcpy(currentEnd, valueData, valueDataLength);
		currentEnd += valueDataLength;

		// Cleanup
		free(valueData);
	}
	((char *)data)[encodedLength-1] = 'e';

	// Return data
	*aoData = data;
	*aoDataLength = encodedLength;

	return true;
}

size_t BEDictionaryGetEncodedLength(BEDictionary *aDictionary)
{
	size_t encodedLength = 0;

	// Add start size
	encodedLength += 1;

	// Add sizes of each entry
	for(size_t i = 0; i < aDictionary->size; ++i)
	{
		// Get entry
		struct _BEDictionaryEntry entry = aDictionary->entries[i];

		// Add key length
		encodedLength += BEStringGetEncodedLength(entry.key);

		// Add value length
		switch(entry.type)
		{
			case BE_STRING:
				encodedLength += BEStringGetEncodedLength(entry.data.string);
				break;

			case BE_INTEGER:
				encodedLength += BEIntegerGetEncodedLength(entry.data.integer);
				break;

			case BE_LIST:
				encodedLength += BEListGetEncodedLength(entry.data.list);
				break;

			case BE_DICTIONARY:
				encodedLength += BEDictionaryGetEncodedLength(entry.data.dictionary);
				break;

			default:
				return -1;
		}
	}

	// Add end size
	encodedLength += 1;

	// Done
	return encodedLength;
}

void BEDictionaryPrint(BEDictionary *aDictionary)
{
	_BEDictionaryPrint(aDictionary, 0);
}

void _BEDictionaryPrint(BEDictionary *aDictionary, size_t aIndentation)
{
	// Print {
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	puts("{");

	// Print entries
	for(size_t currentPair = 0; currentPair < aDictionary->size; ++currentPair)
	{
		struct _BEDictionaryEntry *entry = &aDictionary->entries[currentPair];

		for(size_t i = 0; i < aIndentation+1; ++i)
			fputs("    ", stdout);
		printf("\"%s\" =>\n", entry->key->cString);
		switch(entry->type)
		{
			case BE_STRING:
				_BEStringPrint(entry->data.string, aIndentation+2);
				break;

			case BE_INTEGER:
				_BEIntegerPrint(entry->data.integer, aIndentation+2);
				break;

			case BE_LIST:
				_BEListPrint(entry->data.list, aIndentation+2);
				break;

			case BE_DICTIONARY:
				_BEDictionaryPrint(entry->data.dictionary, aIndentation+2);
				break;
		}
	}

	// Print }
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	puts("}");
}

void _BEDictionaryDelete(void *aDictionary)
{
	// Release entries
	for(size_t i = 0; i < ((BEDictionary *)aDictionary)->size; ++i)
	{
		struct _BEDictionaryEntry entry = ((BEDictionary *)aDictionary)->entries[i];
		CORelease(entry.key);
		switch(entry.type)
		{
			case BE_STRING:
				CORelease(entry.data.string);
				break;

			case BE_INTEGER:
				;
				break;

			case BE_LIST:
				CORelease(entry.data.list);
				break;

			case BE_DICTIONARY:
				CORelease(entry.data.dictionary);
				break;
		}
	}

	// Delete entries array
	if(((BEDictionary *)aDictionary)->entries)
		free(((BEDictionary *)aDictionary)->entries);
}
