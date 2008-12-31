typedef struct _BEDictionary BEDictionary;

BEDictionary *BEDictionaryCreate(void *args, ...);
void BEDictionaryDelete(BEDictionary *aDictionary);

void BEDictionaryEncode(BEDictionary *aDictionary, void **aData, size_t *aDataLength);
