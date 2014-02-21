// YouTubeDownloadLibrary.h

#ifdef YOUTUBEDOWNLOADLIBRARY_EXPORT
#define YOUTUBEDOWNLOADLIBRARY_API __declspec(dllexport)
#else
#define YOUTUBEDOWNLOADLIBRARY_API __declspec(dllimport)
#endif

namespace YouTubeDownloadLibrary
{
	// This class is exported from YouTubeDownloadLibrary.dll
	class YouTubeDownload
	{
	public:
		// Not implimented
		static YOUTUBEDOWNLOADLIBRARY_API
			std::string GetLink (std::string videoID, int encoding[], int size);

		// Not implimented
		static YOUTUBEDOWNLOADLIBRARY_API
			int DownloadToHDD (std::string link, std::fstream file);
	};
}