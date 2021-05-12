/////////////////////////////////////////////////////////////////////////////////////////
//    This file is part of Seventythree.
//
//    Copyright (C) 2020 - 2021 Matthias Hund
//    
//    This program is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 2
//    of the License, or (at your option) any later version.
//    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//    
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
/////////////////////////////////////////////////////////////////////////////////////////
#include "Global.h"
#include "Audio.h"
#include <wx/log.h>

/**
 * @brief reads data from the audio input and feeds the data to the MorseDecode instance
 */
void RunListenThread()
{
	PaStreamParameters  inputParameters;
	PaStream*           stream 		= nullptr;
	const PaDeviceInfo* deviceInfo 	= nullptr;
	
	PaError err = Pa_Initialize();
    if( err != paNoError )
	{
		wxLogDebug("PortAudio: Init error");
		return;
	}
	
	inputParameters.device = paNoDevice;
	int numDevices = Pa_GetDeviceCount();
	for( int i=0; i<numDevices and inputParameters.device==paNoDevice; i++ )
	{
		deviceInfo = Pa_GetDeviceInfo( i );
		if(Global::mAudioDev.compare(deviceInfo->name) == 0 and deviceInfo!=nullptr)
		{
			inputParameters.device = i;
		}
	}
	
    if (inputParameters.device == paNoDevice) 
	{
        wxLogDebug("PortAudio: device not available.");
		Pa_Terminate();
		return;
    }
	
    inputParameters.channelCount 				= 1;                    /* mono input */
    inputParameters.sampleFormat 				= paFloat32;				//PA_SAMPLE_TYPE
    inputParameters.suggestedLatency 			= deviceInfo->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo 	= NULL;

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                 // &outputParameters
              Global::mMD.GetAudioInSampleRate(),				//SAMPLE_RATE
              0,					//FRAMES_PER_BUFFER
              paNoFlag,      		// we won't output out of range samples so don't bother clipping them
              NULL,					// callback function
              NULL );
    if( err != paNoError )
	{
		wxLogDebug("PortAudio: OpenStream error");
		Pa_Terminate();
		return;
	}

    err = Pa_StartStream( stream );
    if( err != paNoError ) 
	{
		wxLogDebug("PortAudio: StartStream error");
		Pa_Terminate();
		return;
	}

	
	const int bufferSize = 1024;
	float sampleBuffer[bufferSize];
    while (!Global::mStopListen and ( err = Pa_IsStreamActive( stream ) ) == 1 )
    {
		Pa_ReadStream(stream,sampleBuffer,bufferSize);
		Global::mMDMutex.lock();
		for(int i=0;i<bufferSize;i++)
		{
			Global::mMD.Process(static_cast<double>(sampleBuffer[i]));
		}
		Global::mMDMutex.unlock();
    }
	if( err < 0 )
	{
		wxLogDebug("PortAudio: Stream error");
	}

    err = Pa_CloseStream( stream );
    if( err != paNoError )
	{
		wxLogDebug("PortAudio: Pa_CloseStream error");
	}
	err = Pa_Terminate();
	if( err != paNoError )
	{
		wxLogDebug("PortAudio: Pa_Terminate error");
	}
}

/**
 * @brief searches for audio input devices
 * @param strArray: array of audio device names that where found
 * @return index of the default input device in the strArray 
 */
int GetInputDevices(wxArrayString &strArray)
{
	const   PaDeviceInfo *deviceInfo;	// check which audio interfaces are available
	int res = -1;
	Pa_Initialize();
	PaDeviceIndex defaultIn = Pa_GetDefaultInputDevice();
	int numDevices 			= Pa_GetDeviceCount();
	int defCount = 0;
	for( int i=0; i<numDevices; i++ )
	{
		deviceInfo = Pa_GetDeviceInfo( i );
		if(deviceInfo->maxInputChannels>0)
		{
			strArray.Add(deviceInfo->name);
			if(defaultIn==i)
			{
				res=defCount;
			}
			defCount++;
		}
	}
	
	Pa_Terminate();
	return res;
}