// video.cpp : Defines the functions for Video class.
//

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
			return false;
		}

		// Obtain container, resolution, and 3D
		std::stringstream ss;
		ss << itag;
		int result;
		ss >> result;

		// Container
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
			return false;
			break;
		}

		// Resolution
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
			return false;
			break;
		}

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
			return false;
			break;
		}

		return true;

	}
}
