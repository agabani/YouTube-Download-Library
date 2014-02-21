// Test Application.cpp

#include <iostream>

#include "YouTubeDownloadLibrary.h"

int main (int argc, char * argv[])
{
	double a = 7.4;
	int b = 99;

	std::cout << "a + b = " <<
		YouTubeDownloadLibrary::YouTubeDownload::Add(a, b) << std::endl;

	std::cin.get();

	return 0;
}