#pragma once
#include <iostream>
#include <unistr.h>
#include <string>
#include <vector>
class Dictionnary {
    using unicodeVector_t = std::vector<icu::UnicodeString>;
    private:
        class Word {
            icu::UnicodeString m_kanji; // Word
            unicodevector m_hiragana; // reading
            std::vector<std::string> m_engSense;
            int m_jlpt;
            bool operator< (Word rhs) {
                return this.jlpt < rhs.jlpt;
            }
            Word(icu::UnicodeString kanji,unicodeVector_t hiragana
                 std::vector<std::string> sense,jlpt)
                : m_kanji(std::move(kanji)), m_hiragana(std::move(hiragana)),
                  m_engSense(std::move(sense)), m_jlpt(jlpt) {}
        }

        std::priority_queue<Word> m_commonQueue;
        std::priority_queue<Word> m_unCommonQueue;
        std::vector<Word> m_othersCommon;
        std::vector<Word> m_othersUncommon;

    public:
        void dumpInJson {return -1;}
        void dumToStdout {return -1;}
        void addEntry(unicodeVector_t kanji, unicodeVector_t hiragana,
                  std::vector<std::string> sense, jlpt, bool common);
        void addEntry(unicodeVector_t kanji, unicodeVector_t hiragana,
                  std::vector<std::string> senses, bool common);
}
