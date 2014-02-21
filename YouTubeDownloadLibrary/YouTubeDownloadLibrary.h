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
		// Returns a + b
		static YOUTUBEDOWNLOADLIBRARY_API double Add(double a, double b);

		// Returns a - b
		static YOUTUBEDOWNLOADLIBRARY_API double Subtract(double a, double b);

		// Returns a * b
		static YOUTUBEDOWNLOADLIBRARY_API double Multiply(double a, double b);

		// Returns a / b
		static YOUTUBEDOWNLOADLIBRARY_API double Divide(double a, double b);
	};
}