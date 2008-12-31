#include <string.h>

#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>
#include <uctest/uctest.h>

static void BETestList_create0(void)
{
	BEList *list = BEListCreate(0);

	UC_ASSERT(0 == list->size);
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
}

static void BETestList_createInvalid(void)
{
	BEList *list = BEListCreate(
		1,
		123, "foo", 3
	);

	UC_ASSERT(!list);
}

void BETestList(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("list");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("create 0",         &BETestList_create0));
	uc_suite_add_test(test_suite, uc_test_create("create 1 string",  &BETestList_create1String));
	uc_suite_add_test(test_suite, uc_test_create("create 1 integer", &BETestList_create1Integer));
	uc_suite_add_test(test_suite, uc_test_create("create 4",         &BETestList_create4));
	uc_suite_add_test(test_suite, uc_test_create("create invalid",   &BETestList_createInvalid));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
