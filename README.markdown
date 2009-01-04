ddbencode
=========

`ddbencode` is a library implements a MIT-licenced "bencode" encoder and
decoder. It comes with a comprehensive test suite to ensure correctness.

Requirements
------------

`ddbencode` requires a C99-compliant compiler. It has no other dependencies.

Building `ddbencode` requires `rake` (Ruby make), although it should be rather
easy to build the library and applications without `rake`.

Running the unit tests requires `uctest` which is a simple C unit testing
library. The rakefile assumes that `uctest` is placed inside the "vendor"
directory.

Usage
-----

See the source documentation for sample usage.

Examples
-----

List creation example:

	BEList *list = BEListCreate(
		4,                      // number of list entries
		BE_STRING,  "foo",   3, // entry 0
		BE_INTEGER, 123,        // entry 1
		BE_LIST,    someList    // entry 2
	);

Dictionary creation example:

	BEDictionary *dictionary = BEDictionaryCreate(
		4                                   // number of dictionary entries
		"foo",  BE_STRING,     "stuff",  5, // entry 0
		"bar",  BE_INTEGER,    123,         // entry 1
		"baz",  BE_LIST,       someList,    // entry 2
		"quux", BE_DICTIONARY, someDict     // entry 3
	);

Encoding example:

	BEList *list = BEListCreate(...);

	void *data;
	size_t dataLength;

	BEListEncode(list, &data, &dataLength);

Decoding example:

	bool success;

	BEType type;

	char *string = NULL;
	int integer = 0;
	BEList *list = NULL;
	BEDictionary *dictionary = NULL;

	size_t stringLength = 0;
	size_t usedLength = 0;

	success = BEDecode(
		"le", 2,                               // the data and its length
		&type,                                 // the type of the decoded item
		&string, &integer, &list, &dictionary, // the decoded item (only one will be set)
		&stringLength,                         // the length of the decoded string, if any
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

Contact
-------

You can reach me (Denis Defreyne) at <denis.defreyne@stoneship.org>.

References
----------

* BitTorrent specification at http://wiki.theory.org/BitTorrentSpecification
