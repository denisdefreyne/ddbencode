#include <stdbool.h>
#include <stdlib.h>

typedef struct _BEDictionary BEDictionary;

BEDictionary *BEDictionaryCreate(void *args, ...);
void BEDictionaryDelete(BEDictionary *aDictionary);

bool BEDictionaryEncode(BEDictionary *aiDictionary, void **aoData, size_t *aoDataLength);
size_t BEDictionaryGetEncodedLength(BEDictionary *aDictionary);
