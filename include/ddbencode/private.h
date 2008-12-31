struct _BEListEntry
{
	BEType type;
	void *data;
};

struct _BEList
{
	struct _BEListEntry *entries;
	size_t length;
};

struct _BEDictionaryEntry
{
	char *key;
	BEType valueType;
	void *value;
};

struct _BEDictionary
{
	struct _BEDictionaryEntry *entries;
	size_t length;
};
