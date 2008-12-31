#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>
#include <uctest/uctest.h>

static void BETestList_create0(void)
{
	BEList *list = BEListCreate(0);

	UC_ASSERT(0 == list->size);
}

static void BETestList_create1(void)
{
	BEList *list = BEListCreate(
		1,
		BE_STRING, "foo"
	);

	UC_ASSERT(1 == list->size);
}

static void BETestList_create8(void)
{
	BEList *list = BEListCreate(
		8,
		BE_STRING, "foo",
		BE_INTEGER, 800,
		BE_STRING, "foo",
		BE_INTEGER, 800,
		BE_INTEGER, 800,
		BE_LIST, NULL,
		BE_DICTIONARY, 2,
		BE_LIST, 123
	);

	UC_ASSERT(8 == list->size);
}

static void BETestList_createInvalid(void)
{
	BEList *list = BEListCreate(
		1,
		123, "foo"
	);

	UC_ASSERT(!list);
}

void BETestList(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("list");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("create 0",       &BETestList_create0));
	uc_suite_add_test(test_suite, uc_test_create("create 1",       &BETestList_create1));
	uc_suite_add_test(test_suite, uc_test_create("create 8",       &BETestList_create8));
	uc_suite_add_test(test_suite, uc_test_create("create invalid", &BETestList_createInvalid));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
