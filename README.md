JISHO Requester
===============

Perform request using jisho API.
[https://jisho.org/]

Supports:

- Single word request.
- Word composed by a list of kanji.
  Words are sorted by jlpt level and "is_common" key in jisho API.


Dependency:
-----------

libcurl: 7.52 (libcurl3 package on debian stretch).
libicu:  57.1 (libicu-dev debian stretch)
Json parser: rapidjson v1.1.0
