#include "Dictionnary.hpp"
#include "JishoRequester.hpp"
#include "jsonHandler.hpp"
#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <unistr.h>
#include <ustream.h>
#include <utility>

int main()
{
	JishoRequester jr;
	icu::UnicodeString test;
	std::cout << "type the kanji string to search" << '\n';
	std::cin >> test;
	Dictionnary dict(jr(std::move(test)));
	dict.sort();
	dict.filter({"見", "火"});
	//std::ofstream file("./toto");
	dict.dumpToOStream(std::cout, ';');
	return 0;
}
