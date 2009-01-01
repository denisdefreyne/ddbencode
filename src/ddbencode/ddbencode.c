#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool _BEDecode_string(void *aiData, size_t aiLength, BEType *aoType, char **aoString, size_t *aoStringLength, size_t *aoUsedLength);
static bool _BEDecode_integer(void *aiData, size_t aiLength, BEType *aoType, int *aoInteger, size_t *aoUsedLength);
static bool _BEDecode_list(void *aiData, size_t aiLength, BEType *aoType, BEList **aoList, size_t *aoUsedLength);
static bool _BEDecode_dictionary(void *aiData, size_t aiLength, BEType *aoType, BEDictionary **aoDictionary, size_t *aoUsedLength);

bool BEDecode(void *aiData, size_t aiLength, BEType *aoType, char **aoString, int *aoInteger, BEList **aoList, BEDictionary **aoDictionary, size_t *aoStringLength, size_t *aoUsedLength)
{
	// Validate length
	if(aiLength < 2)
		return false;

	switch(((char *)aiData)[0])
	{
		case '0'...'9': return _BEDecode_string(aiData, aiLength, aoType, aoString, aoStringLength, aoUsedLength);
		case 'i':       return _BEDecode_integer(aiData, aiLength, aoType, aoInteger, aoUsedLength);
		case 'l':       return _BEDecode_list(aiData, aiLength, aoType, aoList, aoUsedLength);
		case 'd':       return _BEDecode_dictionary(aiData, aiLength, aoType, aoDictionary, aoUsedLength);
		default:        return false;
	}
}

static bool _BEDecode_string(void *aiData, size_t aiLength, BEType *aoType, char **aoString, size_t *aoStringLength, size_t *aoUsedLength)
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

	// Get string
	char *string = malloc((length+1)*sizeof (char));
	if(!string)
		return false;
	memcpy(string, aiData+i+1, length);
	string[length] = '\0';

	// Set result
	*aoType = BE_STRING;
	*aoString = string;
	if(aoStringLength)
		*aoStringLength = length;
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

	// TODO implement
	return false;
}

static bool _BEDecode_dictionary(void *aiData, size_t aiLength, BEType *aoType, BEDictionary **aoDictionary, size_t *aoUsedLength)
{
	// Dictionary, e.g. d3:cow3:moo4:spam4:eggse

	// TODO implement
	return false;
}
