#include <ddbencode/ddbencode.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool BEDecode(void *aiData, size_t aiLength, BEType *aoType, char **aoString, int *aoInteger, BEList **aoList, BEDictionary **aoDictionary, size_t *aoStringLength)
{
	// Validate length
	if(aiLength < 2)
		return false;

	switch(((char *)aiData)[0])
	{
		// Integer, e.g. i3e
		case 'i':
			{
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
				return true;
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
				size_t i;
				for(i = 0; ((char *)aiData)[i] != ':'; ++i)
				{
					length *= 10;
					length += (((char *)aiData)[i] - '0');
				}

				// Get string
				char *string = malloc((length+1)*sizeof (char));
				if(!string)
					return false;
				memcpy(string, aiData+i+1, length);
				string[length] = '\0';

				// Set result
				*aoType = BE_STRING;
				*aoString = string;
				*aoStringLength = length;
				return true;
			}
			break;

		// Invalid
		default:
			;
			break;
	}

	return false;
}
