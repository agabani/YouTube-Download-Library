// http.h
#pragma once

namespace YouTubeDownloadLibrary
{
	class HTTP
	{
	public:
		HTTP();
		~HTTP();

		// Creates get request
		static int CreateGetRequest (std::string host, std::string uri, std::string& result);

		// Does full http exchange
		static int Exchange (std::string address, std::string request, std::string &response);

		// Decodes url encoding
		static std::string UrlDecode (std::string url);

		// 
		static int DownloadFile (std::string address, std::fstream& file, bool displayProgress);

	private:
		static const int MaxBufSize;
		static const std::string UserAgent;
		static const std::string NewLine;
	};
}
