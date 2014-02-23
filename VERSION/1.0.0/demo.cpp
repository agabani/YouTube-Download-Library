/**
 * @file demo.cpp
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
 * Example program using YouTube Download Library
 *
 */


// ========== PREREQUISITES ====================================
// LIBRARY WILL NOT WORK UNTIL THIS IS DONE CORRECTLY
// =============================================================

// * Add debug/YouTubeDownloadLibrary.lib to debug linker
// * Add release/YouTubeDownloadLibrary.lib to release linker
// * Copy YouTubeDownloadLibrary.dll to your .exe folder
// * Copy ssleay32.dll to your .exe folder
// * Copy libeay32.dll to your .exe folder


// ========== REQUIRED INCLUDES =================================
// 
// ==============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "YouTubeDownloadLibrary.h"


// ========== MAIN ==============================================
// 
// ==============================================================

int main (int argc, char * argv[])
{
	// ========== STEP 1 ========================================
	// GETTING VIDEO INFORMATION
	// ==========================================================

	// Select video id from YouTube
	// This can be found in the YouTube URL
	// example: https://www.youtube.com/watch?v=-U-hf6go8as
	//		video ID is -U-hf6go8as

	std::string videoID = "-U-hf6go8as";

	
	// Use API to search for video.

	std::vector<YouTubeDownloadLibrary::Video> videos
		= YouTubeDownloadLibrary::YouTubeDownload::GetLink(videoID);

	if (videos.empty()) {
		std::cout << "Video not found." << std::endl
			<< "Check if you are using a valid video id or if you are connected to the internet";
		return -1; // Failure, exit program.
	}

	
	// ========== STEP 2 ========================================
	// SEARCH FOR WANTED VIDEO CONTAINER AND RESOLUTION
	// ==========================================================

	// Search the list of videos you got from the API search function in step 1 to select a video
	// you want to download.
	// 
	// There are 2 methods...
	// 
	// NOTE:
	//		Possible containers: (found in "YouTubeDownloadLibrary.h")
	//			.3pg, .flv, .mp4, .webm
	//		
	//		Possible resolutions: (found in "YouTubeDownloadLibrary.h")
	//			144p, 240p, 270/360p, 360p, 480p, 720p, 1080p, 3072p
	//
	// SIDE NOTE: The resolution NA means resolution unknown. (DOES NOT MEAN CHOOSE ANY RESOLUTION).
	//					avoid using the NA option.
	
	YouTubeDownloadLibrary::Video video;
	int result;

		// ===== METHOD 1 =====
		// Search using exact container and resolution.
		
	result = YouTubeDownloadLibrary::YouTubeDownload::SearchVideo (
		videos,
		YouTubeDownloadLibrary::YouTubeDownload::Container::MP4,
		YouTubeDownloadLibrary::YouTubeDownload::Resolution::_1080P,
		video
		);
	
	if (result != 0) {
		std::cout << "The video format and resolution you have searched for is not available." << std::endl;
	}

		// ===== METHOD 2 =====
		// Search for a exact container, with highest or lowest resolution.
		
	result = YouTubeDownloadLibrary::YouTubeDownload::SearchVideo (
		videos,
		YouTubeDownloadLibrary::YouTubeDownload::Container::MP4,
		true, // Set value as true to get the highest findable resolution for container.
			  // Set false for lowest possible findable resolution.
		video
		);


	if (result < 0) {
		std::cout << "The video container you have searched for is not available" << std::endl;
	}


	// ========== STEP 3 ========================================
	// OPEN A FILE TO SAVE YOUR VIDEO TO
	// ==========================================================

	// Open a file stream.
	std::string filename = "MyDownloadedVideo.mp4";

		// Optional: create a file name based on the video id given at the beginning of program
		// and get the file extention directly from the video file you have searched for.

	switch (video.GetContainer())
		{
		case YouTubeDownloadLibrary::YouTubeDownload::Container::FLV:
			filename = videoID + ".flv";
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::MP4:
			filename = videoID + ".mp4";
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::_3PG:
			filename = videoID + ".3pg";
			break;
		case YouTubeDownloadLibrary::YouTubeDownload::Container::WEBM:
			filename = videoID + ".webm";
			break;
		default:
			return -1; // Extention not found.
			break;
		}

	std::fstream file;
	file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc); // Important: open in binary out mode with trunc.


	// ========== STEP 4 ========================================
	// DOWNLOAD YOUR VIDEO TO FILE
	// ==========================================================

	// Download video to file using API.
	
	int bytesRemaining = YouTubeDownloadLibrary::YouTubeDownload::DownloadToHDD(
							video.GetURL(),
							file,
							true // Set this to true if you want a GUI progress bar showing download progress in console.
						);

	if (bytesRemaining == 0) {
		std::cout << "Download complete." << std::endl;
	} else if (bytesRemaining > 0) {
		std::cout << "Download incomplete, connection was interupted." << std::endl;
	} else {
		std::cout << "Download could not start, can not connect to host." << std::endl;
	}


	// ========== STEP 5 ========================================
	// CLOSE THE FILE YOU DOWNLOADED THE VIDEO TO
	// ==========================================================

	file.close();

	// Exit demo program.
	std::cin.get();

	return 0;
}
