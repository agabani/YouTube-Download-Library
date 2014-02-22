// YouTubeDownloadLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "YouTubeDownloadLibrary.h"
#include "HTTP.h"
#include <stdexcept>


// Constant Definitions
const std::string Host = "www.youtube.com";
const std::string Port = "80";


namespace YouTubeDownloadLibrary
{
	// FMT structure
	struct FMT {
		std::string	fallback_host, itag, quality, sig, type, url;
	};

	// FMT functions
	std::string ExtractFMT (std::string feed);
	std::vector <FMT> ParseFMT (std::string serial);

	// Class implimentation
	std::string YouTubeDownload::GetLink(std::string vid, int encoding[], int size)
	{
		// Obtain YouTube video information
		std::string request;
		int result = HTTP::CreateGetRequest(Host + ":" + Port, "/get_video_info?video_id=" + vid, request);
		std::string response;
		result = HTTP::Exchange(Host + ":" + Port, request, response);

		// Parse FMT information
		response = ExtractFMT(response);
		response = HTTP::UrlDecode(response);
		std::vector <FMT> links = ParseFMT(response);

		// Debug Code
/*		for (int i = 0; i < links.size(); i++)
		{
			std::cout << "---- New Link ----" << std::endl;
			std::cout << "Fallback Host:\t" << links.at(i).fallback_host << std::endl;
			std::cout << "iTag:\t\t" << links.at(i).itag << std::endl;
			std::cout << "Quality:\t" << links.at(i).quality << std::endl;
			std::cout << "Signature:\t" << links.at(i).sig << std::endl;
			std::cout << "Type:\t\t" << links.at(i).type << std::endl;
			std::cout << "URL:\t\t" << links.at(i).url << std::endl;
			std::cout << std::endl << std::endl;
		}
*/
		return response;
	}


	int YouTubeDownload::DownloadToHDD (std::string link, std::fstream file)
	{
		return 0;
	}
}


std::string YouTubeDownloadLibrary::ExtractFMT (std::string feed)
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


std::vector <YouTubeDownloadLibrary::FMT> YouTubeDownloadLibrary::ParseFMT (std::string serial)
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
	FMT fmt;
	std::vector <FMT> encodes;

	for (unsigned int i = 0; i < entries.size(); i++)
	{
		for (unsigned int j = 0; j < entries.at(i).size(); j++)
		{
			if (entries.at(i).at(j).find("fallback_host=") == 0) {
				fmt.fallback_host = entries.at(i).at(j).substr(14);
			}
			else if (entries.at(i).at(j).find("itag=") == 0) {
				fmt.itag = entries.at(i).at(j).substr(5);
			}
			else if (entries.at(i).at(j).find("quality=") == 0) {
				fmt.quality = entries.at(i).at(j).substr(8);
			}
			else if (entries.at(i).at(j).find("sig=") == 0) {
				fmt.sig = entries.at(i).at(j).substr(4);
			}
			else if (entries.at(i).at(j).find("type=") == 0) {
				fmt.type = HTTP::UrlDecode(entries.at(i).at(j).substr(5));
			}
			else if (entries.at(i).at(j).find("url=") == 0) {
				fmt.url = HTTP::UrlDecode(entries.at(i).at(j).substr(4));
			}
		}

		if ( !fmt.fallback_host.empty() && !fmt.itag.empty() && !fmt.quality.empty()
			&& !fmt.sig.empty() && !fmt.type.empty() && !fmt.url.empty() )
		{
			encodes.push_back(fmt);
		}
	}

	// Debug Code
/*	for (int i = 0; i < encodes.size(); i++)
	{
		std::cout << "--- ENCODE : " << i << " ---" << std::endl;
		std::cout << encodes.at(i).fallback_host << std::endl;
		std::cout << encodes.at(i).itag << std::endl;
		std::cout << encodes.at(i).quality << std::endl;
		std::cout << encodes.at(i).sig << std::endl;
		std::cout << encodes.at(i).type << std::endl;
		std::cout << encodes.at(i).url << std::endl;
		std::cout << std::endl;
	}
*/
	return encodes;
}
