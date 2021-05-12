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
#ifndef MORSESTATISTIC_H
#define MORSESTATISTIC_H

#include <cmath>
#include "MorseDataTypes.h"
#include "HistogramData.h"

//!  The morse statistic class collects data from the decode process.
/**
 * @class MorseStatistic
 * @author Matthias Hund
 * @date 05/25/20
 * @file MorseStatistic.h
 */
class MorseStatistic
{
public:
	MorseStatistic();
	virtual ~MorseStatistic();
	
	void 	StatSetBufferSize(int bufferSize); 
	
	double 	StatGetAverageTime(Morse::MorseSign sign);
	double 	StatGetStdDevOfTime(Morse::MorseSign sign);
	int		StatGetCount(Morse::MorseSign sign);
	int		StatEdgeEventBufferFullCounter();
	void 	AddPeriodToHistogram(double period,Morse::EdgeState state);
	void	EvaluateToneInHistogram(bool care);
	void	EvaluatePauseInHistogram(bool care);
	bool 	IsToneEvaluatedInHistogram();
	bool 	IsPauseEvaluatedInHistogram();

	unsigned short GetNumberOfBins();
	double 		   GetMaxPeriod();
	unsigned short GetHistToneBinCount(unsigned short bin);
	unsigned short GetHistPauseBinCount(unsigned short bin);
	
protected:
	void 	StatAddSample(Morse::MorseSign sign,double dt);
	void	StatEdgeEventBufferFull();
private:
	void 	DeleteBuffer();
	void 	InitBuffer(int bufferSize);
	

	Morse::MorseSign 	* 	mMorseSignBuffer;				//!< buffer to store last morse signs
	double 				* 	mMorseTimeBuffer;				//!< buffer to store duration of the morse signs
	int						mBufferSize;					//!< size of the buffers
	int						mBufferIndex;					//!< index of the buffer element that will be written next
	int						mEdgeEventBufferFullCounter;	//!< counts how often the edge event buffer overflowed
	HistogramData			mHistTone;						//!< instance of the histogram data class containing the tone histogram
	HistogramData			mHistPause;						//!< instance of the histogram data class containing the pause histogram
};

#endif // MORSESTATISTIC_H
