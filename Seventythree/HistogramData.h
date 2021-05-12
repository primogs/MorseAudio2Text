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
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//!  The histogram data class stores the data of the histogram and provide methods to add data and retrieve histogram data.
/*!
  The value (period) is not stored, instead it is directly assigned to a bin. The bin number is stored twice, once 
  in a the ring buffer mHistogram and in the bin buffer mBinBuffer. The ring buffer is used to track the order of the 
  incomming elements. In this way the elements can be removed from the histogram in the same order they come in (FIFO).
  The mBinBuffer is used to store the number of periods (count) that are element of the range regarding a histogram bin. 
  This way a quick access to the counts per bin is possible.   
*/
/**
 * @class HistogramData
 * @author Matthias Hund
 * @date 02/20/21
 * @file HistogramData.h
 */
class HistogramData
{
public:
	HistogramData(unsigned short bins=50, unsigned short length=75,double maxPeriod=0.5);
	virtual ~HistogramData();
	bool IsEnabled();
	void Add(double period);
	void Enable(bool state);
	unsigned short GetBins();
	double	GetMaxPeriod();
	unsigned short GetHistBinCount(unsigned short bin);
private:
	void Init();
	unsigned short GetBin(double period);

	const unsigned short 	mBins;			//!< number of bins the histgram has -> elements of mBinBuffer
	const unsigned short	mBufferSize;	//!< number of elements that are stored at once -> elements in mHistogram
	const double 			mMaxPeriod;		//!< maximal period that evaluated in the histogram
	unsigned short		*	mBinBuffer;		//!< array that stores the counts for each bin
	int						mIndex;			//!< index of the first/last element of the ring buffer mHistogram
	unsigned short		*	mHistogram;		//!< ring buffer to realize the FIFO buffer
	bool					mEnabled;		//!< state of the histogram

};

#endif // HISTOGRAM_H
