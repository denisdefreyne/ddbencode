#include <string.h>

#include <ddbencode/ddbencode.h>
#include <uctest/uctest.h>

static void BETestString_encode0(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("", 0, &data, &length);

	UC_ASSERT(2 == length);
	UC_ASSERT(0 == strcmp(data, "0:"));

	free(data);
}

static void BETestString_encode1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("t", 1, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "1:t"));

	free(data);
}

static void BETestString_encode4(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("test", 4, &data, &length);

	UC_ASSERT(6 == length);
	UC_ASSERT(0 == strcmp(data, "4:test"));

	free(data);
}

static void BETestString_encode9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("abcdefghi", 9, &data, &length);

	UC_ASSERT(11 == length);
	UC_ASSERT(0 == strcmp(data, "9:abcdefghi"));

	free(data);
}

static void BETestString_encode10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("abcdefghij", 10, &data, &length);

	UC_ASSERT(13 == length);
	UC_ASSERT(0 == strcmp(data, "10:abcdefghij"));

	free(data);
}

static void BETestString_encode11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEStringEncode("abcdefghijk", 11, &data, &length);

	UC_ASSERT(14 == length);
	UC_ASSERT(0 == strcmp(data, "11:abcdefghijk"));

	free(data);
}

static void BETestString_decode0(void)
{
	BEType type;
	void *result;

	result = BEDecode("0:", 2, &type);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(result, ""));

	free(result);
}

static void BETestString_decode1(void)
{
	BEType type;
	void *result;

	result = BEDecode("1:a", 3, &type);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(result, "a"));

	free(result);
}

static void BETestString_decode4(void)
{
	BEType type;
	void *result;

	result = BEDecode("4:abcd", 6, &type);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(result, "abcd"));

	free(result);
}

static void BETestString_decode9(void)
{
	BEType type;
	void *result;

	result = BEDecode("9:abcdefghi", 11, &type);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(result, "abcdefghi"));

	free(result);
}

static void BETestString_decode10(void)
{
	BEType type;
	void *result;

	result = BEDecode("10:abcdefghij", 13, &type);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(result, "abcdefghij"));

	free(result);
}

static void BETestString_decode11(void)
{
	BEType type;
	void *result;

	result = BEDecode("11:abcdefghijk", 14, &type);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(result, "abcdefghijk"));

	free(result);
}

static void BETestString_getEncodedLength0(void)
{
	UC_ASSERT(2 == BEStringGetEncodedLength(""));
}

static void BETestString_getEncodedLength1(void)
{
	UC_ASSERT(3 == BEStringGetEncodedLength("a"));
}

static void BETestString_getEncodedLength9(void)
{
	UC_ASSERT(11 == BEStringGetEncodedLength("abcdefghi"));
}

static void BETestString_getEncodedLength10(void)
{
	UC_ASSERT(13 == BEStringGetEncodedLength("abcdefghij"));
}

static void BETestString_getEncodedLength11(void)
{
	UC_ASSERT(14 == BEStringGetEncodedLength("abcdefghijk"));
}

void BETestString(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("string");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("encode 0",              &BETestString_encode0));
	uc_suite_add_test(test_suite, uc_test_create("encode 1",              &BETestString_encode1));
	uc_suite_add_test(test_suite, uc_test_create("encode 4",              &BETestString_encode4));
	uc_suite_add_test(test_suite, uc_test_create("encode 9",              &BETestString_encode9));
	uc_suite_add_test(test_suite, uc_test_create("encode 10",             &BETestString_encode10));
	uc_suite_add_test(test_suite, uc_test_create("encode 11",             &BETestString_encode11));
	uc_suite_add_test(test_suite, uc_test_create("decode 0",              &BETestString_decode0));
	uc_suite_add_test(test_suite, uc_test_create("decode 1",              &BETestString_decode1));
	uc_suite_add_test(test_suite, uc_test_create("decode 4",              &BETestString_decode4));
	uc_suite_add_test(test_suite, uc_test_create("decode 9",              &BETestString_decode9));
	uc_suite_add_test(test_suite, uc_test_create("decode 10",             &BETestString_decode10));
	uc_suite_add_test(test_suite, uc_test_create("decode 11",             &BETestString_decode11));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 0",  &BETestString_getEncodedLength0));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 1",  &BETestString_getEncodedLength1));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 9",  &BETestString_getEncodedLength9));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 10", &BETestString_getEncodedLength10));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 11", &BETestString_getEncodedLength11));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
