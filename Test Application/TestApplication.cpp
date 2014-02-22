// Test Application.cpp

#include <iostream>
#include <string>
#include <fstream>

#include "YouTubeDownloadLibrary.h"

int main (int argc, char * argv[])
{
	std::string videoID = "-U-hf6go8as";
	std::vector<YouTubeDownloadLibrary::Video> videos = YouTubeDownloadLibrary::YouTubeDownload::GetLink(videoID);

	YouTubeDownloadLibrary::Video video;

	int result =
		YouTubeDownloadLibrary::YouTubeDownload::SearchVideo (
			videos,
			YouTubeDownloadLibrary::YouTubeDownload::Container::MP4,
			true,
			video
		);

	if (result != 0) {
		return -1;
	}

	std::string filename;

	switch (video.GetContainer())
		{
		case YouTubeDownloadLibrary::YouTubeDownload::Container::FLV:
			filename = videoID + ".flv";
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::MP4:
			filename = videoID + ".mp4";
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::_3PG:
			filename = videoID + ".3pg";
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::WEBM:
			filename = videoID + ".webm";
			break;
		default:
			return -1;
			break;
		}

	std::fstream file;

	file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	YouTubeDownloadLibrary::YouTubeDownload::DownloadToHDD(video.GetURL(), file, true);

	file.close();

	std::cin.get();

	return 0;
}
