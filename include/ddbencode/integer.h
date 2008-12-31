#include <stdbool.h>
#include <stdlib.h>

bool BEIntegerEncode(int aiInteger, void **aoData, size_t *aoDataLength);
size_t BEIntegerGetEncodedLength(int aInteger);
