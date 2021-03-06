#include "Dictionnary.hpp"
#include <ostream>
#include <ustream.h>
namespace {
icu::RegexMatcher createRegexp(std::vector<icu::UnicodeString> kanjiList)
{
	icu::UnicodeString regexString = "[";
	for(const auto it : kanjiList) regexString += it + "|";
	regexString.replaceBetween(regexString.length() - 1, regexString.length(), "]");
	UErrorCode status = U_ZERO_ERROR;
	return icu::RegexMatcher{regexString, 0, status};
}
} // namespace
bool operator<(const Dictionnary::Word &lhs, const Dictionnary::Word &rhs)
{
	return rhs.m_jlpt < lhs.m_jlpt;
}

bool operator<(const Dictionnary::Word &lhs, int jlpt) { return lhs.m_jlpt < jlpt; }
// Management of jlpt
// Three case:
//      1.. 1 jlpt for every word
//      2.  n jlpt n words
//      3.  0 jlpt

// looks like we duplicate some code but we remove the if from for loop
void Dictionnary::addEntry(std::vector<std::pair<Ustr_t, Ustr_t>> japanese,
                           std::vector<std::string> sense, std::vector<uint8_t> jlpt,
                           bool common)
{
	if(common) {
		if(jlpt.empty()) {
			for(const auto &it_jlpt : japanese)
				m_commonQueue.emplace_back(std::get<0>(it_jlpt), std::get<1>(it_jlpt),
				                           sense);
		}
		if(jlpt.size() == japanese.size()) {
			for(size_t i = 0; i < jlpt.size(); ++i)
				m_commonQueue.emplace_back(std::get<0>(japanese[i]),
				                           std::get<1>(japanese[i]), sense, jlpt[i]);
		}
		if(jlpt.size() == 1) {
			for(const auto &it_jlpt : japanese)
				m_commonQueue.emplace_back(std::get<0>(it_jlpt), std::get<1>(it_jlpt),
				                           sense, jlpt[0]);
		}
	}
	else {
		for(const auto &it_jlpt : japanese)
			m_uncommonQueue.emplace_back(std::get<0>(it_jlpt), std::get<1>(it_jlpt),
			                             sense);
	}
	return;
}
void Dictionnary::dumpToOStream(std::ostream &out, char delim)
{
	dump(out, delim, m_commonQueue);
	dump(out, delim, m_uncommonQueue);
	return;
}
void Dictionnary::filterUtility(std::vector<Word> &queue, icu::RegexMatcher& matcher)
{
	std::vector<Word> FilterQueue;
	FilterQueue.reserve(queue.size());
	for(const auto it : queue) {
		matcher.reset(it.m_kanji);
		if(matcher.find()) FilterQueue.emplace_back(it);
	}
	queue = std::move(FilterQueue);
	return;
}
void Dictionnary::filter(std::vector<Ustr_t> kanjiList)
{
	icu::RegexMatcher matcher{createRegexp(std::move(kanjiList))};
	std::thread common(&Dictionnary::filterUtility, this, std::ref(m_commonQueue),
	                   std::ref(matcher));
	std::thread uncommon(&Dictionnary::filterUtility, this, std::ref(m_uncommonQueue),
	                     std::ref(matcher));
	common.join();
	uncommon.join();
}
