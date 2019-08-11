#pragma once
#include "operator.hpp"
#include "traits.hpp"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <type_traits>
#include <unistr.h>
#include <utility>
#include <vector>

class Dictionnary {
	using Ustr_t = icu::UnicodeString;

  private:
	struct Word : public IneqComparableTV<Word>, public IneqComparableTV<Word, int> {
		icu::UnicodeString m_kanji; // Word
		icu::UnicodeString m_hiragana; // reading
		std::vector<std::string> m_engSense;
		uint8_t m_jlpt;
		Word(icu::UnicodeString kanji, icu::UnicodeString hiragana,
		     std::vector<std::string> sense, uint8_t jlpt = 0)
		    : m_kanji(std::move(kanji)), m_hiragana(std::move(hiragana)),
		      m_engSense(std::move(sense)), m_jlpt(jlpt)
		{
		}
		friend bool operator<(const Word &lhs, const Word &rhs);
		friend bool operator<(const Dictionnary::Word &lhs, int jlpt);
	};
	friend bool operator<(const Word &lhs, const Word &rhs);
	friend bool operator<(const Dictionnary::Word &lhs, int jlpt);
	std::vector<Word> m_commonQueue;
	std::vector<Word> m_uncommonQueue;

	void filterUtility(std::vector<Word> &, std::vector<Ustr_t>);
	// the enable_if is superfluous this template function is private so
	// we know the context
	// It is here for learning purpose and prevent error if we change container
	// class
	template <typename container, typename = std::enable_if_t<is_iterable_v<container>>>
	void dump(std::ostream &out, char delim, const container &wordcontainer)
	{
		for(const auto &it_word : wordcontainer) {
			out << it_word.m_kanji << delim << it_word.m_hiragana << delim;
			for(const auto &eng_it : it_word.m_engSense) out << eng_it << '\t';
			out << '\n';
		}
		out << std::endl;
	}

  public:
	void dumpToOStream(std::ostream &out, char delim);
	template <typename Comparator = std::less<>> void filter(int jlpt)
	{
		m_commonQueue.erase(std::remove_if(m_commonQueue.begin(), m_commonQueue.end(),
		                                   [jlpt](auto word) -> bool {
			                                   return Comparator()(word, jlpt);
		                                   }),
		                    m_commonQueue.end());
	}
	void filter(std::vector<Ustr_t>);
	template <typename Compare = std::greater_equal<>> void sort(void)
	{
		std::stable_sort(m_commonQueue.begin(), m_commonQueue.end(), Compare());
	}
	void addEntry(std::vector<std::pair<Ustr_t, Ustr_t>> japanese,
	              std::vector<std::string> sense, std::vector<uint8_t> jlpt,
	              bool common = 0);
};
