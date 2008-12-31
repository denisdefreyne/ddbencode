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

Status
------

Implemented:

* Encoding
	* String
	* Integer
* Decoding
	* String
	* Integer

Not implemented:

* Creation/deletion
	* List
	* Dictionary
* Encoding
	* List
	* Dictionary
* Decoding
	* List
	* Dictionary

Usage
-----

List creation example:

	BEList *list = BEListCreate(
		4,                   // number of list entries
		BE_STRING,  "foo",   // entry 0
		BE_INTEGER, 123,     // entry 1
		BE_LIST,    someList // entry 2
	);

Dictionary creation example:

	BEDictionary *dictionary = BEDictionaryCreate(
		4                                // number of dictionary entries
		"foo",  BE_STRING,     "stuff",  // entry 0
		"bar",  BE_INTEGER,    123,      // entry 1
		"baz",  BE_LIST,       someList, // entry 2
		"quux", BE_DICTIONARY, someDict  // entry 3
	);

Encoding example:

	…

Decoding example:

	BEType type;
	void *result = BEDecode(data, dataLength, &type);
	if(type == BE_STRING)
		printf("We have a string: %s\n", (char *)result);

Contact
-------

You can reach me (Denis Defreyne) at <denis.defreyne@stoneship.org>.

References
----------

* BitTorrent specification at http://wiki.theory.org/BitTorrentSpecification
