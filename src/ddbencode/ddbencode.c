#include <ddbencode/ddbencode.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
