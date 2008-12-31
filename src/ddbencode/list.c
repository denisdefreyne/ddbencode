#include <ddbencode/ddbencode.h>

#include <stdarg.h>
#include <stdio.h>

BEList *BEListCreate(size_t aSize, ...)
{
	va_list ap;

	// Create (empty) list
	;

	va_start(ap, aSize);
	for(size_t i = 0; i < aSize; ++i)
	{
		// Temporary iterator variables
		char         *string;
		int          integer;
		BEList       *list;
		BEDictionary *dictionary;

		// Get type
		int type = va_arg(ap, int);

		switch(type)
		{
			case BE_STRING:
				string = va_arg(ap, char *);
				printf("it's a string! %s\n", string);
				break;

			case BE_INTEGER:
				integer = va_arg(ap, int);
				printf("it's an integer! %i\n", integer);
				break;

			case BE_LIST:
				list = va_arg(ap, BEList *);
				printf("it's a list!\n");
				break;

			case BE_DICTIONARY:
				dictionary = va_arg(ap, BEDictionary *);
				printf("it's a dictionary!\n");
				break;

			default:
				printf("not sure what it is :/\n");
		}
	}
	va_end(ap);



	// TODO implement
	return NULL;
}

void BEListDelete(BEList *aList)
{
	// TODO implement
	;
}

void BEListEncode(BEList *aList, void **aData, size_t *aDataLength)
{
	// Lists are encoded as an 'l' followed by their elements (also bencoded)
	// followed by an 'e'. For example l4:spam4:eggse corresponds to ['spam',
	// 'eggs'].

	// TODO implement
}

