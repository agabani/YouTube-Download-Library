/**
 * @file YouTubeDownload.cpp
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
 * Class representing the information contained by a video.
 *
 */

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
	std::string YouTubeDownload::GetVersion ()
	{
		return "1.0.0";
	}


	std::vector <Video> YouTubeDownload::GetLink(std::string vid)
	{
		// Request and obtain raw video information from youtube.
		std::string request;
		int result = HTTP::CreateGetRequest(Host + ":" + Port, "/get_video_info?video_id=" + vid, request);
		std::string response;
		result = HTTP::Exchange(Host + ":" + Port, request, response);

		// Parse and structure fmt information.
		response = FMT::ExtractFMT(response);
		response = HTTP::UrlDecode(response);
		std::vector <Video> links = FMT::ParseFMT(response);

		// Returns structured fmt information on all found videos.
		return links;
	}


	int YouTubeDownload::SearchVideo (std::vector <Video> videos, Container container, Resolution resolution, Video& result)
	{
		for (unsigned int i = 0; i < videos.size(); i++)
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

		for (unsigned int i = 0; i < videos.size(); i++)
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


	int YouTubeDownload::DownloadToHDD (std::string link, std::fstream& file, bool displayProgress)
	{
		int result = HTTP::DownloadFile(link, file, displayProgress);

		if (displayProgress == true) {
			std::cout << std::endl;
		}

		return 0;
	}
}
