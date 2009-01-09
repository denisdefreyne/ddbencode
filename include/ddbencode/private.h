struct _BEString
{
	char *cString;
	size_t length;
};

struct _BEListEntry
{
	BEType type;
	union
	{
		BEString    *string;
		int         integer;
		BEList      *list;
		BEDictionary *dictionary;
	} data;
};

struct _BEList
{
	struct _BEListEntry *entries;
	size_t size;
};

struct _BEDictionaryEntry
{
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

struct _BEDictionary
{
	struct _BEDictionaryEntry *entries;
	size_t size;
};

void _BEStringPrint(BEString *aString, size_t aIndentation);
void _BEIntegerPrint(int aInteger, size_t aIndentation);
void _BEListPrint(BEList *aList, size_t aIndentation);
void _BEDictionaryPrint(BEDictionary *aDictionary, size_t aIndentation);
