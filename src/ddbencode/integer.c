#include <ddbencode/ddbencode.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

bool BEIntegerEncode(int aiInteger, void **aoData, size_t *aoDataLength)
{
	// Integers are represented by an 'i' followed by the number in base 10
	// followed by an 'e'. For example i3e corresponds to 3 and i-3e corresponds
	// to -3. Integers have no size limitation. i-0e is invalid. All encodings
	// with a leading zero, such as i03e, are invalid, other than i0e, which of
	// course corresponds to 0.

	// Calculate the length of the integer
	size_t integerLength;
	if(aiInteger == 0 || aiInteger == 1)
		integerLength = 1;
	else
		integerLength = (int)log10(fabs((double)aiInteger)) + 1;
	if(aiInteger < 0)
		++integerLength;

	// Create data
	size_t dataLength = 1 + integerLength + 1;
	void *data = malloc(dataLength+1);
	if(!data)
		return false;

	// Fill data
	sprintf(data, "i%ie", aiInteger);

	// Return data
	*aoData = data;
	*aoDataLength = dataLength;

	return true;
}

size_t BEIntegerGetEncodedLength(int aInteger)
{
	// Get length of integer
	size_t integerLength;
	if(aInteger == 0 || aInteger == 1)
		integerLength = 1;
	else
		integerLength = (int)log10(fabs((double)aInteger)) + 1;
	if(aInteger < 0)
		++integerLength;

	// Add begin and end marker lengths
	return 1 + integerLength + 1;
}

void _BEIntegerPrint(int aInteger, size_t aIndentation)
{
	for(size_t i = 0; i < aIndentation; ++i)
		fputs("    ", stdout);
	printf("%i\n", aInteger);
}

void BEIntegerPrint(int aInteger)
{
	_BEIntegerPrint(aInteger, 0);
}
