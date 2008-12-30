#include "test/bencode_test_string.h"
#include "test/bencode_test_integer.h"
#include "test/bencode_test_list.h"
#include "test/bencode_test_dictionary.h"

int main(void)
{
	BETestString();
	BETestInteger();
	BETestList();
	BETestDictionary();

	return 0;
}
