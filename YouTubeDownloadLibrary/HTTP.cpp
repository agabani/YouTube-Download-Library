// http.cpp : Defines the functions for HTTP class.
//

#include "stdafx.h"
#include <stdexcept>

#include "http.h"
#include <math.h>

// OpenSSl Library
#include <openssl\bio.h>
#include <openssl\ssl.h>
#include <openssl\err.h>

namespace YouTubeDownloadLibrary
{
	const int HTTP::MaxBufSize = 4092;
	const std::string HTTP::UserAgent = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:19.0) Gecko/20100101 Firefox/19.0";
	const std::string HTTP::NewLine = "\r\n";


	HTTP::HTTP ()
	{
	}


	HTTP::~HTTP ()
	{
	}


	int HTTP::CreateGetRequest (std::string host, std::string uri, std::string& result)
	{
		result  =
			"GET " + uri + " HTTP/1.1" + NewLine +
			"Host: " + host + NewLine +
			"User Agent: " + UserAgent + NewLine +
			"Connection: close" + NewLine +
			NewLine;

		return 0;
	}


	int HTTP::Exchange (std::string address, std::string request, std::string &response)
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

	std::string HTTP::UrlDecode (std::string url)
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


	int HTTP::DownloadFile (std::string address, std::fstream& file, bool displayProgress)
	{
		// Get hostname
		//		std::cout << link << std::endl;
		std::string hostname, uri;

		int beg, end;

		beg = address.find("//");
		end = address.find("/",++++beg);

		hostname = address.substr(beg, end - beg);
		uri = address.substr(end);

		//		std::cout << hostname << std::endl;
		//		std::cout << uri << std::endl;

		// Create request
		std::string request;
		int result = HTTP::CreateGetRequest(hostname, uri, request);

		//		std::cout << request << std::endl;

		// Connect to host
		std::string link = hostname + ":80";
		BIO* bio = BIO_new_connect(&link[0]);

		if (bio == NULL) {
			ERR_print_errors_fp(stderr);
			return -1;
		}

		// Send request
		BIO_puts(bio, request.c_str());

		// Download
		std::string downloadStream, httpHeader;
		int totalBytes, downloadedBytes, displayedBytes;

		while (1) {
			downloadStream.resize(MaxBufSize);

			int x = BIO_read(bio, &downloadStream[0], downloadStream.length());
			downloadStream.resize(x);

			if (x == 0) {
				break;
			}
			else if (x < 0) {
				if (!BIO_should_retry(bio)) {
					BIO_free_all(bio);
					return -1;
				}
			}
			else {
				// check if http header is complete
				int pos = httpHeader.find(NewLine + NewLine);

				// if not complete
				if (pos == std::string::npos) {
					// check for send of header in current stream
					pos = downloadStream.find(NewLine + NewLine);

					// if end of header is not found dump all of stream into header and continue
					if (pos == std::string::npos) {
						httpHeader.append(downloadStream);
						continue;
					}

					// else copy the remaining header into the header and dump the rest of the stream into the file and get file size
					else {
						httpHeader.append(downloadStream.substr(0,pos + std::string(NewLine + NewLine).length()));
						file << downloadStream.substr(pos + std::string(NewLine + NewLine).length());

						// Get total file size
						beg = httpHeader.find("Content-Length: ") + std::string("Content-Length: ").length();
						end = httpHeader.find(NewLine, beg);

						std::stringstream ss;
						ss << httpHeader.substr(beg, end-beg);
						ss >> totalBytes;

						if (displayProgress == true) {
							std::cout << "File Size: " << (double)totalBytes / 1024 / 1024 << "MB" << std::endl;
						}

						// Add downloaded bytes to monitor
						downloadedBytes = downloadStream.substr(pos + std::string(NewLine + NewLine).length()).length();
						displayedBytes = 0;

						continue;
					}
				}
				
				// but if complete, dump stream into file
				else {
					file << downloadStream;

					// Add downloaded bytes to monitor
					downloadedBytes += x;

					// display progress bar every few bytes
					if (displayProgress == true) {
						
						if (downloadedBytes > (displayedBytes + 200*1024) || downloadedBytes == totalBytes)
						{
							int totaldotz=40;
							double fractiondownloaded = (double)(downloadedBytes) / (double)totalBytes;
							int dotz = fractiondownloaded * totaldotz;

							int ii=0;
							printf("%3.0f%% [",fractiondownloaded*100);
							for ( ; ii < dotz;ii++) {
								printf("=");
							}
							for ( ; ii < totaldotz;ii++) {
								 printf(" ");
							}
							printf("]\r");
							fflush(stdout);

							displayedBytes = downloadedBytes;
						}
					}
				}
			}
		}

		return totalBytes - downloadedBytes;
	}
}
