#pragma once

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <unistr.h>
/**
 * This class is used as a proxy between
 * curl and our program.
 *
 * For a first version we only consider
 * single threaded thus we use 'easy' interface
 * of curl.
 *
 * TODO: go multithread ?
 *
 **/

class JishoRequester {
  private:
	// curl easy handler
	CURL *m_curl;

  public:
	// RAII compliant
	JishoRequester(void)
	{
		// let's go default on this
		// TODO maybe use only what we need
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		if(!m_curl) {
			std::cerr << "curl easy init failed" << '\n';
		}
		return;
	}
	~JishoRequester(void)
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();
	}

	std::string operator()(icu::UnicodeString kanji);

  private:
	static size_t write_data(void *contents, size_t size, size_t nmemb, void *userp)
	{
		try {
			((std::string *)userp)->append((char *)contents, size * nmemb);
		}
		catch(const std::length_error &e) {
			return 0;
		}
		catch(const std::bad_alloc &e) {

			return 0;
		}
		return size * nmemb;
	}
};
