#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

BEList *BEListCreate(size_t aSize, ...)
{
	va_list ap;

	// Create list
	// FIXME check malloc return value
	BEList *list = malloc(sizeof (BEList));
	list->entries = malloc(aSize * (sizeof (struct _BEListEntry)));
	list->size = aSize;

	va_start(ap, aSize);
	for(size_t i = 0; i < aSize; ++i)
	{
		switch(va_arg(ap, int))
		{
			case BE_STRING:
				// TODO decide whether the string should be retained (dup'ed) or not
				list->entries[i].type = BE_STRING;
				list->entries[i].data.string = va_arg(ap, char *);
				list->entries[i].stringLength = va_arg(ap, size_t);
				break;

			case BE_INTEGER:
				list->entries[i].type = BE_INTEGER;
				list->entries[i].data.integer = va_arg(ap, int);
				break;

			case BE_LIST:
				list->entries[i].type = BE_LIST;
				list->entries[i].data.list = va_arg(ap, BEList *);
				break;

			case BE_DICTIONARY:
				list->entries[i].type = BE_DICTIONARY;
				list->entries[i].data.dictionary = va_arg(ap, BEDictionary *);
				break;

			default:
				free(list->entries);
				free(list);
				return NULL;
		}
	}
	va_end(ap);

	// Done
	return list;
}

void BEListDelete(BEList *aList)
{
	free(aList->entries);
	free(aList);
}

void BEListEncode(BEList *aiList, void **aoData, size_t *aoDataLength)
{
	// Lists are encoded as an 'l' followed by their elements (also bencoded)
	// followed by an 'e'. For example l4:spam4:eggse corresponds to ['spam',
	// 'eggs'].

	// Calculate the length of the encoded list
	size_t encodedLength = BEListGetEncodedLength(aiList);

	// Create data
	// FIXME check malloc return value
	void *data = malloc(encodedLength*(sizeof data));

	// Fill data
	((char *)data)[0] = 'l';
	void *currentEnd = data+1;
	for(size_t i = 0; i < aiList->size; ++i)
	{
		// Get entry
		struct _BEListEntry entry = aiList->entries[i];

		// Encode entry
		void   *entryData;
		size_t entryDataLength;
		switch(entry.type)
		{
			case BE_STRING:
				BEStringEncode(entry.data.string, entry.stringLength, &entryData, &entryDataLength);
				break;

			case BE_INTEGER:
				BEIntegerEncode(entry.data.integer, &entryData, &entryDataLength);
				break;

			case BE_LIST:
				BEListEncode(entry.data.list, &entryData, &entryDataLength);
				break;

			case BE_DICTIONARY:
				BEDictionaryEncode(entry.data.dictionary, &entryData, &entryDataLength);
				break;

			default:
				return;
		}

		// Append entry data
		memcpy(currentEnd, entryData, entryDataLength);
		currentEnd += entryDataLength;

		// Cleanup
		free(entryData);
	}
	((char *)data)[encodedLength-1] = 'e';

	// Return data
	*aoData = data;
	*aoDataLength = encodedLength;
}

size_t BEListGetEncodedLength(BEList *aList)
{
	size_t encodedLength = 0;

	// Add start size
	encodedLength += 1;

	// Add sizes of each entry
	for(size_t i = 0; i < aList->size; ++i)
	{
		struct _BEListEntry entry = aList->entries[i];
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

	// TODO implement
	return encodedLength;
}
