#include <string.h>

#include <ddbencode/ddbencode.h>
#include <uctest/uctest.h>

static void BETestInteger_encode0(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(0, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "i0e"));

	free(data);
}

static void BETestInteger_encode1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(1, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "i1e"));

	free(data);
}

static void BETestInteger_encode9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(9, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "i9e"));

	free(data);
}

static void BETestInteger_encode10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(10, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i10e"));

	free(data);
}

static void BETestInteger_encode11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(11, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i11e"));

	free(data);
}

static void BETestInteger_encodeM1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-1, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i-1e"));

	free(data);
}

static void BETestInteger_encodeM9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-9, &data, &length);

	UC_ASSERT(4 == length);
	UC_ASSERT(0 == strcmp(data, "i-9e"));

	free(data);
}

static void BETestInteger_encodeM10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-10, &data, &length);

	UC_ASSERT(5 == length);
	UC_ASSERT(0 == strcmp(data, "i-10e"));

	free(data);
}

static void BETestInteger_encodeM11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEIntegerEncode(-11, &data, &length);

	UC_ASSERT(5 == length);
	UC_ASSERT(0 == strcmp(data, "i-11e"));

	free(data);
}

static void BETestInteger_decode0(void)
{
	BEType type;
	void *result;

	result = BEDecode("i0e", 3, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == 0);

	free(result);
}

static void BETestInteger_decode1(void)
{
	BEType type;
	void *result;

	result = BEDecode("i1e", 3, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == 1);

	free(result);
}

static void BETestInteger_decode9(void)
{
	BEType type;
	void *result;

	result = BEDecode("i9e", 3, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == 9);

	free(result);
}

static void BETestInteger_decode10(void)
{
	BEType type;
	void *result;

	result = BEDecode("i10e", 4, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == 10);

	free(result);
}

static void BETestInteger_decode11(void)
{
	BEType type;
	void *result;

	result = BEDecode("i11e", 4, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == 11);

	free(result);
}

static void BETestInteger_decodeM1(void)
{
	BEType type;
	void *result;

	result = BEDecode("i-1e", 4, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == -1);

	free(result);
}

static void BETestInteger_decodeM9(void)
{
	BEType type;
	void *result;

	result = BEDecode("i-9e", 4, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == -9);

	free(result);
}

static void BETestInteger_decodeM10(void)
{
	BEType type;
	void *result;

	result = BEDecode("i-10e", 5, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == -10);

	free(result);
}

static void BETestInteger_decodeM11(void)
{
	BEType type;
	void *result;

	result = BEDecode("i-11e", 5, &type);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(*((int *)result) == -11);

	free(result);
}

void BETestInteger(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("integer");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("encode 0",   &BETestInteger_encode0));
	uc_suite_add_test(test_suite, uc_test_create("encode 1",   &BETestInteger_encode1));
	uc_suite_add_test(test_suite, uc_test_create("encode 9",   &BETestInteger_encode9));
	uc_suite_add_test(test_suite, uc_test_create("encode 10",  &BETestInteger_encode10));
	uc_suite_add_test(test_suite, uc_test_create("encode 11",  &BETestInteger_encode11));
	uc_suite_add_test(test_suite, uc_test_create("encode -1",  &BETestInteger_encodeM1));
	uc_suite_add_test(test_suite, uc_test_create("encode -9",  &BETestInteger_encodeM9));
	uc_suite_add_test(test_suite, uc_test_create("encode -10", &BETestInteger_encodeM10));
	uc_suite_add_test(test_suite, uc_test_create("encode -11", &BETestInteger_encodeM11));
	uc_suite_add_test(test_suite, uc_test_create("decode 0",   &BETestInteger_decode0));
	uc_suite_add_test(test_suite, uc_test_create("decode 1",   &BETestInteger_decode1));
	uc_suite_add_test(test_suite, uc_test_create("decode 9",   &BETestInteger_decode9));
	uc_suite_add_test(test_suite, uc_test_create("decode 10",  &BETestInteger_decode10));
	uc_suite_add_test(test_suite, uc_test_create("decode 11",  &BETestInteger_decode11));
	uc_suite_add_test(test_suite, uc_test_create("decode -1",  &BETestInteger_decodeM1));
	uc_suite_add_test(test_suite, uc_test_create("decode -9",  &BETestInteger_decodeM9));
	uc_suite_add_test(test_suite, uc_test_create("decode -10", &BETestInteger_decodeM10));
	uc_suite_add_test(test_suite, uc_test_create("decode -11", &BETestInteger_decodeM11));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}