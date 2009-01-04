struct _BEListEntry
{
	BEType type;
	union
	{
		char        *string;
		int         integer;
		BEList      *list;
		BEDictionary *dictionary;
	} data;
	size_t stringLength;
};

struct _BEList
{
	struct _BEListEntry *entries;
	size_t size;
};

struct _BEDictionaryEntry
{
	char *key;
	BEType type;
	union
	{
		char        *string;
		int         integer;
		BEList      *list;
		BEDictionary *dictionary;
	} data;
	size_t stringLength;
};

struct _BEDictionary
{
	struct _BEDictionaryEntry *entries;
	size_t size;
};

void _BEStringPrint(char *aString, size_t aIndentation);
void _BEIntegerPrint(int aInteger, size_t aIndentation);
void _BEListPrint(BEList *aList, size_t aIndentation);
void _BEDictionaryPrint(BEDictionary *aDictionary, size_t aIndentation);
