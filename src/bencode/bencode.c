#include <bencode/bencode.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct _BEListEntry
{
	BEType type;
	void *data;
};

struct _BEList
{
	struct _BEListEntry *entries;
	size_t length;
};

struct _BEDictionaryEntry
{
	char *key;
	BEType valueType;
	void *value;
};

struct _BEDictionary
{
	struct _BEDictionaryEntry *entries;
	size_t length;
};

/* ---------- LIST CREATION/DELETION ---------- */

BEList *BEListCreate(void *args, ...)
{
	// TODO implement
	return NULL;
}

void BEListDelete(BEList *aList)
{
	// TODO implement
	;
}

/* ---------- DICTIONARY CREATION/DELETION ---------- */

BEDictionary *BEDictionaryCreate(void *args, ...)
{
	// TODO implement
	return NULL;
}

void BEDictionaryDelete(BEDictionary *aDictionary)
{
	// TODO implement
}

/* ---------- ENCODING ---------- */

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

void BEListEncode(BEList *aList, void **aData, size_t *aDataLength)
{
	// Lists are encoded as an 'l' followed by their elements (also bencoded)
	// followed by an 'e'. For example l4:spam4:eggse corresponds to ['spam',
	// 'eggs'].

	// TODO implement
}

void BEDictionaryEncode(BEDictionary *aDictionary, void **aData, size_t *aDataLength)
{
	// Dictionaries are encoded as a 'd' followed by a list of alternating keys
	// and their corresponding values followed by an 'e'. For example,
	// d3:cow3:moo4:spam4:eggse corresponds to {'cow': 'moo', 'spam': 'eggs'} and
	// d4:spaml1:a1:bee corresponds to {'spam': ['a', 'b']}. Keys must be strings
	// and appear in sorted order (sorted as raw strings, not alphanumerics).

	// TODO implement
}

/* ---------- DECODING ---------- */

void *BEDecode(void *aData, size_t aLength, BEType *aType)
{
	switch(((char *)aData)[0])
	{
		// Integer, e.g. i3e
		case 'i':
			{
				// Check presence of minus sign
				bool isNegative = (((char *)aData)[1] == '-');

				// Get integer
				int integer = 0;
				for(size_t i = (isNegative ? 2 : 1); i < aLength-1; ++i)
				{
					integer *= 10;
					integer += (((char *)aData)[i] - '0');
				}
				if(isNegative)
					integer = -integer;

				// Set result
				// FIXME check malloc return value
				*aType = BE_INTEGER;
				int *result = malloc(sizeof (int));
				*result = integer;
				return result;
			}
			break;

		// Dictionary, e.g. d3:cow3:moo4:spam4:eggse
		case 'd':
			;
			break;

		// List, e.g. l4:spam4:eggse
		case 'l':
			;
			break;

		// String, e.g. 4:spam
		case '0'...'9':
			{
				// Get string length
				int length = 0;
				for(char *currentChar = (char *)aData; *currentChar != ':'; ++currentChar)
				{
					length *= 10;
					length += (*currentChar - '0');
				}

				// Get string
				// FIXME check malloc return value
				char *string = malloc((length+1)*sizeof (char));
				memcpy(string, aData+2, length);
				string[length] = '\0';

				// Set result
				*aType = BE_STRING;
				return string;
			}
			break;

		// Invalid
		default:
			;
			break;
	}

	// TODO implement
	return NULL;
}
