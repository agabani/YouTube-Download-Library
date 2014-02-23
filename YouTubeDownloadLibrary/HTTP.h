/**
 * @file http.h
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

#pragma once


namespace YouTubeDownloadLibrary
{
	class HTTP
	{
	public:

		/**
		 * @fn	HTTP::HTTP();
		 *
		 * @brief	Default constructor.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 */

		HTTP();

		/**
		 * @fn	HTTP::~HTTP();
		 *
		 * @brief	Destructor.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 */

		~HTTP();

		/**
		 * @fn	static int HTTP::CreateGetRequest (std::string host, std::string uri, std::string& result);
		 *
		 * @brief	Creates a HTTP get request.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	host	  	The host.
		 * @param	uri		  	URI of the document.
		 * @param [out]	result	The GET request.
		 *
		 * @return	Returns 0 if success.
		 */

		static int CreateGetRequest (std::string host, std::string uri, std::string& result);

		/**
		 * @fn	static int HTTP::Exchange (std::string address, std::string request, std::string &response);
		 *
		 * @brief	Connects to target host and performs full HTTP exchange.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	address			The hostname and port to exchange with.
		 * @param	request			The HTTP GET request.
		 * @param [out]	response	The response of the HTTP request.
		 *
		 * @return	Returns 0 if success.
		 */

		static int Exchange (std::string address, std::string request, std::string &response);

		/**
		 * @fn	static std::string HTTP::UrlDecode (std::string url);
		 *
		 * @brief	Decodes URL encoded text.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	url	URL of the document.
		 *
		 * @return	returns decoded text.
		 */

		static std::string UrlDecode (std::string url);

		/**
		 * @fn	static int HTTP::DownloadFile (std::string address, std::fstream& file, bool displayProgress);
		 *
		 * @brief	Downloads the file.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	address		   	The full URL of target file.
		 * @param [out]	file	   	An open file stream configured to write in binary mode.
		 * @param	displayProgress	True to display progress.
		 *
		 * @return	Returns remaining bytes to download. Returns -1 if cannot connect to host.
		 */

		static int DownloadFile (std::string address, std::fstream& file, bool displayProgress);

	private:

		/**
		 * @brief	Size of the maximum read buffer.
		 */

		static const int MaxBufSize;

		/**
		 * @brief	The user agent.
		 */

		static const std::string UserAgent;

		/**
		 * @brief	The new line character for HTTP.
		 */

		static const std::string NewLine;
	};
}
