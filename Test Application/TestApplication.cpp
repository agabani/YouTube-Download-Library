// Test Application.cpp

#include <iostream>
#include <string>

#include "YouTubeDownloadLibrary.h"

int main (int argc, char * argv[])
{
	YouTubeDownloadLibrary::YouTubeDownload::GetLink("E4XqGyCa5Vo", NULL, NULL);

//	std::cout << YouTubeDownloadLibrary::YouTubeDownload::GetLink("E4XqGyCa5Vo", NULL, NULL) << std::endl;

	std::cin.get();

	return 0;
}
