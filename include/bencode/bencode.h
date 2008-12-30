#include <stdint.h>
#include <stdlib.h>

/* ---------- TYPES ---------- */

enum {
	BE_STRING,
	BE_INTEGER,
	BE_LIST,
	BE_DICTIONARY
};
typedef uint8_t BEType;

typedef struct _BEList BEList;
typedef struct _BEDictionary BEDictionary;

/* ---------- LIST CREATION/DELETION ---------- */

BEList *BEListCreate(void *args, ...);
void BEListDelete(BEList *aList);

/* ---------- DICTIONARY CREATION/DELETION ---------- */

BEDictionary *BEDictionaryCreate(void *args, ...);
void BEDictionaryDelete(BEDictionary *aDictionary);

/* ---------- ENCODING ---------- */

void BEStringEncode(void *aString, size_t aStringLength, void **aData, size_t *aDataLength);
void BEIntegerEncode(int aInteger, void **aData, size_t *aDataLength);
void BEListEncode(BEList *aList, void **aData, size_t *aDataLength);
void BEDictionaryEncode(BEDictionary *aDictionary, void **aData, size_t *aDataLength);

/* ---------- DECODING ---------- */

void *BEDecode(void *aData, size_t aLength, BEType *aType);
