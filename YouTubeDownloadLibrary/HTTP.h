// HTTP.h

namespace HTTP
{
	// Creates get request
	int CreateGetRequest (std::string host, std::string uri, std::string& result);

	// Does full http exchange
	int Exchange (std::string address, std::string request, std::string &response);

	// decodes url encoding
	std::string UrlDecode (std::string url);
}