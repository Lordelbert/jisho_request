#include "JishoRequester.hpp"
#include "jsonHandler.hpp"
#include <string>
#include <locale>
#include <iostream>
#include <unistr.h>
#include <utility>
#include <ustream.h>

int main () {
    JishoRequester jr;
    JsonHandler jh;
    icu::UnicodeString test;
    std::cout<<"type the kanji string to search" << '\n';
    std::cin >> test;

    std::string jsonString{jr(std::move(test))};
    std::cout << jsonString;
    jh.parse(jsonString);
    return 0;
}
