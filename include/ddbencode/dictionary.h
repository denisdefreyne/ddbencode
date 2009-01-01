#include <stdbool.h>
#include <stdlib.h>

typedef struct _BEDictionary BEDictionary;

BEDictionary *BEDictionaryCreate(size_t aSize, ...);
void BEDictionaryDelete(BEDictionary *aDictionary);
void BEDictionaryDeleteDeep(BEDictionary *aDictionary);

bool BEDictionaryEncode(BEDictionary *aiDictionary, void **aoData, size_t *aoDataLength);
size_t BEDictionaryGetEncodedLength(BEDictionary *aDictionary);
