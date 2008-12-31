#include <ddbencode/ddbencode.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void BEIntegerEncode(int aInteger, void **aData, size_t *aDataLength)
{
	// Integers are represented by an 'i' followed by the number in base 10
	// followed by an 'e'. For example i3e corresponds to 3 and i-3e corresponds
	// to -3. Integers have no size limitation. i-0e is invalid. All encodings
	// with a leading zero, such as i03e, are invalid, other than i0e, which of
	// course corresponds to 0.

	// Calculate the length of the integer
	size_t integerLength;
	if(aInteger == 0 || aInteger == 1)
		integerLength = 1;
	else
		integerLength = (int)log10(fabs((double)aInteger)) + 1;
	if(aInteger < 0)
		++integerLength;

	// Create data
	// FIXME check malloc return value
	size_t dataLength = 1 + integerLength + 1;
	void *data = malloc(dataLength+1);

	// Fill data
	sprintf(data, "i%ie", aInteger);

	// Return data
	*aData = data;
	*aDataLength = dataLength;
}

