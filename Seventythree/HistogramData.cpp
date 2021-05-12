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
#include "HistogramData.h"

/**
 * @brief constructor of histogram data that allocates and intialize the memory for the histogram data
 */
HistogramData::HistogramData(unsigned short bins, unsigned short length,double maxPeriod):mBins(bins),mBufferSize(length),mMaxPeriod(maxPeriod)
{
	mEnabled   = true;
	mBinBuffer = new unsigned short[mBufferSize];
	mHistogram = new unsigned short[mBins];
	Init();
}

/**
 * @brief initialize the histogram data. After initialization all counts are in the first bin. 
 */
void HistogramData::Init()
{
	mHistogram[0] = mBufferSize;
	mIndex = 0;
	for(int i=0;i<mBufferSize;i++)
	{
		mBinBuffer[i] = 0;
	}
	for(int i=1;i<mBins;i++)
	{
		mHistogram[i] = 0;
	}
}

/**
 * @brief destructor that will free the histogram data
 */
HistogramData::~HistogramData()
{
	delete[] mBinBuffer;
	delete[] mHistogram;
	mBinBuffer	= nullptr;
	mHistogram	= nullptr;
}

/**
 * @brief add the period and remove the oldest period from the histogram if enabled 
 * @param period: period in seconds
 */
void HistogramData::Add(double period)
{
	if(mEnabled)
	{
		const unsigned short newBin = GetBin(period);
		mBinBuffer[mIndex] = newBin;
		mHistogram[newBin]=mHistogram[newBin]+1;
		mIndex++;
		if(mIndex>=mBufferSize)
			mIndex = 0;
		const unsigned short oldBin = mBinBuffer[mIndex];
		mHistogram[oldBin]=mHistogram[oldBin]-1;
	}
}

/**
 * @brief return the state of the histogram 
 * @return true if the histogram is enabled, otherwise false
 */
bool HistogramData::IsEnabled()
{
	return mEnabled;
}

/**
 * @brief set the state of the histogram 
 * @param state: enables the histogram if true and disables the histogram if false
 */
void HistogramData::Enable(bool state)
{
	mEnabled = state;
	if(mEnabled)
		Init();
}

/**
 * @brief determines the bin number
 * @param period: period in seconds
 * @return the bin number the period belongs to. return zero if the period is out of the histogram range
 */
unsigned short HistogramData::GetBin(double period)
{
	unsigned short result = 0;
	if(period<mMaxPeriod)
	{
		result = (mBins*period)/mMaxPeriod;
	}
	return result;
}

/**
 * @brief to get the counts in a bin 
 * @param bin: the number of the bin
 * @return the counts of the histogram bin or zero if the histogram is disabled or the bin number is invalid
 */
unsigned short HistogramData::GetHistBinCount(unsigned short bin)
{
	if(bin>=mBins or mEnabled==false)
		return 0;
	return mHistogram[bin];
}

/**
 * @brief number of histogram bins 
 * @return number of bins
 */
unsigned short HistogramData::GetBins()
{
	return mBins;
}

double	HistogramData::GetMaxPeriod()
{
	return mMaxPeriod;
}