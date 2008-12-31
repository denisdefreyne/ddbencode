#include <stdint.h>
#include <stdlib.h>

#include <ddbencode/string.h>
#include <ddbencode/integer.h>
#include <ddbencode/list.h>
#include <ddbencode/dictionary.h>

enum {
	BE_STRING,
	BE_INTEGER,
	BE_LIST,
	BE_DICTIONARY,
	BE_END
};
typedef uint8_t BEType;

void *BEDecode(void *aData, size_t aLength, BEType *aType);
