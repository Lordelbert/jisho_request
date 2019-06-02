#pragma once
#include <iostream>
#include <unistr.h>
#include <string>
#include <vector>
#include <utility>
#include <queue>

class Dictionnary {
    using Ustr_t = icu::UnicodeString;
    private:
    struct Word {
        icu::UnicodeString m_kanji; // Word
        icu::UnicodeString m_hiragana; // reading
        std::vector<std::string> m_engSense;
        uint8_t m_jlpt;
        Word(icu::UnicodeString kanji, icu::UnicodeString hiragana,
                std::vector<std::string> sense, uint8_t jlpt=0) :
            m_kanji(std::move(kanji)), m_hiragana(std::move(hiragana)),
            m_engSense(std::move(sense)), m_jlpt(jlpt) {}
        friend bool operator< ( const Word& lhs, const Word& rhs );
    };

    friend bool operator< ( const Word& lhs, const Word& rhs );
    std::priority_queue<Word> m_commonQueue;
    std::priority_queue<Word> m_uncommonQueue;
    std::vector<Word> m_othersCommon;
    std::vector<Word> m_othersUncommon;

    public:
    void dumpInJson() {return ;}
    void dumToOStream(std::ostream& out, char delim);
    void addEntry(std::vector<std::pair<Ustr_t,Ustr_t>> japanese,
                  std::vector<std::string> sense, uint8_t jlpt, bool common);
    void addEntry(std::vector<std::pair<Ustr_t,Ustr_t>> japanese,
                  std::vector<std::string> sense, bool common);
};

