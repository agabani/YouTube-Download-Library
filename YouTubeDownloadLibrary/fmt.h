/**
 * @file fmt.h
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
 * Class that impliments commonly used fmt functions.
 *
 */

#pragma once

#include "YouTubeDownloadLibrary.h"

namespace YouTubeDownloadLibrary
{
	class FMT
	{
	public:
		FMT();
		~FMT();

		/**
		 * @fn	static std::string FMT::ExtractFMT (std::string feed);
		 *
		 * @brief	Extracts the youtube fmt data from text
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	feed	The input text.
		 *
		 * @return	The extracted fmt text.
		 */

		static std::string ExtractFMT (std::string feed);

		/**
		 * @fn	static std::vector <YouTubeDownloadLibrary::Video> FMT::ParseFMT (std::string serial);
		 *
		 * @brief	Parse and structures fmt data.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	serial	Unparsed fmt data.
		 *
		 * @return	Formated and structured fmt data.
		 */

		static std::vector <YouTubeDownloadLibrary::Video> ParseFMT (std::string serial);
	};
}