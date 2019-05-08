#include "JishoRequester.hpp"
#include <string>
#include <locale>
#include <iostream>
#include <unistr.h>
#include <utility>
#include <ustream.h>

int main () {
    JishoRequester jr;
    icu::UnicodeString test;
    std::cin >> test;

    jr(std::move(test));
    return 0;
}
