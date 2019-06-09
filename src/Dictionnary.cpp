#include "Dictionnary.hpp"
#include <ostream>
#include <ustream.h>


bool operator<( const Dictionnary::Word& lhs, const Dictionnary::Word& rhs )
{
    return rhs.m_jlpt >= lhs.m_jlpt;
}


// TODO Management of jlpt
// Three case:
//      1.. 1 jlpt for every word
//      2.  n jlpt n words
//      3.  0 jlpt

// looks like we duplicate some code but we remove the if from for loop
void Dictionnary::addEntry(std::vector<std::pair<Ustr_t,Ustr_t>> japanese, std::vector<std::string> sense,
                           std::vector<uint8_t> jlpt, bool common)
{
    if(common){
        if(jlpt.empty()) {
            for(const auto& it_jlpt : japanese)
                m_commonQueue.emplace(std::get<0>(it_jlpt), std::get<1>(it_jlpt),sense);
        }
        if(jlpt.size() == japanese.size()) {
            for(size_t i=0; i< jlpt.size();++i)
                m_commonQueue.emplace(std::get<0>(japanese[i]), std::get<1>(japanese[i]),sense,jlpt[i]);
        }
        if(jlpt.size() == 1) {
            for(const auto& it_jlpt : japanese)
                    m_commonQueue.emplace(std::get<0>(it_jlpt), std::get<1>(it_jlpt),sense,jlpt[0]);
            }
    } else {
        //TODO can uncommon kanji have a jlpt ?
        for(const auto& it_jlpt : japanese)
            m_uncommonQueue.emplace(std::get<0>(it_jlpt), std::get<1>(it_jlpt),sense);

    }
}

void Dictionnary::dumpToOStream(std::ostream& out, char delim) {
    dump(out,delim, m_commonQueue);
    dump(out,delim, m_uncommonQueue);
}
