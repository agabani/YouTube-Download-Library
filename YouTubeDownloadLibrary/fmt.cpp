/**
 * @file fmt.cpp
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

#include "stdafx.h"
#include <stdexcept>

#include "fmt.h"
#include "http.h"

namespace YouTubeDownloadLibrary
{
	FMT::FMT()
	{
	}


	FMT::~FMT()
	{
	}


	std::string FMT::ExtractFMT (std::string feed)
	{
		const std::string keyword = "&url_encoded_fmt_stream_map=";
		size_t start = feed.find(keyword);

		if (start == std::string::npos) {
			return std::string();
		}

		start += keyword.length();
		size_t end = feed.find("&",start);
		return std::string (feed, start, end - start);
	}


	std::vector <YouTubeDownloadLibrary::Video> FMT::ParseFMT (std::string serial)
	{
		// Seperate data into several fields per entry.
		std::string field;
		std::vector <std::string> entry;
		std::vector <std::vector<std::string>> entries;

		for (unsigned int i = 0; i < serial.length(); i++)
		{
			switch (serial.at(i))
			{
			case ',': // Represents new fmt entry delimitor
				entry.push_back(field);
				entries.push_back(entry);
				field.clear();
				entry.clear();
				break;
			case '&': // Represents new field delimitor
				entry.push_back(field);
				field.clear();
				break;
			default: // Represents normal data
				field.push_back(serial.at(i));
				break;
			}
		}

		// Structures and organises fields into their respective entries
		YouTubeDownloadLibrary::Video video;
		std::vector <YouTubeDownloadLibrary::Video> videos;

		for (unsigned int i = 0; i < entries.size(); i++)
		{
			for (unsigned int j = 0; j < entries.at(i).size(); j++)
			{
				if (entries.at(i).at(j).find("fallback_host=") == 0) {
					video.fallback_host = entries.at(i).at(j).substr(14);
				}
				else if (entries.at(i).at(j).find("itag=") == 0) {
					video.itag = entries.at(i).at(j).substr(5);
				}
				else if (entries.at(i).at(j).find("quality=") == 0) {
					video.quality = entries.at(i).at(j).substr(8);
				}
				else if (entries.at(i).at(j).find("sig=") == 0) {
					video.sig = entries.at(i).at(j).substr(4);
				}
				else if (entries.at(i).at(j).find("type=") == 0) {
					video.type = HTTP::UrlDecode(entries.at(i).at(j).substr(5));
				}
				else if (entries.at(i).at(j).find("url=") == 0) {
					video.url = HTTP::UrlDecode(entries.at(i).at(j).substr(4));
				}
				
			}

			// Checks if fmt is valid (compulsory)
			if ( video.Validate() )
			{
				// Adds fmt to list of fmts
				videos.push_back(video);
			}
		}

		return videos;
	}
}
