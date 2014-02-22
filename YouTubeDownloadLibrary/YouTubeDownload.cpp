// YouTubeDownloadLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdexcept>

#include "fmt.h"
#include "http.h"
#include "YouTubeDownloadLibrary.h"


// Constant Definitions
const std::string Host = "www.youtube.com";
const std::string Port = "80";

namespace YouTubeDownloadLibrary
{
	std::vector <Video> YouTubeDownload::GetLink(std::string vid)
	{
		// Obtain YouTube video information
		std::string request;
		int result = HTTP::CreateGetRequest(Host + ":" + Port, "/get_video_info?video_id=" + vid, request);
		std::string response;
		result = HTTP::Exchange(Host + ":" + Port, request, response);

		// Parse FMT information
		response = FMT::ExtractFMT(response);
		response = HTTP::UrlDecode(response);
		std::vector <Video> links = FMT::ParseFMT(response);

		return links;
	}

	int YouTubeDownload::DownloadToHDD (std::string link, std::fstream file)
	{
		return 0;
	}
}
