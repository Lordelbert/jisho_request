#include "jsonHandler.hpp"
#include "rapidjson/document.h"
#include <iostream>
#include <unistr.h>
#include <string>
#include <vector>
using namespace rapidjson;

void JsonHandler::parse(std::string jsonString)
{
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    const Value& data = document["data"];
    std::vector<icu::UnicodeString> kanji; // word
    std::vector<icu::UnicodeString> hiragana; // reading
    std::vector<std::string> engSense;
    std::vector<int> jlpt;

    for (const auto& it_data : data.GetArray()) {
        for(const auto& it_japanese : it_data["japanese"].GetArray()) {
            kanji.push_back(std::move(it_japanese["word"].GetString()));
            hiragana.push_back(std::move(it_japanese["reading"].GetString()));
        }
        for(const auto& it_senses : it_data["senses"].GetArray()) {
            for(const auto& it_definitions :it_senses["english_definitions"].GetArray()) {
                engSense.push_back(std::move(it_definitions.GetString()));
            }
        }
        //std::cout<< "is_common " << it_data["is_common"].GetBool()<< '\t';
        for(const auto& it_jlpt : it_data["jlpt"].GetArray()){
            // jlpt value range in [0,5]
            // tmp is formated as follow jlpt-N5.
            std::string tmp{it_jlpt.GetString()};
            jlpt.push_back(tmp.back()-0x30);
        }
        // push a word in Dictionnary
        //
        kanji.clear();
        hiragana.clear();
        engSense.clear();
        jlpt.clear();
    }
}
