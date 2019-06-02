#include "Dictionnary.hpp"
#include <ostream>
#include <ustream.h>


bool operator<( const Dictionnary::Word& lhs, const Dictionnary::Word& rhs )
{
    return rhs.m_jlpt < lhs.m_jlpt;
}


// TODO Management of jlpt
// Three case:
//      1.. 1 jlpt for every word
//      2.  n jlpt n words
//      3.  0 jlpt



void Dictionnary::addEntry(std::vector<std::pair<Ustr_t,Ustr_t>> japanese, std::vector<std::string> sense, uint8_t jlpt, bool common)
{
    for(const auto& jp_it : japanese) {
        if(common) {
            m_commonQueue.emplace(std::get<0>(jp_it), std::get<1>(jp_it),sense, jlpt);
        } else {
            m_uncommonQueue.emplace(std::get<0>(jp_it), std::get<1>(jp_it),sense, jlpt);
        }
    }
}
void Dictionnary::addEntry(std::vector<std::pair<Ustr_t,Ustr_t>> japanese, std::vector<std::string> sense, bool common)
{
    for(const auto& jp_it : japanese) {
        if(common) {
            m_othersCommon.push_back(Word(std::get<0>(jp_it), std::get<1>(jp_it),sense));
        } else {
            m_othersUncommon.push_back(Word(std::get<0>(jp_it), std::get<1>(jp_it),sense));
        }
    }
}

void Dictionnary::dumToOStream(std::ostream& out, char delim) {
    while(!m_commonQueue.empty()) {
        const auto& common_it {m_commonQueue.top()};
        out << common_it.m_kanji << delim << common_it.m_hiragana << delim;
        for(const auto& eng_it : common_it.m_engSense)
            out<< eng_it << '\t';
        out << std::endl;
        m_commonQueue.pop();
    }
}
