#include <ddbencode/ddbencode.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

void BEStringEncode(void *aString, size_t aStringLength, void **aData, size_t *aDataLength)
{
	// Strings are length-prefixed base ten followed by a colon and the string.
	// For example 4:spam corresponds to 'spam'.

	// Calculate the length of the length (yes, indeed) of the string
	size_t stringLength = strlen(aString);
	size_t lengthLength;
	if(stringLength < 2)
		lengthLength = 1;
	else
		lengthLength = (int)log10((double)stringLength) + 1;

	// Create data
	// FIXME check malloc return value
	size_t dataLength = lengthLength + 1 + stringLength;
	void *data = malloc(dataLength+1);

	// Fill data
	sprintf(data, "%i:", (int)stringLength);
	memcpy(data+lengthLength+1, aString, aStringLength);
	((char *)data)[lengthLength+1+aStringLength] = '\0';

	// Return data
	*aData = data;
	*aDataLength = dataLength;
}
