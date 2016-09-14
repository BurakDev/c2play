/*
*
* Copyright (C) 2016 OtherCrashOverride@users.noreply.github.com.
* All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2, as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
*/

#pragma once

extern "C"
{
	// aml_lib
#include <codec.h>
}

#include "Mutex.h"
#include "Pin.h"
#include "Rectangle.h"


class AmlCodec
{
	const unsigned long PTS_FREQ = 90000;

	const long EXTERNAL_PTS = (1);
	const long SYNC_OUTSIDE = (2);
	const long USE_IDR_FRAMERATE = 0x04;
	const long UCODE_IP_ONLY_PARAM = 0x08;
	const long MAX_REFER_BUF = 0x10;
	const long ERROR_RECOVERY_MODE_IN = 0x20;

	const char* CODEC_VIDEO_ES_DEVICE = "/dev/amstream_vbuf";
	const char* CODEC_VIDEO_ES_HEVC_DEVICE = "/dev/amstream_hevc";
	const char* CODEC_CNTL_DEVICE = "/dev/amvideo";
	typedef int CODEC_HANDLE;


	//codec_para_t codec = { 0 };
	bool isOpen = false;
	Mutex codecMutex;
	CODEC_HANDLE handle;
	CODEC_HANDLE cntl_handle;
	VideoFormatEnum format;
	int width;
	int height;
	double frameRate;



	void InternalOpen(VideoFormatEnum format, int width, int height, double frameRate);
	void InternalClose();

public:

	bool IsOpen() const
	{
		return isOpen;
	}


	void Open(VideoFormatEnum format, int width, int height, double frameRate);
	void Close();
	void Reset();
	double GetCurrentPts();
	void SetCurrentPts(double value);
	void Pause();
	void Resume();
	buf_status GetBufferStatus();
	bool SendData(unsigned long pts, unsigned char* data, int length);
	void SetVideoAxis(Int32Rectangle rectangle);
	Int32Rectangle GetVideoAxis();
	void SetSyncThreshold(unsigned long pts);

};