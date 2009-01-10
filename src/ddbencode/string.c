#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

BEString *BEStringCreate(char *aCString, size_t aLength)
{
	// Create string
	BEString *string = malloc(sizeof (BEString));
	if(!string)
		return NULL;

	// Initialize
	COInitialize(string);
	COSetDestructor(string, &_BEStringDelete);

	// Set length
	string->length = aLength;

	// Copy C string
	string->cString = malloc((aLength+1)*sizeof(char));
	if(!string->cString)
	{
		free(string);
		return NULL;
	}
	memcpy(string->cString, aCString, aLength);
	string->cString[aLength] = '\0';

	// Done
	return string;
}

bool BEStringEncode(BEString *aiString, void **aoData, size_t *aoDataLength)
{
	// Strings are length-prefixed base ten followed by a colon and the string.
	// For example 4:spam corresponds to 'spam'.

	// Calculate the length of the length (yes, indeed) of the string
	size_t lengthLength;
	if(aiString->length < 2)
		lengthLength = 1;
	else
		lengthLength = (int)log10((double)aiString->length) + 1;

	// Create data
	size_t dataLength = lengthLength + 1 + aiString->length;
	void *data = malloc(dataLength+1);
	if(!data)
		return false;

	// Fill data
	sprintf(data, "%i:", (int)aiString->length);
	memcpy(data+lengthLength+1, aiString->cString, aiString->length);
	((char *)data)[lengthLength+1+aiString->length] = '\0';

	// Return data
	*aoData = data;
	*aoDataLength = dataLength;

	return true;
}

size_t BEStringGetEncodedLength(BEString *aString)
{
	if(aString->length < 2)
		return 1 + 1 + aString->length;
	else
		return (int)log10((double)aString->length) + 1 + 1 + aString->length;
}

void BEStringPrint(BEString *aString)
{
	_BEStringPrint(aString, 0);
}

void _BEStringPrint(BEString *aString, size_t aIndentation)
{
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	printf("\"%s\"\n", aString->cString);
}

void _BEStringDelete(void *aString)
{
	// Delete C string
	free(((BEString *)aString)->cString);
}
