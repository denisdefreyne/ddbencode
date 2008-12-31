#include <stdbool.h>
#include <stdlib.h>

typedef struct _BEList BEList;

BEList *BEListCreate(size_t aSize, ...);
void BEListDelete(BEList *aList);

bool BEListEncode(BEList *aiList, void **aoData, size_t *aoDataLength);
size_t BEListGetEncodedLength(BEList *aList);
