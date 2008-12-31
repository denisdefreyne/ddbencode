typedef struct _BEList BEList;

BEList *BEListCreate(size_t aSize, ...);
void BEListDelete(BEList *aList);

void BEListEncode(BEList *aList, void **aData, size_t *aDataLength);
