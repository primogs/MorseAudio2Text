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
#ifndef GLOBAL_H
#define GLOBAL_H

#include "MorseDecode.h"

#include <mutex>

/**
 * @class Global
 * @author Matthias Hund
 * @date 06/17/20
 * @file Global.h
 * @brief container for data that is accessed from different threads
 */
class Global
{
public:
	Global();
	virtual ~Global();

	static MorseDecode			mMD;			//!< MorseDecode class used to transform the audio signal into a text
	static std::mutex 			mMDMutex;		//!< mutex to coordinate access to mMD
	static bool 				mStopListen;	//!< flag to indicate the listen thread that it should terminate 
	static std::string			mAudioDev;		//!< name of the audio input device that should be used
};

#endif // GLOBAL_H
