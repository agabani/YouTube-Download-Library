#include "stdafx.h"


// OpenSSl Library
#include <openssl\bio.h>
#include <openssl\ssl.h>
#include <openssl\err.h>


namespace HTTP
{
	// Constant Definitions
	const int MaxBufSize = 4092;
	const std::string UserAgent = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:19.0) Gecko/20100101 Firefox/19.0";
	const std::string NewLine = "\r\n";


	int CreateGetRequest (std::string host, std::string uri, std::string& result)
	{
		result  =
			"GET " + uri + " HTTP/1.1" + NewLine +
			"Host: " + host + NewLine +
			"User Agent: " + UserAgent + NewLine +
			"Connection: close" + NewLine +
			NewLine;

		return 0;
	}


	int Exchange (std::string address, std::string request, std::string &response)
	{
		BIO* bio = BIO_new_connect(&address[0]);

		if (bio == NULL) {
			ERR_print_errors_fp(stderr);
			return -1;
		}
		BIO_puts(bio, request.c_str());

		std::string recvbuf;
		response.clear();

		while (1) {
			recvbuf.resize(MaxBufSize);

			int iResult = BIO_read(bio, &recvbuf[0], recvbuf.length());

			if (iResult == 0) {
				break;
			}
			else if (iResult < 0) {
				if (!BIO_should_retry(bio))	{
					BIO_free_all(bio);
					return -1;
				}
			}
			else {
				response.append(recvbuf.substr(0,iResult));
			}
		}

		BIO_free_all(bio);
		return 0;
	}


	std::string UrlDecode (std::string url)
	{
		std::string decode;
		std::stringstream ss;
		int hexval;

		for (unsigned int i = 0; i < url.length(); i++)
		{
			if (url.at(i) == '%') {
				ss << std::hex << url.at(++i);
				ss << std::hex << url.at(++i);
				ss >> hexval;
				ss.clear();
				decode.push_back(hexval);
			}
			else {
				decode.push_back(url.at(i));
			}
		}

		return decode;
	}
}
