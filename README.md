# YouTube Download Library

## This project is depreciated

Lightweight c++ library for downloading videos directly from YouTube.

Version: 1.0.0 

License: MIT

Files: YouTube-Download-Library / VERSION / 1.0.0

Installation
------------
* Add debug/YouTubeDownloadLibrary.lib to debug linker
* Add release/YouTubeDownloadLibrary.lib to release linker
* Copy YouTubeDownloadLibrary.dll to your .exe folder
* Copy ssleay32.dll to your .exe folder
* Copy libeay32.dll to your .exe folder
* Include YouTubeDownloadLibrary.h

Usage
-----
Download process has been simplified down to 5 easy steps...

1)  Download video information using:    
        std::vector <Video> YouTubeDownload::GetLink (std::string videoID);

2)  Search for wanted video container and resolution using:
        int SearchVideo (std::vector <Video>, Container, Resolution, Video& DownloadLink);
    
    or using just the resolution and selecting either highest or lowest resolution using:
        int YouTubeDownload::SearchVideo (std::vector <Video>, Container, bool HighestResolutionFirst, Video& DownloadLink);

3)  Open a file stream in "binary", "out" and "trunc".
        std::fstream file("myvideo.mp4", std::ios::out | std::ios::binary | std::ios::trunc);

4)  Download video to file stream using:  
        int DownloadToHDD (std::string link, std::fstream& file, bool displayProgress);

5)  Close the file stream.
        file.close();

Tutorial
--------
The tutorial demo.cpp is found in:
        YouTube-Download-Library / VERSION / 1.0.0
	
The tutorial demo.exe is found in:
        YouTube-Download-Library / VERSION / 1.0.0
