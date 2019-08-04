#include "JishoRequester.hpp"
#include <cstdlib>
#include <cstring>
static const char fmtRequest[] = "https://jisho.org/api/v1/search/words?keyword=%s";
std::string JishoRequester::operator()(icu::UnicodeString kanji)
{
	std::string tmp;
	kanji.toUTF8String(tmp);
	char *fmt(curl_easy_escape(m_curl, tmp.c_str(), 0));
	char *request =
	    (char *)calloc(std::strlen(fmtRequest) + std::strlen(fmt) + 1, sizeof(char));
	sprintf(request, fmtRequest, fmt);
	curl_free(fmt);
	curl_easy_setopt(m_curl, CURLOPT_URL, request);
	free(request);

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
	return buffer;
}
