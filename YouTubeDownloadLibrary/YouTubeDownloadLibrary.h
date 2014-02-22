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
		enum Container {
			_3PG, FLV, MP4, WEBM
		};
		enum Resolution {
			NA = 0, _144P = 144, _240P = 240, _270_360P = 270, _360P = 360, _480P = 480, _720P = 720, _1080P = 1080, _3072P = 3072
		};


		// Obtains the full lists of videos available from video id
		static YOUTUBEDOWNLOADLIBRARY_API
			std::vector <Video> GetLink (std::string videoID);

		// Search through and return video of choice.
		static YOUTUBEDOWNLOADLIBRARY_API
			int SearchVideo (std::vector <Video>, Container, Resolution, Video& DownloadLink);
		static YOUTUBEDOWNLOADLIBRARY_API
			int SearchVideo (std::vector <Video>, Container, bool HighestResolutionFirst, Video& DownloadLink);

		// Not implimented
		static YOUTUBEDOWNLOADLIBRARY_API
			int DownloadToHDD (std::string link, std::fstream& file, bool displayProgress);
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

		YOUTUBEDOWNLOADLIBRARY_API
			YouTubeDownload::Container GetContainer();

		YOUTUBEDOWNLOADLIBRARY_API
			YouTubeDownload::Resolution	GetResolution();

		YOUTUBEDOWNLOADLIBRARY_API
			bool is3D();

	private:
		bool Validate();

		std::string	fallback_host, itag, quality, sig, type, url;
		YouTubeDownload::Container container;
		YouTubeDownload::Resolution resolution;
		bool _3D;
	};
}
