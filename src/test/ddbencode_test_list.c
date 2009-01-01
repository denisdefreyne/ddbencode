#include <string.h>

#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>
#include <uctest/uctest.h>

static void BETestList_create0(void)
{
	BEList *list = BEListCreate(0);

	UC_ASSERT(0 == list->size);

	BEListDelete(list);
}

static void BETestList_create1Integer(void)
{
	BEList *list = BEListCreate(
		1,
		BE_INTEGER, 123
	);

	UC_ASSERT(1 == list->size);

	UC_ASSERT(BE_INTEGER == list->entries[0].type);
	UC_ASSERT(123 == list->entries[0].data.integer);

	BEListDelete(list);
}

static void BETestList_create1String(void)
{
	BEList *list = BEListCreate(
		1,
		BE_STRING, "foo", 3
	);

	UC_ASSERT(1 == list->size);

	UC_ASSERT(BE_STRING == list->entries[0].type);
	UC_ASSERT(0 == strcmp(list->entries[0].data.string, "foo"));
	UC_ASSERT(3 == list->entries[0].stringLength);

	BEListDelete(list);
}

static void BETestList_create4(void)
{
	BEList *list = BEListCreate(
		4,
		BE_STRING,     "foo",       3,
		BE_INTEGER,    111,
		BE_LIST,       (void *)222,
		BE_DICTIONARY, (void *)333
	);

	UC_ASSERT(4 == list->size);

	UC_ASSERT(BE_STRING == list->entries[0].type);
	UC_ASSERT(0 == strcmp(list->entries[0].data.string, "foo"));
	UC_ASSERT(3 == list->entries[0].stringLength);

	UC_ASSERT(BE_INTEGER == list->entries[1].type);
	UC_ASSERT(111 == list->entries[1].data.integer);

	UC_ASSERT(BE_LIST == list->entries[2].type);
	UC_ASSERT((void *)222 == list->entries[2].data.list);

	UC_ASSERT(BE_DICTIONARY == list->entries[3].type);
	UC_ASSERT((void *)333 == list->entries[3].data.dictionary);

	BEListDelete(list);
}

static void BETestList_createInvalid(void)
{
	BEList *list = BEListCreate(
		1,
		123, "foo", 3
	);

	UC_ASSERT(!list);
}

static void BETestList_encode0(void)
{
	BEList *list = BEListCreate(
		0
	); // le

	void *data;
	size_t dataLength;

	BEListEncode(list, &data, &dataLength);

	UC_ASSERT(data);
	UC_ASSERT(1+1 == dataLength);
	UC_ASSERT(0 == strncmp(data, "le", 1+1));

	free(data);
	BEListDelete(list);
}

static void BETestList_encode1(void)
{
	BEList *list = BEListCreate(
		1,
		BE_STRING, "foo", 3
	); // l3:fooe

	void *data;
	size_t dataLength;

	BEListEncode(list, &data, &dataLength);

	UC_ASSERT(data);
	UC_ASSERT(1+(1+1+3)+1 == dataLength);
	UC_ASSERT(0 == strncmp(data, "l3:fooe", 1+(1+1+3)+1));

	free(data);
	BEListDelete(list);
}

static void BETestList_encode2(void)
{
	BEList *list = BEListCreate(
		2,
		BE_STRING,  "foo", 3,
		BE_INTEGER, 123
	); // l3:fooi123ee

	void *data;
	size_t dataLength;

	BEListEncode(list, &data, &dataLength);

	UC_ASSERT(data);
	UC_ASSERT(1+(1+1+3)+(1+3+1)+1 == dataLength);
	UC_ASSERT(0 == strncmp(data, "l3:fooi123ee", 1+(1+1+3)+(1+3+1)+1));

	free(data);
	BEListDelete(list);
}

static void BETestList_decode0(void)
{
	BEType type;
	bool success;

	char *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t stringLength = 0;
	size_t usedLength = 0;

	success = BEDecode("le", 2, &type, &string, &integer, &list, &dictionary, &stringLength, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_LIST == type);
	UC_ASSERT(list);
	UC_ASSERT(0 == list->size);

	UC_ASSERT(NULL == string);
	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(0 == stringLength);
	UC_ASSERT(2 == usedLength);
}

static void BETestList_decode1(void)
{
	BEType type;
	bool success;

	char *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t stringLength = 0;
	size_t usedLength = 0;

	success = BEDecode("li123ee", 7, &type, &string, &integer, &list, &dictionary, &stringLength, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_LIST == type);
	UC_ASSERT(list);
	UC_ASSERT(1 == list->size);
	UC_ASSERT(BE_INTEGER == list->entries[0].type);
	UC_ASSERT(123 == list->entries[0].data.integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(0 == stringLength);
	UC_ASSERT(7 == usedLength);
}

static void BETestList_decode2(void)
{
	BEType type;
	bool success;

	char *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t stringLength = 0;
	size_t usedLength = 0;

	success = BEDecode("li123ei456ee", 12, &type, &string, &integer, &list, &dictionary, &stringLength, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_LIST == type);
	UC_ASSERT(list);
	UC_ASSERT(2 == list->size);
	UC_ASSERT(BE_INTEGER == list->entries[0].type);
	UC_ASSERT(123 == list->entries[0].data.integer);
	UC_ASSERT(BE_INTEGER == list->entries[1].type);
	UC_ASSERT(456 == list->entries[1].data.integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(0 == stringLength);
	UC_ASSERT(12 == usedLength);
}

static void BETestList_decodeComplex(void)
{
	BEType type;
	bool success;

	char *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t stringLength = 0;
	size_t usedLength = 0;

	success = BEDecode("llli123eeee", 11, &type, &string, &integer, &list, &dictionary, &stringLength, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_LIST == type);
	UC_ASSERT(list);
	UC_ASSERT(1 == list->size);

	UC_ASSERT(BE_LIST == list->entries[0].type);
	UC_ASSERT(list->entries[0].data.list);
	UC_ASSERT(1 == list->entries[0].data.list->size);

	UC_ASSERT(BE_LIST == list->entries[0].data.list->entries[0].type);
	UC_ASSERT(list->entries[0].data.list->entries[0].data.list);
	UC_ASSERT(1 == list->entries[0].data.list->entries[0].data.list->size);

	UC_ASSERT(NULL == string);
	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(0 == stringLength);
	UC_ASSERT(11 == usedLength);
}

static void BETestList_decodeInvalid(void)
{
	BEType type;
	bool success;

	char *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t stringLength = 0;
	size_t usedLength = 0;

	success = BEDecode("li123ei456e", 11, &type, &string, &integer, &list, &dictionary, &stringLength, &usedLength);

	UC_ASSERT(!success);
}

static void BETestList_getEncodedLength0(void)
{
	BEList *list = BEListCreate(
		0
	); // le

	UC_ASSERT(1+1 == BEListGetEncodedLength(list));

	BEListDelete(list);
}

static void BETestList_getEncodedLength1(void)
{
	BEList *list = BEListCreate(
		1,
		BE_STRING, "foo", 3
	); // l3:fooe

	UC_ASSERT(1+(1+1+3)+1 == BEListGetEncodedLength(list));

	BEListDelete(list);
}

static void BETestList_getEncodedLength2(void)
{
	BEList *list = BEListCreate(
		2,
		BE_STRING,  "foo", 3,
		BE_INTEGER, 123
	); // l3:fooi123ee

	UC_ASSERT(1+(1+1+3)+(1+3+1)+1 == BEListGetEncodedLength(list));

	BEListDelete(list);
}

void BETestList(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("list");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("create 0",             &BETestList_create0));
	uc_suite_add_test(test_suite, uc_test_create("create 1 string",      &BETestList_create1String));
	uc_suite_add_test(test_suite, uc_test_create("create 1 integer",     &BETestList_create1Integer));
	uc_suite_add_test(test_suite, uc_test_create("create 4",             &BETestList_create4));
	uc_suite_add_test(test_suite, uc_test_create("create invalid",       &BETestList_createInvalid));
	uc_suite_add_test(test_suite, uc_test_create("encode 0",             &BETestList_encode0));
	uc_suite_add_test(test_suite, uc_test_create("encode 1",             &BETestList_encode1));
	uc_suite_add_test(test_suite, uc_test_create("encode 2",             &BETestList_encode2));
	uc_suite_add_test(test_suite, uc_test_create("decode 0",             &BETestList_decode0));
	uc_suite_add_test(test_suite, uc_test_create("decode 1",             &BETestList_decode1));
	uc_suite_add_test(test_suite, uc_test_create("decode 2",             &BETestList_decode2));
	uc_suite_add_test(test_suite, uc_test_create("decode complex",       &BETestList_decodeComplex));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid",       &BETestList_decodeInvalid));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 0", &BETestList_getEncodedLength0));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 1", &BETestList_getEncodedLength1));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 2", &BETestList_getEncodedLength2));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
