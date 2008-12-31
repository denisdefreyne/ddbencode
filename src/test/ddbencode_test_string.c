#include <string.h>

#include <ddbencode/ddbencode.h>
#include <uctest/uctest.h>

static void BETestString_decodeWithLengthEqualTo0(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("", 0, &data, &length);

	UC_ASSERT(2 == length);
	UC_ASSERT(0 == strcmp(data, "0:"));

	free(data);
}

static void BETestString_decodeWithLengthEqualTo1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("t", 1, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "1:t"));

	free(data);
}

static void BETestString_decodeWithSmallLength(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("test", 4, &data, &length);

	UC_ASSERT(6 == length);
	UC_ASSERT(0 == strcmp(data, "4:test"));

	free(data);
}

static void BETestString_decodeWithLengthEqualTo9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("abcdefghi", 9, &data, &length);

	UC_ASSERT(11 == length);
	UC_ASSERT(0 == strcmp(data, "9:abcdefghi"));

	free(data);
}

static void BETestString_decodeWithLengthEqualTo10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("abcdefghij", 10, &data, &length);

	UC_ASSERT(13 == length);
	UC_ASSERT(0 == strcmp(data, "10:abcdefghij"));

	free(data);
}

static void BETestString_decodeWithLengthEqualTo11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("abcdefghijk", 11, &data, &length);

	UC_ASSERT(14 == length);
	UC_ASSERT(0 == strcmp(data, "11:abcdefghijk"));

	free(data);
}

void BETestString(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("string");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("length == 0",        &BETestString_decodeWithLengthEqualTo0));
	uc_suite_add_test(test_suite, uc_test_create("length == 1",        &BETestString_decodeWithLengthEqualTo1));
	uc_suite_add_test(test_suite, uc_test_create("length > 1 and < 9", &BETestString_decodeWithSmallLength));
	uc_suite_add_test(test_suite, uc_test_create("length == 9",        &BETestString_decodeWithLengthEqualTo9));
	uc_suite_add_test(test_suite, uc_test_create("length == 10",       &BETestString_decodeWithLengthEqualTo10));
	uc_suite_add_test(test_suite, uc_test_create("length == 11",       &BETestString_decodeWithLengthEqualTo11));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}