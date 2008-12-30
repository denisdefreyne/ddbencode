#include <string.h>

#include <bencode/bencode.h>
#include <uctest/uctest.h>

static void BETestInteger_0(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(0, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "i0e"));

	free(data);
}

static void BETestInteger_1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(1, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "i1e"));

	free(data);
}

static void BETestInteger_9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(9, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "i9e"));

	free(data);
}

static void BETestInteger_10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(10, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i10e"));

	free(data);
}

static void BETestInteger_11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(11, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i11e"));

	free(data);
}

static void BETestInteger_m1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-1, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i-1e"));

	free(data);
}

static void BETestInteger_m9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-9, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i-9e"));

	free(data);
}

static void BETestInteger_m10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-10, &data, &length);

	UC_ASSERT(5 == length);
	UC_ASSERT(0 == strcmp(data, "i-10e"));

	free(data);
}

static void BETestInteger_m11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-11, &data, &length);

	UC_ASSERT(5 == length);
	UC_ASSERT(0 == strcmp(data, "i-11e"));

	free(data);
}

void BETestInteger(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("integer");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("0",   &BETestInteger_0));
	uc_suite_add_test(test_suite, uc_test_create("1",   &BETestInteger_1));
	uc_suite_add_test(test_suite, uc_test_create("9",   &BETestInteger_9));
	uc_suite_add_test(test_suite, uc_test_create("10",  &BETestInteger_10));
	uc_suite_add_test(test_suite, uc_test_create("11",  &BETestInteger_11));
	uc_suite_add_test(test_suite, uc_test_create("-1",  &BETestInteger_m1));
	uc_suite_add_test(test_suite, uc_test_create("-9",  &BETestInteger_m9));
	uc_suite_add_test(test_suite, uc_test_create("-10", &BETestInteger_m10));
	uc_suite_add_test(test_suite, uc_test_create("-11", &BETestInteger_m11));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
