#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BEList *BEListCreate(size_t aSize, ...)
{
	va_list ap;

	// Create list
	BEList *list = malloc(sizeof (BEList));
	if(!list)
		return NULL;
	list->entries = malloc(aSize * (sizeof (struct _BEListEntry)));
	if(!list->entries)
	{
		free(list);
		return NULL;
	}
	list->size = aSize;

	// Initialize
	COInitialize(list);
	COSetDestructor(list, &_BEListDelete);

	va_start(ap, aSize);
	for(size_t i = 0; i < aSize; ++i)
	{
		switch(va_arg(ap, int))
		{
			case BE_STRING:
				list->entries[i].type = BE_STRING;
				list->entries[i].data.string = va_arg(ap, BEString *);
				CORetain(list->entries[i].data.string);
				break;

			case BE_INTEGER:
				list->entries[i].type = BE_INTEGER;
				list->entries[i].data.integer = va_arg(ap, int);
				break;

			case BE_LIST:
				list->entries[i].type = BE_LIST;
				list->entries[i].data.list = va_arg(ap, BEList *);
				CORetain(list->entries[i].data.list);
				break;

			case BE_DICTIONARY:
				list->entries[i].type = BE_DICTIONARY;
				list->entries[i].data.dictionary = va_arg(ap, BEDictionary *);
				CORetain(list->entries[i].data.dictionary);
				break;

			default:
				CORelease(list);
				return NULL;
		}
	}
	va_end(ap);

	// Done
	return list;
}

bool BEListEncode(BEList *aiList, void **aoData, size_t *aoDataLength)
{
	// Lists are encoded as an 'l' followed by their elements (also bencoded)
	// followed by an 'e'. For example l4:spam4:eggse corresponds to ['spam',
	// 'eggs'].

	// Calculate the length of the encoded list
	size_t encodedLength = BEListGetEncodedLength(aiList);

	// Create data
	void *data = malloc(encodedLength*(sizeof data));
	if(!data)
		return false;

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
				BEStringEncode(entry.data.string, &entryData, &entryDataLength);
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
				return false;
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

	return true;
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

	// Done
	return encodedLength;
}

void BEListPrint(BEList *aList)
{
	_BEListPrint(aList, 0);
}

void _BEListPrint(BEList *aList, size_t aIndentation)
{
	// Print [
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	puts("[");

	// Print entries
	for(size_t currentItem = 0; currentItem < aList->size; ++currentItem)
	{
		struct _BEListEntry *entry = &aList->entries[currentItem];

		switch(entry->type)
		{
			case BE_STRING:
				_BEStringPrint(entry->data.string, aIndentation+1);
				break;

			case BE_INTEGER:
				_BEIntegerPrint(entry->data.integer, aIndentation+1);
				break;

			case BE_LIST:
				_BEListPrint(entry->data.list, aIndentation+1);
				break;

			case BE_DICTIONARY:
				_BEDictionaryPrint(entry->data.dictionary, aIndentation+1);
				break;
		}
	}

	// Print ]
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	puts("]");
}

void _BEListDelete(void *aList)
{
	// Release entries
	for(size_t i = 0; i < ((BEList *)aList)->size; ++i)
	{
		struct _BEListEntry entry = ((BEList *)aList)->entries[i];
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
	if(((BEList *)aList)->entries)
		free(((BEList *)aList)->entries);
}
