// Test Application.cpp

#include <iostream>
#include <string>

#include "YouTubeDownloadLibrary.h"

int main (int argc, char * argv[])
{
	std::vector<YouTubeDownloadLibrary::Video> videos = YouTubeDownloadLibrary::YouTubeDownload::GetLink("E4XqGyCa5Vo");

	YouTubeDownloadLibrary::Video video;

	int result =
		YouTubeDownloadLibrary::YouTubeDownload::SearchVideo (
		videos,
		YouTubeDownloadLibrary::YouTubeDownload::Container::MP4,
		true,
		video
		);

	if (result == 0)
	{
		std::cout << "Video Found" << std::endl;
		std::cout << "Container: ";
		switch (video.GetContainer())
		{
		case YouTubeDownloadLibrary::YouTubeDownload::Container::FLV:
			std::cout << "FLV" << std::endl;
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::MP4:
			std::cout << "MP4" << std::endl;
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::_3PG:
			std::cout << "3PG" << std::endl;
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::WEBM:
			std::cout << "WEBM" << std::endl;
			break;
		default:
			break;
		}
		std::cout << "itag: " << video.GetITag() << std::endl;
		std::cout << "Resolution: " << video.GetResolution() << std::endl;
		std::cout << "Type: " << video.GetType() << std::endl;
		std::cout << "URL:" << std::endl << video.GetURL() << std::endl;
	} else {
		std::cout << "Video not Found" << std::endl;
	}

	return 0;
}
