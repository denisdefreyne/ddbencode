#include <stdbool.h>
#include <stdlib.h>

bool BEStringEncode(void *aiString, size_t aiStringLength, void **aoData, size_t *aoDataLength);
size_t BEStringGetEncodedLength(void *aString);
