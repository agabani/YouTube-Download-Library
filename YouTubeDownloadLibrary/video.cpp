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


	bool Video::isValid()
	{
		if (fallback_host.empty() || itag.empty() || quality.empty() || sig.empty() || type.empty() || url.empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
