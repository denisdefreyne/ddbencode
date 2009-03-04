ddbencode
=========

`ddbencode` is a library implements a MIT-licenced "bencode" encoder and
decoder. It comes with a comprehensive test suite to ensure correctness.

Requirements
------------

`ddbencode` requires a C99-compliant compiler. It also depends on `CObject`, a
minimalistic reference-counting library that makes memory management in C a
lot easier.

Building `ddbencode` requires `rake` (Ruby make), although it should be rather
easy to build the library and applications without `rake`.

Running the unit tests requires `uctest` which is a simple C unit testing
library. The rakefile assumes that `uctest` is placed inside the "vendor"
directory.

The `CObject` and `uctest` dependencies can be fetched automagically by
issuing the `fetch_dependencies` rake task.

Usage
-----

See the source documentation for sample usage.

Examples
--------

String creation example:

	BEString *string = BEStringCreate(
		"foo", 3
	);

List creation example:

	BEList *list = BEListCreate(
		4,                   // number of list entries
		BE_STRING,  string,  // entry 0
		BE_INTEGER, 123,     // entry 1
		BE_LIST,    someList // entry 2
	);

Dictionary creation example:

	BEDictionary *dictionary = BEDictionaryCreate(
		4                                // number of dictionary entries
		"foo",  BE_STRING,     string,   // entry 0
		"bar",  BE_INTEGER,    123,      // entry 1
		"baz",  BE_LIST,       someList, // entry 2
		"quux", BE_DICTIONARY, someDict  // entry 3
	);

Encoding example:

	BEList *list = BEListCreate(...);

	void *data;
	size_t dataLength;

	BEListEncode(list, &data, &dataLength);

Decoding example:

	bool success;

	BEType type;

	BEString *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t usedLength = 0;

	success = BEDecode(
		"le", 2,                               // the data and its length
		&type,                                 // the type of the decoded item
		&string, &integer, &list, &dictionary, // the decoded item
		&usedLength                            // the amount of consumed bytes
	);

	if(success)
	{
		puts("successfully decoded");
		if(type == BE_STRING)
			printf("We have a string: %s\n", string);
		else if(type == BE_INTEGER)
			printf("We have an integer: %s\n", integer);
		// etc...
	}

Tests
-----

`ddbencode` comes with a comprehensive test suite to ensure the correctness of
its implementation. Issue the `test` rake task in order to run the test suite.
Running the test suite should not cause any failures to be reported; if one or
more tests fail, please contact me (see below).

Contact
-------

You can reach me (Denis Defreyne) at <denis.defreyne@stoneship.org>.

References
----------

* BitTorrent specification at http://wiki.theory.org/BitTorrentSpecification
