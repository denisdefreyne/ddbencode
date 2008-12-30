#include <bencode/bencode.h>
#include <uctest/uctest.h>

static void BETestDictionary_0(void)
{
	UC_ASSERT(true);
}

void BETestDictionary(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("dictionary");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("test 0", &BETestDictionary_0));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
