// fmt.h
#pragma once

#include "YouTubeDownloadLibrary.h"

namespace YouTubeDownloadLibrary
{
	class FMT
	{
	public:
		FMT();
		~FMT();

		static std::string ExtractFMT (std::string feed);
		static std::vector <YouTubeDownloadLibrary::Video> ParseFMT (std::string serial);
	};
}