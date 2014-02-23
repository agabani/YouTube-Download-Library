/**
 * @file http.cpp
 * @author agabani
 * @version 1.0
 *
 * @section LICENCE
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Class that impliments commonly used network functions used for HTTP client
 * applications.
 *
 */

#include "stdafx.h"
#include <stdexcept>

#include "http.h"

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
		// Extracts host and uri from address.
		int beg = address.find("//");
		int end = address.find("/",++++beg);
		std::string hostname = address.substr(beg, end - beg);
		std::string uri = address.substr(end);

		// Creates GET request.
		std::string request;
		int result = HTTP::CreateGetRequest(hostname, uri, request);

		// Connects to host.
		std::string link = hostname + ":80";
		BIO* bio = BIO_new_connect(&link[0]);

		if (bio == NULL) {
			ERR_print_errors_fp(stderr);
			return -1; // Failure.
		}

		// Send GET request to host.
		BIO_puts(bio, request.c_str());

		// Download file from host.
		std::string downloadStream, httpHeader;
		int totalBytes, downloadedBytes, displayedBytes;

		while (1) {
			// Set read buffer to maximum size.
			downloadStream.resize(MaxBufSize);

			// Read recieved packet and resize read buffer accordingly.
			int x = BIO_read(bio, &downloadStream[0], downloadStream.length());
			downloadStream.resize(x);

			// If download complete...
			if (x == 0) {
				break; // Exit download loop.
			}
			// If connection lost...
			else if (x < 0) {
				// If retry limit has been reached...
				if (!BIO_should_retry(bio)) {
					BIO_free_all(bio);
					return -1; // Failure.
				}
			}
			// If data is in the read buffer...
			else {
				// Check if the header is complete by looking for the double newline in the stored header.
				int pos = httpHeader.find(NewLine + NewLine);

				// If complete header was not found in stored header...
				if (pos == std::string::npos) {
					// Check for end of header in the read buffer.
					pos = downloadStream.find(NewLine + NewLine);

					// If the end of the header was not found...
					if (pos == std::string::npos) {
						// Append all data in read buffer to header and start next read cycle.
						httpHeader.append(downloadStream);
						continue;
					}

					// If the end of header was found in the read buffer...
					else {
						// Copy the remaining header to the header.
						httpHeader.append(downloadStream.substr(0,pos + std::string(NewLine + NewLine).length()));

						// Write the remaining data to give file.
						file << downloadStream.substr(pos + std::string(NewLine + NewLine).length());

						// Extract the content size of body and store for future reference.
						beg = httpHeader.find("Content-Length: ") + std::string("Content-Length: ").length();
						end = httpHeader.find(NewLine, beg);

						std::stringstream ss;
						ss << httpHeader.substr(beg, end-beg);
						ss >> totalBytes;

						// If user wishes to display download feedback...
						if (displayProgress == true) {
							// Display exact filesize in MB.
							std::cout << "File Size: " << (double)totalBytes / 1024 / 1024 << "MB" << std::endl;
						}

						// Add downloaded bytes to monitor and start next read cycle.
						downloadedBytes = downloadStream.substr(pos + std::string(NewLine + NewLine).length()).length();
						displayedBytes = 0;
						continue;
					}
				}
				
				// If header is complete...
				else {
					// Write contents of read buffer to file.
					file << downloadStream;

					// Add downloaded bytes to monitor.
					downloadedBytes += x;

					// If user wants to display download feedback...
					if (displayProgress == true) {
						
						// If 200KB has been downloaded since the last time the feedback GUI has been updated.
						if (downloadedBytes > (displayedBytes + 200*1024) || downloadedBytes == totalBytes)
						{
							// Draw feedback GUI.
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

							// Update the previous recording of bytes displayed to the current number of bytes downloaded.
							displayedBytes = downloadedBytes;
						}
					}
				}
			}
		}

		// Return the remaining number of bytes to download.
		return totalBytes - downloadedBytes;
	}
}
