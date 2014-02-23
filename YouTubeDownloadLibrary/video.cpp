/**
 * @file video.cpp
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
 * Class representing the information contained by a video.
 *
 */

#include "stdafx.h"
#include <stdexcept>

#include "YouTubeDownloadLibrary.h"

namespace YouTubeDownloadLibrary
{
	std::string Video::GetURL()
	{
		return url + "&signature=" + sig;
	}


	std::string Video::GetQuality()
	{
		return quality;
	}


	std::string Video::GetType()
	{
		return type;
	}


	int	Video::GetITag()
	{
		std::stringstream ss;
		ss << itag;
		int result;
		ss >> result;
		return result;
	}


	YouTubeDownload::Container Video::GetContainer()
	{
		return container;
	}


	YouTubeDownload::Resolution	Video::GetResolution()
	{
		return resolution;
	}


	bool Video::is3D()
	{
		return _3D;
	}


	bool Video::Validate()
	{
		if (fallback_host.empty() || itag.empty() || quality.empty() || sig.empty() || type.empty() || url.empty())
		{
			return false; // Failure. All required fields is not available.
		}

		// Obtain container, resolution, and 3D
		std::stringstream ss;
		ss << itag;
		int result;
		ss >> result;

		// Identify the video's container.
		switch (result)
		{
			// 3GP
		case 13: case 17: case 36:
			container = YouTubeDownload::Container::_3PG;
			break;

			// FLV
		case 5: case 6: case 34: case 35:
			container = YouTubeDownload::Container::FLV;
			break;

			// MP4
		case 18: case 22: case 37: case 38: case 82: case 83: case 84: case 85:
			container = YouTubeDownload::Container::MP4;
			break;

			// WebM
		case 43: case 44: case 45: case 46: case 100: case 101: case 102:
			container = YouTubeDownload::Container::WEBM;
			break;

		default:
			return false; // Failure. File itag not supported.
			break;
		}

		// Identify the video's resolution.
		switch (result)
		{
			// NA
		case 13:
			resolution = YouTubeDownload::Resolution::NA;
			break;

			// 144p
		case 17:
			resolution = YouTubeDownload::Resolution::_144P;
			break;

			// 240p
		case 5: case 83:
			resolution = YouTubeDownload::Resolution::_240P;
			break;

			// 270/360p
		case 18:
			resolution = YouTubeDownload::Resolution::_270_360P;
			break;

			// 360p
		case 34: case 43: case 82: case 100: case 101:
			resolution = YouTubeDownload::Resolution::_360P;
			break;

			// 480p
		case 35: case 44:
			resolution = YouTubeDownload::Resolution::_480P;
			break;

			// 720p
		case 22: case 45: case 84: case 102:
			resolution = YouTubeDownload::Resolution::_720P;
			break;

			// 1080p
		case 37: case 46: case 85:
			resolution = YouTubeDownload::Resolution::_1080P;
			break;

			// 3072p
		case 38:
			resolution = YouTubeDownload::Resolution::_3072P;
			break;

		default:
			return false; // Failure. File itag not supported.
			break;
		}

		// Identifies if video has 3D properties.
		switch (result)
		{
			// Non 3D
		case 5: case 6: case 13: case 17: case 18: case 22: case 34: case 35:
		case 36: case 37: case 38: case 43: case 44: case 45: case 46:
			_3D = false;
			break;
			
			// 3D
		case 82: case 83: case 84: case 85: case 100: case 101: case 102:
			_3D = true;
			break;

		default:
			return false; // Failure. File itag not supported.
			break;
		}

		return true; // Succuess.

	}
}
