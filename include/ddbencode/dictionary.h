typedef struct _BEDictionary BEDictionary;

BEDictionary *BEDictionaryCreate(void *args, ...);
void BEDictionaryDelete(BEDictionary *aDictionary);

void BEDictionaryEncode(BEDictionary *aiDictionary, void **aoData, size_t *aoDataLength);
size_t BEDictionaryGetEncodedLength(BEDictionary *aDictionary);
