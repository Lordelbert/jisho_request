#include "JishoRequester.hpp"
#include "jsonHandler.hpp"

#include <cstdlib>
#include <cstring>
static const char fmtRequest[] =
    "https://jisho.org/api/v1/search/words?keyword=%s&page=%d";
Dictionnary JishoRequester::operator()(icu::UnicodeString kanji)
{
	JsonHandler jh;
	Dictionnary dict;
	bool empty = false;
	std::string tmp;
	kanji.toUTF8String(tmp);
	std::shared_ptr<char> fmt(curl_easy_escape(m_curl, tmp.c_str(), 0),curl_free);
	std::shared_ptr<char>request ((char *)calloc(std::strlen(fmtRequest) + std::strlen(fmt.get()) + 3, sizeof(char)),free);
	for(int i= 1; !empty;++i) {
		sprintf(request.get(), fmtRequest, fmt.get(), i);
		curl_easy_setopt(m_curl, CURLOPT_URL, request.get());
		// what to do with data
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
		// where to store
		std::string buffer;
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &buffer);
		// Execute
		CURLcode errorCode = curl_easy_perform(m_curl);
		if(errorCode != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(errorCode)
			          << '\n';
		}
		dict.append(jh.parse(buffer, empty));
	}
	return dict;
}
