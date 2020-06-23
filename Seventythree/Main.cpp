/////////////////////////////////////////////////////////////////////////////////////////
//    This file is part of Seventythree.
//
//    Copyright (C) 2020 Matthias Hund
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

/*! \mainpage Sventythree
 *
 * \section Introduction
 *
 * Sventythree converts a morse signal from a audio stream to a text. The audio stream is recorded with the sound card. A recorded audio file 
 * can be decoded if the soundcard output is conected with the input by a wire. An additional prefilter is maybe required if the audio stream is 
 * very noisy. For more information about the decoding see MorseDecode class.
 *
 * \section Configuration File
 * 
 * A configuration file can be used to parameterize the programm. The configuration must be named "config.txt" and placed in the same folder as 
 * the executable file. Following parameter are supported: MaxMemoryConsumption, AudioInSampleRate, MaxAmplitude, AutoThresholdFactor, 
 * MinThreshold, DotTimeLowerLimit, DotTimeUpperLimit, StableDotTimeInaccuracy, MaxMorseSignsPerChar, DebounceBounceTime, LowPassDecayRate, 
 * AutoThresholdDecayRate, AveTimeBufferLength, ShortTimeBufferLength,StableDotTimeBufferLength, EdgeEventBufferLength, TextBufferLength
 * A parameter is expected as name value pair in a single row eg.
 * AudioInSampleRate 44100
 * The value must be in the base unit, eg. seconds if it is a time. Any line starting with a # will be ignorde.
 *
 * \section Source Code
 * 
 * Sventythree use wxWidgets (version 3.0) for the gui and portaudio (v19) for audio card access. You will need to link against both libaries 
 * to get the full functionality. It is also possible to compile the programm as command line tool reading from stdin.
 * 
 */


#include "Main.h"

// initialize the application
IMPLEMENT_APP(MainApp);


/**
 * @brief application class implementation 
 * @return returns always true
 */
bool MainApp::OnInit()
{
	SetTopWindow( new MainDialog( NULL ) );
	GetTopWindow()->Show();
	
	// true = enter the main loop
	return true;
}

