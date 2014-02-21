// YouTubeDownloadLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "YouTubeDownloadLibrary.h"
#include <stdexcept>

// OpenSSl Library
#include <openssl\bio.h>
#include <openssl\ssl.h>
#include <openssl\err.h>

namespace YouTubeDownloadLibrary
{
	std::string YouTubeDownload::GetLink(std::string, int encode[], int size)
	{
		return std::string();
	}

	int YouTubeDownload::DownloadToHDD (std::string link, std::fstream file)
	{
		return 0;
	}
}
