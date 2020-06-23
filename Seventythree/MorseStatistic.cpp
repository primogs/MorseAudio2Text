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
#include "MorseStatistic.h"

using namespace Morse;

/**
 * @brief constructor that initialize the buffer
 * @return 
 */
MorseStatistic::MorseStatistic()
{
	InitBuffer(100);
	mEdgeEventBufferFullCounter = 0;
}

/**
 * @brief destructor that deletes the buffer
 * @return 
 */
MorseStatistic::~MorseStatistic()
{
	DeleteBuffer();
}

/**
 * @brief free the memory used as buffer
 */
void MorseStatistic::DeleteBuffer()
{
	delete[] mMorseSignBuffer;
	delete[] mMorseTimeBuffer;
	mMorseSignBuffer = nullptr;
	mMorseTimeBuffer = nullptr;
}

/**
 * @brief allocate memory for the buffer and initialze it
 * @param bufferSize
 */
void MorseStatistic::InitBuffer(int bufferSize)
{
	mBufferSize = bufferSize;
	mBufferIndex= 0;
	
	mMorseSignBuffer = new MorseSign[mBufferSize];
	mMorseTimeBuffer = new double[mBufferSize];
	
	for(int i=0;i<mBufferSize;i++)
	{
		mMorseSignBuffer[i] = NO_SIGN;
		mMorseTimeBuffer[i] = 0.0;
	}
}

/**
 * @brief delete buffer and create a new one with the desired size
 * @param bufferSize: size of the new buffer
 */
void MorseStatistic::StatSetBufferSize(int bufferSize)
{
	DeleteBuffer();
	InitBuffer(bufferSize);
} 

/**
 * @brief add a sample to the buffer
 * @param sign:	morse sign that is added
 * @param dt: duration that is addef
 */
void MorseStatistic::StatAddSample(MorseSign sign,double dt)
{
	mMorseSignBuffer[mBufferIndex] = sign;
	mMorseTimeBuffer[mBufferIndex] = dt;
	mBufferIndex++;
	if(mBufferIndex>=mBufferSize)
	{
		mBufferIndex=0;
	}
	
}

/**
 * @brief averages the duration for a morse sign
 * @param sign: morse sign for which the average is calculated
 * @return the average duration in seconds of the sign
 */
double 	MorseStatistic::StatGetAverageTime(MorseSign sign)
{
	int count = 0;
	double mean = 0.0;
	for(int i=0;i<mBufferSize;i++)
	{
		if(mMorseSignBuffer[i] == sign)
		{
			count++;
			mean += mMorseTimeBuffer[i];
		}
	}
	mean /= static_cast<double>(count);
	return mean;
}

/**
 * @brief standard deviation for a morse sign
 * @param sign: morse sign for which the standard deviation is calculated
 * @return the standard deviation of the sign
 */
double 	MorseStatistic::StatGetStdDevOfTime(MorseSign sign)
{
	const double aveTime = StatGetAverageTime(sign);
	int count = 0;
	double squareSum = 0.0;
	for(int i=0;i<mBufferSize;i++)
	{
		if(mMorseSignBuffer[i] == sign)
		{
			count++;
			squareSum += (mMorseTimeBuffer[i]-aveTime)*(mMorseTimeBuffer[i]-aveTime);
		}
	}
	squareSum *= 1.0/(static_cast<double>(count)-1.0);
	return std::sqrt(squareSum);
}

/**
 * @brief counts the amount of durations for a sign stored in the buffer 
 * @param sign: morse sign
 * @return durations stored in the buffer
 */
int	MorseStatistic::StatGetCount(MorseSign sign)
{
	int count = 0;
	for(int i=0;i<mBufferSize;i++)
	{
		if(mMorseSignBuffer[i] == sign)
		{
			count++;
		}
	}
	return count;
}

/**
 * @brief increase the edge event buffer full counter
 */
void MorseStatistic::StatEdgeEventBufferFull()
{
	mEdgeEventBufferFullCounter++;
}

/**
 * @brief returns the edge event buffer full counter
 * @return edge event buffer full counter
 */
int	MorseStatistic::StatEdgeEventBufferFullCounter()
{
	return mEdgeEventBufferFullCounter;
}