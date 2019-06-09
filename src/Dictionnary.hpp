#pragma once
#include <iostream>
#include <unistr.h>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <type_traits>

template <typename T, typename = void>
struct is_iterable : std::false_type {};
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                  decltype(std::declval<T>().end())>>
    : std::true_type {};
template< class T >
inline constexpr bool is_iterable_v = is_iterable<T>::value;

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
    std::set<Word> m_commonQueue;
    std::set<Word> m_uncommonQueue;

    // the enable_if is superfluous this template function is private so
    // we know the context
    // It is here for learning purpose and prevent error if we change container class
    template<typename container, typename = std::enable_if_t<is_iterable_v<container>>>
        void dump(std::ostream& out, char delim, const container& wordcontainer)
        {
            for(const auto& it_word : wordcontainer) {
                out << it_word.m_kanji << delim << it_word.m_hiragana << delim;
                for(const auto& eng_it : it_word.m_engSense)
                    out<< eng_it << '\t';
                out << std::endl;
            }
        }

    public:
    void dumpInJson() {return ;}
    void dumpToOStream(std::ostream& out, char delim);
    void addEntry(std::vector<std::pair<Ustr_t,Ustr_t>> japanese,
                  std::vector<std::string> sense, std::vector<uint8_t> jlpt,
                  bool common=0);
};



