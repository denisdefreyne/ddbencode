#include <stdint.h>
#include <stdlib.h>

#include <ddbencode/string.h>
#include <ddbencode/integer.h>
#include <ddbencode/list.h>
#include <ddbencode/dictionary.h>

enum {
	BE_STRING     = 1,
	BE_INTEGER    = 2,
	BE_LIST       = 3,
	BE_DICTIONARY = 4
};
typedef uint8_t BEType;

void *BEDecode(void *aData, size_t aLength, BEType *aType);
