#include <ddbencode/ddbencode.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

bool BEStringEncode(void *aiString, size_t aiStringLength, void **aoData, size_t *aoDataLength)
{
	// Strings are length-prefixed base ten followed by a colon and the string.
	// For example 4:spam corresponds to 'spam'.

	// Calculate the length of the length (yes, indeed) of the string
	size_t stringLength = strlen(aiString);
	size_t lengthLength;
	if(stringLength < 2)
		lengthLength = 1;
	else
		lengthLength = (int)log10((double)stringLength) + 1;

	// Create data
	size_t dataLength = lengthLength + 1 + stringLength;
	void *data = malloc(dataLength+1);
	if(!data)
		return false;

	// Fill data
	sprintf(data, "%i:", (int)stringLength);
	memcpy(data+lengthLength+1, aiString, aiStringLength);
	((char *)data)[lengthLength+1+aiStringLength] = '\0';

	// Return data
	*aoData = data;
	*aoDataLength = dataLength;

	return true;
}

size_t BEStringGetEncodedLength(void *aString)
{
	size_t stringLength = strlen(aString);
	if(stringLength < 2)
		return 1 + 1 + stringLength;
	else
		return (int)log10((double)stringLength) + 1 + 1 + stringLength;
}

void _BEStringPrint(char *aString, size_t aIndentation)
{
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	printf("\"%s\"\n", aString);
}

void BEStringPrint(char *aString)
{
	_BEStringPrint(aString, 0);
}
