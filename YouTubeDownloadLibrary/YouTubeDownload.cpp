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


	int YouTubeDownload::SearchVideo (std::vector <Video> videos, Container container, Resolution resolution, Video& result)
	{
		for (int i = 0; i < videos.size(); i++)
		{
			if (videos.at(i).GetContainer() == container && videos.at(i).GetResolution() == resolution)
			{
				result = videos.at(i);
				return 0; // Success
			}
		}

		return -1; // Not found
	}


	int YouTubeDownload::SearchVideo (std::vector <Video> videos, Container container, bool HighestResolutionFirst, Video& result)
	{
		int best = -1; // Invalid start value (error checking)

		for (int i = 0; i < videos.size(); i++)
		{
			if ( videos.at(i).GetContainer() == container )
			{
				// If first load without without check
				if (best == -1) {
					best = i;
					continue;
				}

				// Resolution is higher than previous best and searching for highest available resolution.
				else if ( (videos.at(i).GetResolution() > videos.at(best).GetResolution() && HighestResolutionFirst == true) ||
					// Or resolution is lower than previous best and searching for lowest available resolution.
					( videos.at(i).GetResolution() < videos.at(best).GetResolution() && HighestResolutionFirst == false) )
				{
					best = i;
					continue;
				}
			}
		}

		// If no best was found
		if (best == -1)
		{
			return -1; // failure
		}

		result = videos.at(best);
		return 0; // succuess
	}


	int YouTubeDownload::DownloadToHDD (std::string link, std::fstream file)
	{
		return 0;
	}
}
