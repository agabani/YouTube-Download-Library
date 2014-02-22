// YouTubeDownloadLibrary.h
#pragma once

#ifdef YOUTUBEDOWNLOADLIBRARY_EXPORT
#define YOUTUBEDOWNLOADLIBRARY_API __declspec(dllexport)
#else
#define YOUTUBEDOWNLOADLIBRARY_API __declspec(dllimport)
#endif

#include <vector>

namespace YouTubeDownloadLibrary
{
	// Forward declarations
	class FMT;
	class Video;
	class YouTubeDownload;
	

	// This class is exported from YouTubeDownloadLibrary.dll
	class YouTubeDownload
	{
	public:
		// Not implimented
		static YOUTUBEDOWNLOADLIBRARY_API
			std::vector <Video> GetLink (std::string videoID);

		// Not implimented
		static YOUTUBEDOWNLOADLIBRARY_API
			int DownloadToHDD (std::string link, std::fstream file);
	};


	// This class contains video information
	class Video
	{
		friend FMT;

	public:
		YOUTUBEDOWNLOADLIBRARY_API
			std::string GetURL();

		YOUTUBEDOWNLOADLIBRARY_API
			std::string GetQuality();

		YOUTUBEDOWNLOADLIBRARY_API
			std::string GetType();

		YOUTUBEDOWNLOADLIBRARY_API
			int	GetITag();

	private:
		bool isValid();

		std::string	fallback_host, itag, quality, sig, type, url;
	};
}
