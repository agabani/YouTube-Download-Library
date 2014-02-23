/**
 * @file YouTubeDownloadLibrary.cpp
 * @author agabani
 * @version 1.0
 *
 * @section LICENCE
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * ==== ABOUT ====
 * YouTube Download Library - Lightweight and simple to use C++ library for the purpose
 * of downloading videos directly from youtube using only the video id.
 * 
 * ==== INSTALLATION ====
 * add this .h to your project
 * add debug/.lib and release/.lib to your compilers linker options
 * add all .dll to the same folder as your .exe 
 *
 * ==== HOW TO USE ====
 * Download process has been abstracted down to 5 easy steps...
 * 
 * 1) Download video information using:    
 *		std::vector <Video> YouTubeDownload::GetLink (std::string videoID);
 *		
 * 2) Search for wanted video container and resolution using   
 *		int SearchVideo (std::vector <Video>, Container, Resolution, Video& DownloadLink);
 *		
 *	  or using just the resolution and selecting either highest or lowest resolution using:
 *		int YouTubeDownload::SearchVideo (std::vector <Video>, Container, bool HighestResolutionFirst, Video& DownloadLink);
 *		
 * 3) Open a file stream in "binary", "out" and "trunc".
 *  
 * 4) Download video to file stream using:  
 *		int DownloadToHDD (std::string link, std::fstream& file, bool displayProgress);
 *
 * 5) Close the file stream.   
 */

#pragma once

#ifdef YOUTUBEDOWNLOADLIBRARY_EXPORT
#define YOUTUBEDOWNLOADLIBRARY_API __declspec(dllexport)
#else
#define YOUTUBEDOWNLOADLIBRARY_API __declspec(dllimport)
#endif

namespace YouTubeDownloadLibrary
{
	/**
	 *	Forward declarations - You can ignore this.
	 */

	class FMT; // INTERNAL ONLY
	class Video;
	class YouTubeDownload;


	/**
	 * @class	YouTubeDownload
	 *
	 * @brief	Contains API for YouTube Download Library.
	 *
	 * @author	agabani
	 * @date	23/02/2014
	 */

	class YouTubeDownload
	{
	public:

		/**
		 * @fn		std::string YouTubeDownload::GetVersion();
		 *
		 * @brief	Gets the library .dll version.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	Library .dll version.
		 */

		static YOUTUBEDOWNLOADLIBRARY_API
			std::string GetVersion();


		/**
		 * @enum	Container
		 *
		 * @brief	List of supported video containers. (.3pg, .flv, .mp4, .webm)
		 */

		enum Container {
			_3PG, FLV, MP4, WEBM
		};

		/**
		 * @enum	Resolution
		 *
		 * @brief	List of supported video resolutions. (144p, 240p, 270/360p, 360p, 480p, 720p, 1080p, 3072p)
		 */

		enum Resolution {
			NA = 0, _144P = 144, _240P = 240, _270_360P = 270, _360P = 360, _480P = 480, _720P = 720, _1080P = 1080, _3072P = 3072
		};


		/**
		 * @fn	std::vector <Video> YouTubeDownload::GetLink (std::string videoID);
		 *
		 * @brief	Obtains a full list of available videos for given video ID.
		 * 			A video ID is value in the "v=" field of a YouTube video url.
		 * 			Example: http://www.youtube.com/watch?v=AaBbCc-DeEe video id is AaBbCc-DeEe
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	videoID	Identifier for the video.
		 *
		 * @return	Video information for all videos found under the same video ID.
		 */

		static YOUTUBEDOWNLOADLIBRARY_API
			std::vector <Video> GetLink (std::string videoID);

		/**
		 * @fn	int YouTubeDownload::SearchVideo (std::vector <Video>, Container, Resolution, Video& DownloadLink);
		 *
		 * @brief	Searches a list of video information for a specific container and resolution.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	std::vector <Video>		List of video information.
		 * @param	Container				Container.
		 * @param	Resolution				Resolution.
		 * @param [out]	DownloadLink		Download link associated with video.
		 *
		 * @return	Returns 0 if video with specified container and resolution was found.
		 */

		static YOUTUBEDOWNLOADLIBRARY_API
			int SearchVideo (std::vector <Video>, Container, Resolution, Video& DownloadLink);

		/**
		 * @fn	int YouTubeDownload::SearchVideo (std::vector <Video>, Container, bool HighestResolutionFirst, Video& DownloadLink);
		 *
		 * @brief	Searches for the first video.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	<Video>				  	List of video information.
		 * @param	Container			  	Container.
		 * @param	HighestResolutionFirst	Set to true if looking for highest possible resolution for video.
		 * 									Set to false if looking for lowest possible resolution for video.
		 * @param [out]	DownloadLink		Download link associated with video.
		 *
		 * @return	Returns -1:			No best match was found.
		 * 			Returns positive:	Index of best video match.
		 */

		static YOUTUBEDOWNLOADLIBRARY_API
			int SearchVideo (std::vector <Video>, Container, bool HighestResolutionFirst, Video& DownloadLink);

		/**
		 * @fn	int YouTubeDownload::DownloadToHDD (std::string link, std::fstream& file, bool displayProgress);
		 *
		 * @brief	Downloads file to target location.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @param	link		   	Address of file.
		 * @param [out]	file	   	Opened storage location of file set to binary write.
		 * @param	displayProgress	True: Display download feedback/progress in console.
		 * 							False: Do not display download feedback/progress in console.
		 *
		 * @return	An int.
		 */

		static YOUTUBEDOWNLOADLIBRARY_API
			int DownloadToHDD (std::string link, std::fstream& file, bool displayProgress);
	};


	/**
	 * @class	Video
	 *
	 * @brief	Storage class of video information.
	 *
	 * @author	agabani
	 * @date	23/02/2014
	 */

	class Video
	{
		friend FMT;

	public:

		/**
		 * @fn		std::string Video::GetURL();
		 *
		 * @brief	Gets the video URL.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	Video URL.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			std::string GetURL();

		/**
		 * @fn		std::string Video::GetQuality();
		 *
		 * @brief	Gets human readable video information.
		 * 			May include video container, codec, bitrate, etc...
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	The quality.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			std::string GetQuality();

		/**
		 * @fn	YOUTUBEDOWNLOADLIBRARY_API std::string Video::GetType();
		 *
		 * @brief	Gets type of the video.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	Video type.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			std::string GetType();

		/**
		 * @fn		int Video::GetITag();
		 *
		 * @brief	Gets the iTag of the video.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	Video iTag.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			int	GetITag();

		/**
		 * @fn		YouTubeDownload::Container Video::GetContainer();
		 *
		 * @brief	Gets the container of the video.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	Video container.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			YouTubeDownload::Container GetContainer();

		/**
		 * @fn	YouTubeDownload::Resolution Video::GetResolution();
		 *
		 * @brief	Gets the resolution of the video.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	Video resolution.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			YouTubeDownload::Resolution	GetResolution();

		/**
		 * @fn	YOUTUBEDOWNLOADLIBRARY_API bool Video::is3D();
		 *
		 * @brief	Gets the 3D status of a video.
		 *
		 * @author	agabani
		 * @date	23/02/2014
		 *
		 * @return	True if 3D.
		 * 			False if 2D.
		 */

		YOUTUBEDOWNLOADLIBRARY_API
			bool is3D();

	private:
		/**
		 * This private area can be ignored - INTERNAL ONLY.
		 */

		bool Validate();

		std::string	fallback_host, itag, quality, sig, type, url;
		YouTubeDownload::Container container;
		YouTubeDownload::Resolution resolution;
		bool _3D;
	};
}
