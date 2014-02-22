// Test Application.cpp

#include <iostream>
#include <string>

#include "YouTubeDownloadLibrary.h"

int main (int argc, char * argv[])
{
	std::vector<YouTubeDownloadLibrary::Video> videos = YouTubeDownloadLibrary::YouTubeDownload::GetLink("E4XqGyCa5Vo");

	std::cout << "Found " << videos.size() << " videos." << std::endl;

	for (unsigned int i = 0; i < videos.size(); i++)
	{
		std::cout << "--- Video number: " << i+1 << " ---" << std::endl;
		std::cout << videos.at(i).GetITag() << std::endl;
		std::cout << videos.at(i).GetQuality() << std::endl;
		std::cout << videos.at(i).GetType() << std::endl;
		std::cout << videos.at(i).GetURL() << std::endl;
		std::cout << std::endl;
	}

	std::cin.get();

	return 0;
}
