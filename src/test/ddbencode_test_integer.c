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
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i0e", 3, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(0 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(3 == usedLength);
}

static void BETestInteger_decode1(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i1e", 3, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(1 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(3 == usedLength);
}

static void BETestInteger_decode9(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i9e", 3, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(9 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(3 == usedLength);
}

static void BETestInteger_decode10(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i10e", 4, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(10 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(4 == usedLength);
}

static void BETestInteger_decode11(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i11e", 4, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(11 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(4 == usedLength);
}

static void BETestInteger_decodeM1(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i-1e", 4, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(-1 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(4 == usedLength);
}

static void BETestInteger_decodeM9(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i-9e", 4, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(-9 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(4 == usedLength);
}

static void BETestInteger_decodeM10(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i-10e", 5, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(-10 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(5 == usedLength);
}

static void BETestInteger_decodeM11(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i-11e", 5, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(-11 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(5 == usedLength);
}

static void BETestInteger_decodeLong(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i123eblahblah", 13, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_INTEGER == type);
	UC_ASSERT(123 == integer);

	UC_ASSERT(NULL == string);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(5 == usedLength);
}

static void BETestInteger_decodeInvalid0(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("ie", 2, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(false == success);
}

static void BETestInteger_decodeInvalid1(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("ieee", 4, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(false == success);
}

static void BETestInteger_decodeInvalid2(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("i12345e", 3, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(false == success);
}

static void BETestInteger_getEncodedLength0(void)
{
	UC_ASSERT(3 == BEIntegerGetEncodedLength(0));
}

static void BETestInteger_getEncodedLength1(void)
{
	UC_ASSERT(3 == BEIntegerGetEncodedLength(1));
}

static void BETestInteger_getEncodedLength9(void)
{
	UC_ASSERT(3 == BEIntegerGetEncodedLength(9));
}

static void BETestInteger_getEncodedLength10(void)
{
	UC_ASSERT(4 == BEIntegerGetEncodedLength(10));
}

static void BETestInteger_getEncodedLength11(void)
{
	UC_ASSERT(4 == BEIntegerGetEncodedLength(11));
}

static void BETestInteger_getEncodedLengthM1(void)
{
	UC_ASSERT(4 == BEIntegerGetEncodedLength(-1));
}

static void BETestInteger_getEncodedLengthM9(void)
{
	UC_ASSERT(4 == BEIntegerGetEncodedLength(-9));
}

static void BETestInteger_getEncodedLengthM10(void)
{
	UC_ASSERT(5 == BEIntegerGetEncodedLength(-10));
}

static void BETestInteger_getEncodedLengthM11(void)
{
	UC_ASSERT(5 == BEIntegerGetEncodedLength(-11));
}

void BETestInteger(void)
{
	/* create suite */
	uc_suite_t *test_suite = uc_suite_create("integer");

	/* add tests to suite */
	uc_suite_add_test(test_suite, uc_test_create("encode 0",               &BETestInteger_encode0));
	uc_suite_add_test(test_suite, uc_test_create("encode 1",               &BETestInteger_encode1));
	uc_suite_add_test(test_suite, uc_test_create("encode 9",               &BETestInteger_encode9));
	uc_suite_add_test(test_suite, uc_test_create("encode 10",              &BETestInteger_encode10));
	uc_suite_add_test(test_suite, uc_test_create("encode 11",              &BETestInteger_encode11));
	uc_suite_add_test(test_suite, uc_test_create("encode -1",              &BETestInteger_encodeM1));
	uc_suite_add_test(test_suite, uc_test_create("encode -9",              &BETestInteger_encodeM9));
	uc_suite_add_test(test_suite, uc_test_create("encode -10",             &BETestInteger_encodeM10));
	uc_suite_add_test(test_suite, uc_test_create("encode -11",             &BETestInteger_encodeM11));
	uc_suite_add_test(test_suite, uc_test_create("decode 0",               &BETestInteger_decode0));
	uc_suite_add_test(test_suite, uc_test_create("decode 1",               &BETestInteger_decode1));
	uc_suite_add_test(test_suite, uc_test_create("decode 9",               &BETestInteger_decode9));
	uc_suite_add_test(test_suite, uc_test_create("decode 10",              &BETestInteger_decode10));
	uc_suite_add_test(test_suite, uc_test_create("decode 11",              &BETestInteger_decode11));
	uc_suite_add_test(test_suite, uc_test_create("decode -1",              &BETestInteger_decodeM1));
	uc_suite_add_test(test_suite, uc_test_create("decode -9",              &BETestInteger_decodeM9));
	uc_suite_add_test(test_suite, uc_test_create("decode -10",             &BETestInteger_decodeM10));
	uc_suite_add_test(test_suite, uc_test_create("decode -11",             &BETestInteger_decodeM11));
	uc_suite_add_test(test_suite, uc_test_create("decode long",            &BETestInteger_decodeLong));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 0",       &BETestInteger_decodeInvalid0));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 1",       &BETestInteger_decodeInvalid1));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 2",       &BETestInteger_decodeInvalid2));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 0",   &BETestInteger_getEncodedLength0));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 1",   &BETestInteger_getEncodedLength1));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 9",   &BETestInteger_getEncodedLength9));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 10",  &BETestInteger_getEncodedLength10));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length 11",  &BETestInteger_getEncodedLength11));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length -1",  &BETestInteger_getEncodedLengthM1));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length -9",  &BETestInteger_getEncodedLengthM9));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length -10", &BETestInteger_getEncodedLengthM10));
	uc_suite_add_test(test_suite, uc_test_create("get encoded length -11", &BETestInteger_getEncodedLengthM11));

	/* run suite */
	uc_suite_run(test_suite);

	/* destroy suite */
	uc_suite_destroy(test_suite);
}
