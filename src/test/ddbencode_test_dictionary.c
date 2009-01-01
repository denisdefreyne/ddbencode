#include <string.h>

#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>
#include <uctest/uctest.h>

static void BETestDictionary_create0(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(0);

	UC_ASSERT(0 == dictionary->size);

	BEDictionaryDelete(dictionary);
}

static void BETestDictionary_create1String(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		1,
		"foo", BE_STRING, "bar", 3
	);

	UC_ASSERT(1 == dictionary->size);

	UC_ASSERT(0 == strcmp("foo", dictionary->entries[0].key));
	UC_ASSERT(BE_STRING == dictionary->entries[0].type);
	UC_ASSERT(0 == strcmp("bar", dictionary->entries[0].data.string));
	UC_ASSERT(3 == dictionary->entries[0].stringLength);

	BEDictionaryDelete(dictionary);
}

static void BETestDictionary_create1Integer(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		1,
		"foo", BE_INTEGER, 123
	);

	UC_ASSERT(1 == dictionary->size);

	UC_ASSERT(0 == strcmp("foo", dictionary->entries[0].key));
	UC_ASSERT(BE_INTEGER == dictionary->entries[0].type);
	UC_ASSERT(123 == dictionary->entries[0].data.integer);

	BEDictionaryDelete(dictionary);
}

static void BETestDictionary_create4(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		4,
		"string key",     BE_STRING,     "foo",       3,
		"integer key",    BE_INTEGER,    111,
		"list key",       BE_LIST,       (void *)222,
		"dictionary key", BE_DICTIONARY, (void *)333
	);

	UC_ASSERT(4 == dictionary->size);

	UC_ASSERT(BE_STRING == dictionary->entries[0].type);
	UC_ASSERT(0 == strcmp(dictionary->entries[0].data.string, "foo"));
	UC_ASSERT(3 == dictionary->entries[0].stringLength);

	UC_ASSERT(BE_INTEGER == dictionary->entries[1].type);
	UC_ASSERT(111 == dictionary->entries[1].data.integer);

	UC_ASSERT(BE_LIST == dictionary->entries[2].type);
	UC_ASSERT((void *)222 == dictionary->entries[2].data.list);

	UC_ASSERT(BE_DICTIONARY == dictionary->entries[3].type);
	UC_ASSERT((void *)333 == dictionary->entries[3].data.dictionary);

	BEDictionaryDelete(dictionary);
}

static void BETestDictionary_createInvalid(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		1,
		"some key", 123, "foo", 3
	);

	UC_ASSERT(!dictionary);
}

static void BETestDictionary_getEncodedLength0(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		0
	); // de

	UC_ASSERT(1+1 == BEDictionaryGetEncodedLength(dictionary));

	BEDictionaryDelete(dictionary);
}

static void BETestDictionary_getEncodedLength1(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		1,
		"key", BE_STRING, "foo", 3
	); // d3:key3:fooe

	UC_ASSERT(1+((1+1+3)+(1+1+3))+1 == BEDictionaryGetEncodedLength(dictionary));

	BEDictionaryDelete(dictionary);
}

static void BETestDictionary_getEncodedLength2(void)
{
	BEDictionary *dictionary = BEDictionaryCreate(
		2,
		"key1", BE_STRING,  "foo", 3,
		"key2", BE_INTEGER, 123
	); // d4:key13:foo4:key2i123ee

	UC_ASSERT(1+((1+1+4)+(1+1+3))+((1+1+4)+(1+3+1))+1 == BEDictionaryGetEncodedLength(dictionary));

	BEDictionaryDelete(dictionary);
}

void BETestDictionary(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("dictionary");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("create 0",             &BETestDictionary_create0));
	uc_suite_add_test(test_suite, uc_test_create("create 1 string",      &BETestDictionary_create1String));
	uc_suite_add_test(test_suite, uc_test_create("create 1 integer",     &BETestDictionary_create1Integer));
	uc_suite_add_test(test_suite, uc_test_create("create 4",             &BETestDictionary_create4));
	uc_suite_add_test(test_suite, uc_test_create("create invalid",       &BETestDictionary_createInvalid));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 0", &BETestDictionary_getEncodedLength0));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 1", &BETestDictionary_getEncodedLength1));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 2", &BETestDictionary_getEncodedLength2));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
