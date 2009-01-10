#include <cobject/cobject.h>

// String
struct _BEString
{
	COGuts *guts;

	char *cString;
	size_t length;
};

// List entry
struct _BEListEntry
{
	COGuts *guts;

	BEType type;
	union
	{
		BEString    *string;
		int         integer;
		BEList      *list;
		BEDictionary *dictionary;
	} data;
};

// List
struct _BEList
{
	COGuts *guts;

	struct _BEListEntry *entries;
	size_t size;
};

// Dictionary entry
struct _BEDictionaryEntry
{
	COGuts *guts;

	BEString *key;
	BEType type;
	union
	{
		BEString    *string;
		int         integer;
		BEList      *list;
		BEDictionary *dictionary;
	} data;
};

// Dictionary
struct _BEDictionary
{
	COGuts *guts;

	struct _BEDictionaryEntry *entries;
	size_t size;
};

// Printing
void _BEStringPrint(BEString *aString, size_t aIndentation);
void _BEIntegerPrint(int aInteger, size_t aIndentation);
void _BEListPrint(BEList *aList, size_t aIndentation);
void _BEDictionaryPrint(BEDictionary *aDictionary, size_t aIndentation);

// Deleting
void _BEStringDelete(void *aString);
void _BEListDelete(void *aList);
void _BEDictionaryDelete(void *aDictionary);
