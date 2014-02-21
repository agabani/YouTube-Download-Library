// YouTubeDownloadLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "YouTubeDownloadLibrary.h"
#include <stdexcept>

using namespace std;

namespace YouTubeDownloadLibrary
{
	double YouTubeDownload::Add(double a, double b)
	{
		return a + b;
	}

	double YouTubeDownload::Subtract(double a, double b)
	{
		return a - b;
	}

	double YouTubeDownload::Multiply(double a, double b)
	{
		return a * b;
	}

	double YouTubeDownload::Divide(double a, double b)
	{
		if (b == 0)
		{
			throw invalid_argument("b cannot be zero!");
		}

		return a / b;
	}
}
