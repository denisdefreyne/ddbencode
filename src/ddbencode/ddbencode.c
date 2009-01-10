#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool _BEDecode_string(void *aiData, size_t aiLength, BEType *aoType, BEString **aoString, size_t *aoUsedLength);
static bool _BEDecode_integer(void *aiData, size_t aiLength, BEType *aoType, int *aoInteger, size_t *aoUsedLength);
static bool _BEDecode_list(void *aiData, size_t aiLength, BEType *aoType, BEList **aoList, size_t *aoUsedLength);
static bool _BEDecode_dictionary(void *aiData, size_t aiLength, BEType *aoType, BEDictionary **aoDictionary, size_t *aoUsedLength);

bool BEDecode(void *aiData, size_t aiLength, BEType *aoType, BEString **aoString, int *aoInteger, BEList **aoList, BEDictionary **aoDictionary, size_t *aoUsedLength)
{
	// Validate length
	if(aiLength < 2)
		return false;

	switch(((char *)aiData)[0])
	{
		case '0'...'9': return _BEDecode_string(aiData, aiLength, aoType, aoString, aoUsedLength);
		case 'i':       return _BEDecode_integer(aiData, aiLength, aoType, aoInteger, aoUsedLength);
		case 'l':       return _BEDecode_list(aiData, aiLength, aoType, aoList, aoUsedLength);
		case 'd':       return _BEDecode_dictionary(aiData, aiLength, aoType, aoDictionary, aoUsedLength);
		default:        return false;
	}
}

static bool _BEDecode_string(void *aiData, size_t aiLength, BEType *aoType, BEString **aoString, size_t *aoUsedLength)
{
	// String, e.g. 4:spam

	// Get string length
	int length = 0;
	size_t i;
	for(i = 0; ((char *)aiData)[i] != ':'; ++i)
	{
		// Get and validate char
		char thisChar = ((char *)aiData)[i];
		if(thisChar < '0' || thisChar > '9')
			return false;

		// Add to length
		length *= 10;
		length += (thisChar - '0');

		// Validate length
		if(i+1 >= aiLength)
			return false;
	}

	// Validate numbers
	if(i == 0)
		return false;

	// Validate length
	if(i + 1 + length > aiLength)
		return false;

	// Create string
	BEString *string = BEStringCreate(aiData+i+1, length);
	if(!string)
		return false;

	// Set result
	*aoType = BE_STRING;
	*aoString = string;
	if(aoUsedLength)
		*aoUsedLength = i + 1 + length;
	return true;
}

static bool _BEDecode_integer(void *aiData, size_t aiLength, BEType *aoType, int *aoInteger, size_t *aoUsedLength)
{
	// Integer, e.g. i3e

	// Check presence of minus sign
	bool isNegative = (((char *)aiData)[1] == '-');

	// Validate length
	if(aiLength < (isNegative ? 4 : 3))
		return false;

	// Get integer
	int integer = 0;
	size_t i;
	for(i = (isNegative ? 2 : 1); ((char *)aiData)[i] != 'e'; ++i)
	{
		// Get and validate char
		char thisChar = ((char *)aiData)[i];
		if(thisChar < '0' || thisChar > '9')
			return false;

		// Add to integer
		integer *= 10;
		integer += (thisChar - '0');

		// Validate length
		if(i+1 >= aiLength)
			return false;
	}
	if(isNegative)
		integer = -integer;

	// Validate numbers
	if(i == (isNegative ? 2 : 1))
		return false;

	// Set result
	*aoType = BE_INTEGER;
	*aoInteger = integer;
	if(aoUsedLength)
		*aoUsedLength = i+1;
	return true;
}

static bool _BEDecode_list(void *aiData, size_t aiLength, BEType *aoType, BEList **aoList, size_t *aoUsedLength)
{
	// List, e.g. l4:spam4:eggse

	// Create list
	BEList *list = malloc(sizeof (BEList));
	if(!list)
		return NULL;
	list->entries = NULL;
	list->size = 0;

	// Initialize
	COInitialize(list);
	COSetDestructor(list, &_BEListDelete);

	// Look for list items
	size_t currentStart = 1;
	while(((char *)aiData)[currentStart] != 'e')
	{
		BEType subType;

		BEString     *subString     = NULL;
		int          subInteger;
		BEList       *subList       = NULL;
		BEDictionary *subDictionary = NULL;

		size_t subUsedLength;

		// Decode one sub-item
		bool success = BEDecode(
			aiData+currentStart, aiLength-currentStart-1,
			&subType,
			&subString, &subInteger, &subList, &subDictionary,
			&subUsedLength
		);

		// Check for errors
		if(!success)
		{
			// Cleanup
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(list);

			return false;
		}

		// Expand list
		// FIXME optimize by getting rid of realloc
		struct _BEListEntry *entries = realloc(list->entries, (list->size+1)*sizeof (struct _BEListEntry));
		if(!entries)
		{
			// Cleanup
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(list);

			return false;
		}
		list->entries = entries;
		list->size++;

		// Fill list
		switch(subType)
		{
			case BE_STRING:
				list->entries[list->size-1].type = BE_STRING;
				list->entries[list->size-1].data.string = subString;
				break;

			case BE_INTEGER:
				list->entries[list->size-1].type = BE_INTEGER;
				list->entries[list->size-1].data.integer = subInteger;
				break;

			case BE_LIST:
				list->entries[list->size-1].type = BE_LIST;
				list->entries[list->size-1].data.list = subList;
				break;

			case BE_DICTIONARY:
				list->entries[list->size-1].type = BE_DICTIONARY;
				list->entries[list->size-1].data.dictionary = subDictionary;
				break;
		}

		// Move to next
		currentStart += subUsedLength;
	}

	// Set result
	*aoType = BE_LIST;
	*aoList = list;
	if(aoUsedLength)
		*aoUsedLength = currentStart+1;
	return true;
}

static bool _BEDecode_dictionary(void *aiData, size_t aiLength, BEType *aoType, BEDictionary **aoDictionary, size_t *aoUsedLength)
{
	// Dictionary, e.g. d3:cow3:moo4:spam4:eggse

	// Create dictionary
	BEDictionary *dictionary = malloc(sizeof (BEDictionary));
	if(!dictionary)
		return NULL;
	dictionary->entries = NULL;
	dictionary->size = 0;

	// Initialize
	COInitialize(dictionary);
	COSetDestructor(dictionary, &_BEDictionaryDelete);

	// Look for dictionary items
	size_t currentStart = 1;
	while(((char *)aiData)[currentStart] != 'e')
	{
		BEType subType;

		BEString     *subKey        = NULL;
		BEString     *subString     = NULL;
		int          subInteger;
		BEList       *subList       = NULL;
		BEDictionary *subDictionary = NULL;

		bool success;
		size_t subUsedLength;

		// Decode key
		// FIXME check whether aiLength-currentStart-1 doesn't become negative
		success = BEDecode(
			aiData+currentStart, aiLength-currentStart-1,
			&subType,
			&subKey, &subInteger, &subList, &subDictionary,
			&subUsedLength
		);

		// Check for errors
		if(!success || subType != BE_STRING)
		{
			// Cleanup
			if(subKey)
				CORelease(subKey);
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(dictionary);

			return false;
		}

		// Move to value
		currentStart += subUsedLength;

		// Decode value
		// FIXME check whether aiLength-currentStart-1 doesn't become negative
		success = BEDecode(
			aiData+currentStart, aiLength-currentStart-1,
			&subType,
			&subString, &subInteger, &subList, &subDictionary,
			&subUsedLength
		);

		// Check for errors
		if(!success)
		{
			// Cleanup
			if(subKey)
				CORelease(subKey);
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(dictionary);

			return false;
		}

		// Expand dictionary
		// FIXME optimize by getting rid of realloc
		struct _BEDictionaryEntry *entries = realloc(dictionary->entries, (dictionary->size+1)*sizeof (struct _BEDictionaryEntry));
		if(!entries)
		{
			// Cleanup
			if(subKey)
				CORelease(subKey);
			if(subString)
				CORelease(subString);
			if(subList)
				CORelease(subList);
			if(subDictionary)
				CORelease(subDictionary);
			CORelease(dictionary);

			return false;
		}
		dictionary->entries = entries;
		dictionary->size++;

		// Fill dictionary
		dictionary->entries[dictionary->size-1].key = subKey;
		switch(subType)
		{
			case BE_STRING:
				dictionary->entries[dictionary->size-1].type = BE_STRING;
				dictionary->entries[dictionary->size-1].data.string = subString;
				break;

			case BE_INTEGER:
				dictionary->entries[dictionary->size-1].type = BE_INTEGER;
				dictionary->entries[dictionary->size-1].data.integer = subInteger;
				break;

			case BE_LIST:
				dictionary->entries[dictionary->size-1].type = BE_LIST;
				dictionary->entries[dictionary->size-1].data.list = subList;
				break;

			case BE_DICTIONARY:
				dictionary->entries[dictionary->size-1].type = BE_DICTIONARY;
				dictionary->entries[dictionary->size-1].data.dictionary = subDictionary;
				break;
		}

		// Move to next pair
		currentStart += subUsedLength;
	}

	// Set result
	*aoType = BE_DICTIONARY;
	*aoDictionary = dictionary;
	if(aoUsedLength)
		*aoUsedLength = currentStart+1;
	return true;
}
