// fmt.cpp : Defines the functions for FMT class.
//

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
		// 1. Seperate Entries
		std::string field;
		std::vector <std::string> entry;
		std::vector <std::vector<std::string>> entries;

		for (unsigned int i = 0; i < serial.length(); i++)
		{
			switch (serial.at(i))
			{
			case ',':
				entry.push_back(field);
				entries.push_back(entry);
				field.clear();
				entry.clear();
				break;
			case '&':
				entry.push_back(field);
				field.clear();
				break;
			default:
				field.push_back(serial.at(i));
				break;
			}
		}

		// 2. Poputlate FMT
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

			if ( video.isValid() )
			{
				videos.push_back(video);
			}
		}

		return videos;
	}
}
