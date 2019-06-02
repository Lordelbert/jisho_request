#include "jsonHandler.hpp"
#include "Dictionnary.hpp"
#include "rapidjson/document.h"
#include <iostream>
#include <unistr.h>
#include <string>
#include <vector>
#include <utility>

using namespace rapidjson;

void JsonHandler::parse(std::string jsonString)
{
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    const Value& data = document["data"];
    std::vector<std::pair<icu::UnicodeString,icu::UnicodeString>> kanji; // word ,reading
    std::vector<std::string> engSense;
    std::vector<int> jlpt;
    Dictionnary dict;
    for (const auto& it_data : data.GetArray()) {
        for(const auto& it_japanese : it_data["japanese"].GetArray()) {
            kanji.push_back(std::make_pair(it_japanese["word"].GetString(),
                                           it_japanese["reading"].GetString()));
        }
        for(const auto& it_senses : it_data["senses"].GetArray()) {
            for(const auto& it_definitions :it_senses["english_definitions"].GetArray()) {
                engSense.push_back(std::move(it_definitions.GetString()));
            }
        }
        for(const auto& it_jlpt : it_data["jlpt"].GetArray()){
            // jlpt value range in [0,5]
            // tmp is formated as follow jlpt-N5.
            std::string tmp{it_jlpt.GetString()};
            jlpt.push_back(tmp.back()-0x30);
        }
        bool common {it_data["is_common"].GetBool()};
        // push a word in Dictionnary
        //
        dict.addEntry(kanji,engSense,jlpt[0],common);
        kanji.clear();
        engSense.clear();
        jlpt.clear();
    }
    dict.dumToOStream(std::cout,';');
}
