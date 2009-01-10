#include <string.h>

#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>
#include <uctest/uctest.h>

// TODO add string creation tests

static void BETestString_encode0(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEString *string = BEStringCreate("", 0);
	BEStringEncode(string, &data, &length);

	UC_ASSERT(2 == length);
	UC_ASSERT(0 == strcmp(data, "0:"));

	free(data);
	CORelease(string);
}

static void BETestString_encode1(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEString *string = BEStringCreate("t", 1);
	BEStringEncode(string, &data, &length);

	UC_ASSERT(3 == length);
	UC_ASSERT(0 == strcmp(data, "1:t"));

	free(data);
	CORelease(string);
}

static void BETestString_encode4(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEString *string = BEStringCreate("test", 4);
	BEStringEncode(string, &data, &length);

	UC_ASSERT(6 == length);
	UC_ASSERT(0 == strcmp(data, "4:test"));

	free(data);
	CORelease(string);
}

static void BETestString_encode9(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEString *string = BEStringCreate("abcdefghi", 9);
	BEStringEncode(string, &data, &length);

	UC_ASSERT(11 == length);
	UC_ASSERT(0 == strcmp(data, "9:abcdefghi"));

	free(data);
	CORelease(string);
}

static void BETestString_encode10(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEString *string = BEStringCreate("abcdefghij", 10);
	BEStringEncode(string, &data, &length);

	UC_ASSERT(13 == length);
	UC_ASSERT(0 == strcmp(data, "10:abcdefghij"));

	free(data);
	CORelease(string);
}

static void BETestString_encode11(void)
{
	void   *data  = NULL;
	size_t length = 0;

	BEString *string = BEStringCreate("abcdefghijk", 11);
	BEStringEncode(string, &data, &length);

	UC_ASSERT(14 == length);
	UC_ASSERT(0 == strcmp(data, "11:abcdefghijk"));

	free(data);
	CORelease(string);
}

static void BETestString_decode0(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("0:", 2, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, ""));
	UC_ASSERT(0 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(2 == usedLength);

	CORelease(string);
}

static void BETestString_decode1(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("1:a", 3, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, "a"));
	UC_ASSERT(1 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(3 == usedLength);

	CORelease(string);
}

static void BETestString_decode4(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("4:abcd", 6, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, "abcd"));
	UC_ASSERT(4 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(6 == usedLength);

	CORelease(string);
}

static void BETestString_decode9(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("9:abcdefghi", 11, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, "abcdefghi"));
	UC_ASSERT(9 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(11 == usedLength);

	CORelease(string);
}

static void BETestString_decode10(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("10:abcdefghij", 13, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, "abcdefghij"));
	UC_ASSERT(10 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(13 == usedLength);

	CORelease(string);
}

#include <cobject/private.h>

static void BETestString_decode11(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("11:abcdefghijk", 14, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, "abcdefghijk"));
	UC_ASSERT(11 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(14 == usedLength);

	CORelease(string);
}

static void BETestString_decodeLong(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("3:abcdefghijklmno", 17, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(success);

	UC_ASSERT(BE_STRING == type);
	UC_ASSERT(0 == strcmp(string->cString, "abc"));
	UC_ASSERT(3 == string->length);

	UC_ASSERT(0 == integer);
	UC_ASSERT(NULL == list);
	UC_ASSERT(NULL == dictionary);
	UC_ASSERT(5 == usedLength);

	CORelease(string);
}

static void BETestString_decodeInvalid0(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("0", 1, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(!success);
}

static void BETestString_decodeInvalid1(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode(":", 1, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(!success);
}

static void BETestString_decodeInvalid2(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("5:asdf", 6, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(!success);
}

static void BETestString_decodeInvalid3(void)
{
	BEType type;
	bool success;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode("9:asdf", 6, &type, &string, &integer, &list, &dictionary, &usedLength);

	UC_ASSERT(!success);
}

static void BETestString_getEncodedLength0(void)
{
	BEString *string = BEStringCreate("", 0);

	UC_ASSERT(2 == BEStringGetEncodedLength(string));

	CORelease(string);
}

static void BETestString_getEncodedLength1(void)
{
	BEString *string = BEStringCreate("a", 1);

	UC_ASSERT(3 == BEStringGetEncodedLength(string));

	CORelease(string);
}

static void BETestString_getEncodedLength9(void)
{
	BEString *string = BEStringCreate("abcdefghi", 9);

	UC_ASSERT(11 == BEStringGetEncodedLength(string));

	CORelease(string);
}

static void BETestString_getEncodedLength10(void)
{
	BEString *string = BEStringCreate("abcdefghij", 10);

	UC_ASSERT(13 == BEStringGetEncodedLength(string));

	CORelease(string);
}

static void BETestString_getEncodedLength11(void)
{
	BEString *string = BEStringCreate("abcdefghijk", 11);

	UC_ASSERT(14 == BEStringGetEncodedLength(string));

	CORelease(string);
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
	uc_suite_add_test(test_suite, uc_test_create("decode long",           &BETestString_decodeLong));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 0",      &BETestString_decodeInvalid0));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 1",      &BETestString_decodeInvalid1));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 2",      &BETestString_decodeInvalid2));
	uc_suite_add_test(test_suite, uc_test_create("decode invalid 3",      &BETestString_decodeInvalid3));
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
