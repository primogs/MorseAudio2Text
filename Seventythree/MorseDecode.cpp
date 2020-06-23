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
#include "MorseDecode.h"
#include "MorseCodeLookupTable.h"

using namespace Morse;

 /**
  * @brief allocates memory for the buffers and initialized variables
  * @param samplesPerSecond: sample rate of the audio signal
  * @param initDotTime: initialization value of the duration of a dot
  */
MorseDecode::MorseDecode(int samplesPerSecond,double initDotTime): 
	mSamplesPerSecond(		samplesPerSecond),
	mRoundTimeLevel{		0.0,1.0,3.0,7.0},
	mInitDotTime(			initDotTime)
{
	mCharacter 					= nullptr;
	mDebounceBuffer				= nullptr;
	mLowPassFilterBuffer		= nullptr;
	mTimeAveBuffer				= nullptr;
	mShrtTimeBuffer				= nullptr;
	mStableDotTimeBuffer		= nullptr;
	mEdgeEventPeriodBuffer		= nullptr;
	mEdgeEventStateBuffer		= nullptr;
	mTextBuffer 				= nullptr;
	SetMaxMemoryConsumption(1073741824); // 1 GiB
	Reset();
}

/**
 * @brief destructor
 */
MorseDecode::~MorseDecode()
{
	FreeMemory();
}

/**
 * @brief free the memory
 */
void MorseDecode::FreeMemory()
{
	if(mLowPassFilterBuffer != nullptr)
	{
		delete[] mLowPassFilterBuffer;
		mLowPassFilterBuffer = nullptr;
	}
	if(mDebounceBuffer != nullptr)
	{
		delete[] mDebounceBuffer;
		mDebounceBuffer = nullptr;
	}
	if(mTimeAveBuffer != nullptr)
	{
		delete[] mTimeAveBuffer;
		mTimeAveBuffer = nullptr;
	}
	if(mShrtTimeBuffer != nullptr)
	{
		delete[] mShrtTimeBuffer;
		mShrtTimeBuffer = nullptr;
	}
	if(mEdgeEventPeriodBuffer != nullptr)
	{
		delete[] mEdgeEventPeriodBuffer;
		mEdgeEventPeriodBuffer = nullptr;
	}
	if(mEdgeEventStateBuffer != nullptr)
	{
		delete[] mEdgeEventStateBuffer;
		mEdgeEventStateBuffer = nullptr;
	}
	if(mStableDotTimeBuffer != nullptr)
	{
		delete[] mStableDotTimeBuffer;
		mStableDotTimeBuffer = nullptr;
	}
	if(mTextBuffer != nullptr)
	{
		delete[] mTextBuffer;
		mTextBuffer = nullptr;
	}
}

/**
 * @brief reset all variables to default values
 */
void MorseDecode::Reset()
{
	mDebounceBufferLength		= 0;	// set all buffer lengths to zero otherwise memory consumption count does not work
	mLowPassFilterLength		= 0;
	mTimeAveBufferLength		= 0;
	mShrtTimeBufferLength		= 0;
	mStableDotTimeBufferLength	= 0;
	mEdgeEventBufferLength		= 0;
	mTextBufferLength			= 0;
	FreeMemory();
	
	mMemoryConsumption			= 0;
	mMemoryExceeded 			= false;
	mEdge 						= NONE;
	mSign 						= UNKOWN_SIGN;
	mRelevantSign				= UNKOWN_SIGN;
	memset(mGetCharStr,0,sizeof(mGetCharStr));
	mAmplitude 					= 0.0;
	mEnvelope 					= 0.0;
	mThreshold 					= 0.0;
	mDt 						= 0.0;
	mThreshold 					= 0.0;
	mEdgeTriggerLastState 		= UNKOWN;
	mTimerDigitalTime 			= 0;
	mTimerStartTime 			= 0;
	mDotTime 					= mInitDotTime;
	
	SetMaxAmplitude(1.0);
	SetLowPassDecayRate(400.0);
	SetAutoThresholdDecayRate(0.25);
	SetAutoThresholdFactor(0.5);		//50 %
	SetMinThreshold(0.01);
	SetDebounceBounceTime(0.01);
	SetAveTimeBufferLength(16);
	SetShortTimeBufferLength(8);
	SetStableDotTimeBufferLength(16);
	SetDotTimeLowerLimit(0.0134); 		// ~ 90 WPM
	SetDotTimeUpperLimit(1.0);
	SetStableDotTimeInaccuracy(0.2); 	// 20 %
	SetEdgeEventBufferLength(32);
	SetMaxMorseSignsPerChar(16);
	SetTextBufferLength(0);
}

/**
 * @brief normalize the signal regarding mMaxAmplitude and takes compute the absoulut value
 * @param signal: a value from the audio input stream
 * @return the normalized amplitude
 */
inline double MorseDecode::NormalizedAmplitude(double signal)
{
	if(signal>mMaxAmplitude)
		return mMaxAmplitude;
	else
		return std::abs(signal/mMaxAmplitude);
}

/**
 * @brief low pass filter for the normalized amplitude to get the envelope of the signal
 * @param newSample: new normalized amplitude value
 * @return low pass fitered amplitude
 */
double MorseDecode::Lowpass(double newSample)
{
	mLowPassfIndex++;
	if(mLowPassfIndex >= mLowPassFilterLength)
	{
		mLowPassfIndex = 0;
	}
	mLowPassFilterBuffer[mLowPassfIndex] = newSample;
	double sum = 0.0;
	for(int i=0;i<mLowPassFilterLength;i++)
	{
		sum += mLowPassFilterBuffer[i];
		mLowPassFilterBuffer[i] *= mLowpassDamping;
	}
	sum /= mLowPassFilterLength;
	return sum;
}

/**
 * @brief Determines a threshold that is about half of the tone amplitude. The threshold is lowered with time and increased if the envelope is more than twice the threshold.
 * @param envelope: a value of the signal envelope
 * @return the threshold value 
 */
double MorseDecode::AutomaticThreshold(double envelope)
{	
	envelope *= mAutoThresholdFactor;
	if(envelope>mThreshold)
	{
		mThreshold = envelope;
	}
	else
	{
		mThreshold *=mAutoThresholdDamping;
	}
	if(mThreshold<mAutoThresholdMinThreshold)
	{
		mThreshold = mAutoThresholdMinThreshold;
	}
	return mThreshold;
}

/**
 * @brief simple edge trigger
 * @param input: input value from the stream
 * @param threshold: threshold the input is compared with
 * @return the edge state:
 * 		   - RISING if the input was below the threshold and no is above the threshold
 * 		   - FALLING if the input was above the threshold and no is below the threshold
 * 		   - NONE otherwise
 */
EdgeState MorseDecode::EdgeTrigger(double input, double threshold)
{
	if(input>threshold and (mEdgeTriggerLastState==LOW or mEdgeTriggerLastState==UNKOWN))
	{
		mEdgeTriggerLastState = HIGH;
		return RISING;
	}
	else if(input<threshold and (mEdgeTriggerLastState==HIGH or mEdgeTriggerLastState==UNKOWN))
	{
		mEdgeTriggerLastState = LOW;
		return FALLING;
	}
	return NONE;
}

/**
 * @brief Debounce the edge state to avoid misinterpretation. The new edge state is stored for some time (lockout time) in a FIFO buffer.
 *		  The number of RISING and FALLING states is counted if the element at the FIFO end is not NONE. The state with the most counts 
 * 		  is returned and the FIFO reseted. Note: Normaly only one not NONE state should be in the buffer at a time. 
 * @param state: new edge state
 * @return debounced edge state
 */
EdgeState MorseDecode::Debounce(EdgeState state)
{	
	mDebouncBufferIdxFront++;
	if(mDebouncBufferIdxFront >= mDebounceBufferLength)
	{
		mDebouncBufferIdxFront = 0;
	}
	mDebouncBufferIdxEnd++;
	if(mDebouncBufferIdxEnd >= mDebounceBufferLength)
	{
		mDebouncBufferIdxEnd = 0;
	}
	
	mDebounceBuffer[mDebouncBufferIdxFront]= state;
	
	if(mDebounceBuffer[mDebouncBufferIdxEnd] != NONE)
	{
		int count = 0;
		for(int i=0;i<mDebounceBufferLength;i++)
		{
			if(mDebounceBuffer[i] == RISING)
			{
				count++;
				mDebounceBuffer[i] = NONE;
			}
			else if(mDebounceBuffer[i] == FALLING)
			{
				count--;
				mDebounceBuffer[i] = NONE;
			}
		}
		if(count>0)
		{
			return RISING;
		}
		else if(count<0)
		{
			return FALLING;
		}
	}
	return NONE;
}

/**
 * @brief count time between two edge events (not NONE states)
 * @param state: edge state
 * @return elapsed time between the last two edge events in seconds
 */
double MorseDecode::TimeGap(EdgeState state)
{
	mTimerDigitalTime++;
	if(state != NONE)
	{
		const double deltaTime = static_cast<double>(mTimerDigitalTime-mTimerStartTime);
		mDt = deltaTime/mSamplesPerSecond;
		mTimerStartTime = mTimerDigitalTime = 0;
	}
	return mDt;
}

/**
 * @brief determines a distinction level between two time spaces 
 * @param lLevel: short time
 * @param hLevel: long time
 * @return time between the short time and the long time 
 */
inline double MorseDecode::DistinctionLevel(double lLevel,double hLevel)
{
	return lLevel+(hLevel-lLevel)*0.5;
}

/**
 * @brief round the timeRatio to a integer to compensate impropper timing and simplify further processing
 * @param timeRatio: ratio between two edge events and dot time.
 * @return rounded time ratio
 */
int MorseDecode::RoundTime(double timeRatio)
{
	unsigned int i 			= 1;
	while(i< sizeof(mRoundTimeLevel)/sizeof(double) and DistinctionLevel(mRoundTimeLevel[i-1],mRoundTimeLevel[i])<timeRatio)
	{
		i++;
	}
	
	int res = 0;
	switch(i)
	{
		case 2:
			res = 1;
			break;
		case 3:
			res = 3;
			break;
		case 4:
			res = 7;
			break;
	}
	return res;
}

/**
 * @brief moving average filter for the dot time 
 * @param newTime: new time to add
 * @return the average time
 */
double MorseDecode::TimeAverage(double newTime)
{
	
	mTimeAveBuffer[mTimeAveIndex]=newTime;
	
	mTimeAveIndex++;
	if(mTimeAveIndex >= mTimeAveBufferLength)
		mTimeAveIndex=0;
		
	if(mTimeAveFillLevel<mTimeAveBufferLength)
		mTimeAveFillLevel++;
	
	double sum = 0.0;
	for(int i=0;i<mTimeAveBufferLength and i<mTimeAveFillLevel;i++)
	{
		sum += mTimeAveBuffer[i];
	}
	sum /= mTimeAveFillLevel;
	return sum;
}

/**
 * @brief deterimes shortest time in a intervall 
 * @param newTime: new time to add 
 * @return shortest time that is in the buffer
 */
double MorseDecode::TimeShortest(double newTime)
{
	mShrtTimeBuffer[mShrtTimeIndex]=newTime;
	
	mShrtTimeIndex++;
	if(mShrtTimeIndex >= mShrtTimeBufferLength)
		mShrtTimeIndex=0;
		
	if(mShrtTimeFillLevel<mShrtTimeBufferLength)
		mShrtTimeFillLevel++;
	
	double lowest = newTime;
	for(int i=1;i<mShrtTimeBufferLength and i<mShrtTimeFillLevel;i++)
	{
		if(lowest>mShrtTimeBuffer[i])
			lowest=mShrtTimeBuffer[i];
	}
	return lowest;
}

/**
 * @brief Determines the dot time. The shorteste time period that appered in the recent past is determined and average filtered. The dot time 
 *  	  is limited to a reasonable range.  
 * @param period: time between last two edge events
 * @return time in second used for a dot
 */
double MorseDecode::DetectDotTime(double period)
{
	double ds = TimeShortest(period);
	mDotTime = TimeAverage(ds);
	
	if(mDotTime<mDotTimeLowerLimit)
	{
		mDotTime = mDotTimeLowerLimit;
	}
	else if(mDotTime>mDotTimeUpperLimit)
	{
		mDotTime = mDotTimeUpperLimit;
	}

	return mDotTime;
}

/**
 * @brief find the morse sign that fit best 
 * @param dotTime: time period of a dot
 * @param edge: last edge state that was detected
 * @param period: time period between the to last edge states
 * @return morse sign that was detected or UNKOWN_SIGN
 */
MorseSign MorseDecode::GetMorseSign(double dotTime,EdgeState edge,double period)
{
	MorseSign Sign 		= UNKOWN_SIGN;
	double TimeRatio 	= period/dotTime;
	int iTimeRatio		= RoundTime(TimeRatio);
	
	if(edge==RISING)
	{
		if(iTimeRatio == 1)
		{
			Sign = SPACE;
		}
		else if (iTimeRatio == 3)
		{
			Sign = SPACE_CHAR;
		}
		else if (iTimeRatio == 7)
		{
			Sign = SPACE_WORD;
		}
		
	}
	else if(edge==FALLING)
	{
		if(iTimeRatio == 1)
		{
			Sign = DOT;
		}
		else if (iTimeRatio == 3)
		{
			Sign = DASH;
		}
	}
	return Sign;
}

/**
 * @brief checks if dot time varies only a little
 * @param dotTime: time period of a dot
 * @return true if dot time varies only a litte, otherwise false is returned
 */
bool MorseDecode::IsDotTimeStable(double dotTime)
{
	mStableDotTimeBuffer[mStableDotTimeIndex]=dotTime;
	mStableDotTimeIndex++;
	if(mStableDotTimeIndex >= mStableDotTimeBufferLength)
	{
		mStableDotTimeIndex=0;
	}
	double min = mStableDotTimeBuffer[0];
	double max = mStableDotTimeBuffer[0];
	for(int i=1;i<mStableDotTimeBufferLength;i++)
	{
		if(mStableDotTimeBuffer[i]<min)
			min = mStableDotTimeBuffer[i];
		if(mStableDotTimeBuffer[i]>max)
			max = mStableDotTimeBuffer[i];
	}
	if(((max-min)/max)<mStableDotTimeInaccuracy)
	{
		return true;
	}
	return false;
	
}

/**
 * @brief Saves edge state and time period in a buffer and calls GetMorseSign() to get the a Morse sign if dot time is stable. 
 * @param edge: a new edge state
 * @param period: time period between the to last edge states
 * @return a morse sign if detected and NO_SIGN otherwise
 */
MorseSign MorseDecode::EdgeEvent(EdgeState edge,double period)
{	
	if(edge != NONE)
	{
		double dotTime        = DetectDotTime(period);
		mEdgeEventDotTimeValid = IsDotTimeStable(dotTime);
		
		mEdgeEventPeriodBuffer[mEdgeEventIdxFill]=period;
		mEdgeEventStateBuffer[mEdgeEventIdxFill]=edge;
		mEdgeEventIdxFill++;
		if(mEdgeEventIdxFill>=mEdgeEventBufferLength)
			mEdgeEventIdxFill=0;
		mEdgeEventFillLevel++;
		if(mEdgeEventFillLevel==mEdgeEventBufferLength)
		{
			mEdgeEventDotTimeValid = true; // buffer is full, so we must empty it
			MorseStatistic::StatEdgeEventBufferFull();
		}
	}
	
	if(mEdgeEventDotTimeValid and mEdgeEventFillLevel>0)
	{
		MorseSign Sign = GetMorseSign(mDotTime,mEdgeEventStateBuffer[mEdgeEventIdxEmpty],mEdgeEventPeriodBuffer[mEdgeEventIdxEmpty]);
		MorseStatistic::StatAddSample(Sign,mEdgeEventPeriodBuffer[mEdgeEventIdxEmpty]);
		mEdgeEventIdxEmpty++;
		if(mEdgeEventIdxEmpty>=mEdgeEventBufferLength)
			mEdgeEventIdxEmpty=0;
		mEdgeEventFillLevel--;
		return Sign;
	}
	else
	{
		return NO_SIGN;
	}
}

/**
 * @brief find array index of a dot/dash sequence
 * @param sequence: a binary sequence of dot and dashes to search for
 * @param signSequences: array to search for the sequence
 * @param nSequences: number of elements in the signSequences array
 * @return the index of the sequence in the signSequences array or -1 if sequence was not found
 */
int MorseDecode::GetIndex(const uint16_t sequence,const uint16_t *signSequences,uint32_t nSequences)
{
	int index = -1;
	for(unsigned int i=0;i < nSequences;i++)
	{
		if(signSequences[i]==sequence)
		{
			index = i;
			break;
		}
	}
	return index;
}

/**
 * @brief lookup the character that correspond to a dot/dash sequence 
 * @param sequence:	a binary dot/dash sequence
 * @param nSequenceLength: number of dots/dashes int the sequence
 * @return the character that correspond ti the sequence or a empty string if sequence is unkown
 */
const char* MorseDecode::DecodeCharacter(uint16_t sequence,int nSequenceLength)
{
	const char * res = "";
	switch(nSequenceLength)
	{
		case 1:
		{
			sequence &= 0b1;
			res = Sign_1[sequence];
		}
		break;
		case 2:
		{
			sequence &= 0b11;
			res = Sign_2[sequence];
		}
		break;
		case 3:
		{
			sequence &= 0b111;
			res = Sign_3[sequence];
		}
		break;
		case 4:
		{
			sequence &= 0b1111;
			res = Sign_4[sequence];
		}
		break;
		case 5:
		{
			int idx = GetIndex(sequence,SignSequence_5,sizeof(SignSequence_5)/sizeof(uint16_t));
			if(idx != -1)
			{
				res = Sign_5[idx];
			}
		}
		break;
		case 6:
		{
			int idx = GetIndex(sequence,SignSequence_6,sizeof(SignSequence_6)/sizeof(uint16_t));
			if(idx != -1)
			{
				res = Sign_6[idx];
			}
		}
		break;
		case 7:
		{
			int idx = GetIndex(sequence,SignSequence_7,sizeof(SignSequence_7)/sizeof(uint16_t));
			if(idx != -1)
			{
				res = Sign_7[idx];
			}
		}
		break;
		case 8:
		{
			int idx = GetIndex(sequence,SignSequence_8,sizeof(SignSequence_8)/sizeof(uint16_t));
			if(idx != -1)
			{
				res = Sign_8[idx];
			}
		}
		break;
		default:
		break;
	}
	return res;
}

/**
 * @brief Get a character from a stream of morse signs. The morse signs are collected util a new character begins. 
 * 		  The character is looked up if all morse signs of it are recived.
 * @param sign: new morse sign to process
 * @return sting to a recived character or a null pointer no new character available 
 */
const char* MorseDecode::GetCharacter(MorseSign sign)
{	
	if(mGetCharBufferIndex >= mGetCharMaxSign)
	{
		mGetCharBufferIndex = mGetCharBuffer = 0;
	}
	
	const char * res = nullptr;
	switch(sign)
	{
		case DOT:
		{
			mGetCharBuffer = mGetCharBuffer<<1;	// dot = 0
			mGetCharBufferIndex++;
			mRelevantSign = sign;
		}
		break;
		case DASH:
		{
			mGetCharBuffer = mGetCharBuffer<<1;
			mGetCharBuffer = mGetCharBuffer | 1;	// dash = 1
			mGetCharBufferIndex++;
			mRelevantSign = sign;
		}
		break;
		case NO_SIGN:
		case SPACE:
		{
		}
		break;
		case FLUSH:
		case SPACE_CHAR:
		{
			res = DecodeCharacter(mGetCharBuffer,mGetCharBufferIndex);
			mGetCharBufferIndex = mGetCharBuffer = 0;
			mRelevantSign = sign;
		}
		break;
		case SPACE_WORD:
		{
			res = DecodeCharacter(mGetCharBuffer,mGetCharBufferIndex);
			uint32_t charLength = strlen(res);
			if(charLength>2)
				charLength = 2;
			strncpy(mGetCharStr,res,charLength);
			mGetCharStr[charLength] = ' ';				// append space to the character
			mGetCharStr[charLength+1] = '\0';
			res = mGetCharStr;
			mGetCharBufferIndex = mGetCharBuffer = 0;
			mRelevantSign = sign;
		}
		break;
		default:
		{
			mGetCharBufferIndex = mGetCharBuffer = 0;
		}
		break;
	}
	AppendToTxtBuffer(res);
	
	return res;
}

/**
 * @brief process a new value of the audio input stream nad return characters that are morsed
 * @param signal: value of the audio stream
 * @return morsed characters
 */
const char* MorseDecode::Process(double signal)
{
	mAmplitude 		= NormalizedAmplitude(signal);
	mEnvelope 		= Lowpass(mAmplitude);
	double threshold= AutomaticThreshold(mEnvelope);
	mEdge 			= EdgeTrigger(mEnvelope,threshold);
	mEdge 			= Debounce(mEdge);
	double dt		= TimeGap(mEdge);
	mSign 			= EdgeEvent(mEdge,dt);
	mCharacter 		= GetCharacter(mSign);
	return mCharacter;
}

/**
 * @brief append a character to the text buffer that stores the decoded text temporary
 * @param character to append
 */
void MorseDecode::AppendToTxtBuffer(const char * character)
{
	if(character != nullptr and mTextBuffer != nullptr)
	{
		int length = strlen(character);
		if(mTextBufferLength-mTextBufferIndex >= length)
		{
			strncpy(&mTextBuffer[mTextBufferIndex],character,length);
			mTextBufferIndex += length;
		}
	}
}

/**
 * @brief returns the number of elements currently stored in the edge event buffer
 * @return level 
 */
int MorseDecode::GetFillLevel()
{
	return mEdgeEventFillLevel;
}

/**
 * @brief returns the sample rate of the audio input stream
 * @return sample rate
 */
int	MorseDecode::GetAudioInSampleRate()
{
	return mSamplesPerSecond;
}

/**
 * @brief copy the recived text from temperary text buffer and reset the buffer
 * @param str: memory position where the string is stored
 * @param length: size of the allocated memory
 * @return number of bytes copied 
 */
int MorseDecode::GetText(char* str,int length)
{
	int ncpy = 0;
	if(str != nullptr and length>1 and mTextBuffer != nullptr)
	{
		ncpy = length-1;
		if(mTextBufferIndex<ncpy)
		{
			ncpy = mTextBufferIndex;
		}
		strncpy(str,mTextBuffer,ncpy);
		str[ncpy] 			= '\0';
		mTextBufferIndex 	= 0;
	}
	return ncpy;
}

/**
 * @brief access function to the normilzed amplitude
 * @return normilized amplitude
 */
double MorseDecode::GetAmplitude()
{
	return mAmplitude;
}

/**
 * @brief access function to the audio signal envelope
 * @return envelope
 */
double MorseDecode::GetEnvelope()
{
	return mEnvelope;
}

/**
 * @brief access to the threshold value the envelope is compared with
 * @return threshold
 */
double MorseDecode::GetThreshold()
{
	return mThreshold;
}

/**
 * @brief access to the edge state that was detected
 * @return edge state
 */
EdgeState MorseDecode::GetEdge()
{
	return mEdge;
}

/**
 * @brief access to the time intervall between the last two edge events
 * @return time intervall in seconds
 */
double MorseDecode::GetTimeIntervall()
{
	return mDt;
}

/**
 * @brief access to the detected morse sign
 * @return morse sign
 */
MorseSign MorseDecode::GetSign()
{
	return mSign;
}

/**
 * @brief return the last relevant morse sign
 * @return last relevant sign 
 */
MorseSign MorseDecode::GetRelevantSign()
{
	return mRelevantSign;
}

/**
 * @brief access to the time that was determined for the duration of the morse signe dot
 * @return dot time 
 */
double MorseDecode::GetDotTime()
{
	return mDotTime;
}
/**
 * @brief set the maximal amplitude of the audio signal that is passed to Process()
 * @param maxAmplitude: value of the maximal amplitude
 */
void MorseDecode::SetMaxAmplitude(double maxAmplitude)
{
	mMaxAmplitude=std::abs(maxAmplitude);
	if(mMaxAmplitude==0.0)
		mMaxAmplitude=1E-12;
}

/**
 * @brief set the target factor of the threshold compared to the maximal envelope
 * @param factor: value of the new threshold factor
 */
void MorseDecode::SetAutoThresholdFactor(double factor)
{
	mAutoThresholdFactor = factor;
	if(mAutoThresholdFactor < 0.0)
	{
		mAutoThresholdFactor = 0.0;
	}
	if(mAutoThresholdFactor > 1.0)
	{
		mAutoThresholdFactor = 1.0;
	}
}

/**
 * @brief set the minimal value of the threshold
 * @param minThreshold: minimal value of the threshold 
 */
void MorseDecode::SetMinThreshold(double minThreshold)
{
	mAutoThresholdMinThreshold = std::abs(minThreshold);
}

/**
 * @brief set the lower limit of dot duration
 * @param lowerLimit: lower limit of dot time
 */
void MorseDecode::SetDotTimeLowerLimit(double lowerLimit)
{
	mDotTimeLowerLimit = std::abs(lowerLimit);
}

/**
 * @brief set the upper limit of dot duration
 * @param upperLimit: upper limit of dot time
 */
void MorseDecode::SetDotTimeUpperLimit(double upperLimit)
{
	mDotTimeUpperLimit = std::abs(upperLimit);
}

/**
 * @brief set the maximal inaccuracy that is tollerated to esteem dot time as stable
 * @param maxInaccuracy: maximal inaccuracy
 */
void MorseDecode::SetStableDotTimeInaccuracy(double maxInaccuracy)
{
	mStableDotTimeInaccuracy = std::abs(maxInaccuracy);
	if(mStableDotTimeInaccuracy > 1.0)
	{
		mStableDotTimeInaccuracy = 1.0;
	}
}

/**
 * @brief set the maximal number of morse signs a character can have
 * @param maxSigns: maximal morse signs of a character 
 */
void MorseDecode::SetMaxMorseSignsPerChar(uint8_t maxSigns)
{
	mGetCharMaxSign = maxSigns;
	if(mGetCharMaxSign<0u)
	{
		mGetCharMaxSign = 0u;
	}
	if(mGetCharMaxSign > sizeof(mGetCharBuffer)*8)
	{
		mGetCharMaxSign = sizeof(mGetCharBuffer)*8;
	}
	mGetCharBuffer 			= 0;
	mGetCharBufferIndex 	= 0;
}

/**
 * @brief set the samples per seconds of the audio input stream
 * @param rate: sample rate in Hz
 */
void MorseDecode::SetAudioInSampleRate(int rate)
{
	mSamplesPerSecond = std::abs(rate);
	SetDebounceBounceTime(mDebounceBounceTime);
	SetLowPassDecayRate(mLowPassDecayRate);
	SetAutoThresholdDecayRate(mAutoThresholdDecayRate);
}

/**
 * @brief set the bounce time
 * @param bounceTime: bounce time in seconds
 */
void MorseDecode::SetDebounceBounceTime(double bounceTime)
{
	if(IsMemoryLimitReached(mDebounceBufferLength,std::abs(bounceTime)*mSamplesPerSecond,sizeof(EdgeState)))
		return;
		
	if(mDebounceBuffer != nullptr)
	{
		delete[] mDebounceBuffer;
		mDebounceBuffer = nullptr;
	}
	mDebounceBounceTime 	= std::abs(bounceTime);
	mDebounceBufferLength 	= mDebounceBounceTime*mSamplesPerSecond;
	mDebounceBuffer 		= new EdgeState[mDebounceBufferLength];
	mDebouncBufferIdxFront 	= mDebounceBufferLength;
	mDebouncBufferIdxEnd   	= 0;
}

/**
 * @brief set the low pass decay rate
 * @param lowPassDecayRate: decay rate in Hz
 */
void MorseDecode::SetLowPassDecayRate(double lowPassDecayRate)
{
	if(IsMemoryLimitReached(mLowPassFilterLength,(3*mSamplesPerSecond)/std::abs(lowPassDecayRate),sizeof(double)) or lowPassDecayRate == 0.0)
		return;
		
	if(mLowPassFilterBuffer != nullptr)
	{
		delete[] mLowPassFilterBuffer;
		mLowPassFilterBuffer 	= nullptr;
	}
	
	mLowPassDecayRate 		= std::abs(lowPassDecayRate);
	mLowPassFilterLength 	= (3*mSamplesPerSecond)/mLowPassDecayRate;
	mLowpassDamping			= std::exp(-mLowPassDecayRate/mSamplesPerSecond);
	mLowPassFilterBuffer	= new double[mLowPassFilterLength];
	mLowPassfIndex 			= mLowPassFilterLength;
}

/**
 * @brief set the decay rate of the threshold
 * @param autoThresholdDecayRate: decay rate in Hz
 */
void MorseDecode::SetAutoThresholdDecayRate(double autoThresholdDecayRate)
{
	mAutoThresholdDecayRate = std::abs(autoThresholdDecayRate);
	mAutoThresholdDamping = std::exp(-mAutoThresholdDecayRate/mSamplesPerSecond);
}

/**
 * @brief set the length of the average time
 * @param aveTimeBufferLength: buffer length
 */
void MorseDecode::SetAveTimeBufferLength(uint8_t aveTimeBufferLength)
{
	if(IsMemoryLimitReached(mTimeAveBufferLength,aveTimeBufferLength,sizeof(double)))
		return;
		
	if(mTimeAveBuffer != nullptr)
	{
		delete[] mTimeAveBuffer;
		mTimeAveBuffer = nullptr;
	}
	mTimeAveBufferLength 	= aveTimeBufferLength;
	mTimeAveBuffer 			= new double[mTimeAveBufferLength];
	mTimeAveFillLevel 		= 0;
	mTimeAveIndex 			= 0;
}

/**
 * @brief set the length of the shortest time buffer
 * @param shrtTimeBufferLength: buffer length
 */
void MorseDecode::SetShortTimeBufferLength(uint8_t shrtTimeBufferLength)
{
	if(IsMemoryLimitReached(mShrtTimeBufferLength,shrtTimeBufferLength,sizeof(double)))
		return;
		
	if(mShrtTimeBuffer != nullptr)
	{
		delete[] mShrtTimeBuffer;
		mShrtTimeBuffer = nullptr;
	}
	mShrtTimeBufferLength 	= shrtTimeBufferLength;
	mShrtTimeBuffer 		= new double[mShrtTimeBufferLength];
	mShrtTimeFillLevel 		= 0;
	mShrtTimeIndex 			= 0;
}

/**
 * @brief set the length of the stable dot time buffer
 * @param stableDotTimeBufferLength: buffer length
 */
void MorseDecode::SetStableDotTimeBufferLength(uint8_t stableDotTimeBufferLength)
{
	if(IsMemoryLimitReached(mStableDotTimeBufferLength,stableDotTimeBufferLength,sizeof(double)))
		return;
		
	if(mStableDotTimeBuffer != nullptr)
	{
		delete[] mStableDotTimeBuffer;
		mStableDotTimeBuffer = nullptr;
	}
	mStableDotTimeBufferLength = stableDotTimeBufferLength;
	mStableDotTimeIndex 	= 0;
	mStableDotTimeBuffer	= new double[mStableDotTimeBufferLength];
	for(int i=0;i<mStableDotTimeBufferLength;i++)
	{
		if(i%2 == 0)
		{
			mStableDotTimeBuffer[i] = 1000;
		}
		else
		{
			mStableDotTimeBuffer[i] = -1000;
		}
	}
}

/**
 * @brief set length of the edge event buffer 
 * @param edgeEventBufferLength: buffer length
 */
void MorseDecode::SetEdgeEventBufferLength(uint8_t edgeEventBufferLength)
{
	if(IsMemoryLimitReached(mEdgeEventBufferLength,edgeEventBufferLength,sizeof(double)+sizeof(EdgeState)))
		return;
		
	if(mEdgeEventPeriodBuffer != nullptr)
	{
		delete[] mEdgeEventPeriodBuffer;
		mEdgeEventPeriodBuffer = nullptr;
	}
	if(mEdgeEventStateBuffer != nullptr)
	{
		delete[] mEdgeEventStateBuffer;
		mEdgeEventStateBuffer = nullptr;
	}
	mEdgeEventBufferLength  = edgeEventBufferLength;
	mEdgeEventDotTimeValid 	= false;
	mEdgeEventIdxFill 		= 0;
	mEdgeEventIdxEmpty 		= mEdgeEventIdxFill;
	mEdgeEventFillLevel 	= 0;
	mEdgeEventPeriodBuffer  = new double[mEdgeEventBufferLength];
	mEdgeEventStateBuffer	= new EdgeState[mEdgeEventBufferLength];
}

/**
 * @brief return a label string for a numeriacal value of the MorseSign enum
 * @param sign: sign for which a label are returned
 * @return label for the sign 
 */
const char* MorseDecode::GetSignStr(Morse::MorseSign sign)
{
	const char * res;
	switch(sign)
	{
		case DOT:
		{
			res = "DOT";
		}
		break;
		case DASH:
		{
			res = "DOT";
		}
		break;
		case NO_SIGN:
		{
			res = "NO SIGN";
		}
		break;
		case SPACE:
		{
			res = "SPACE";
		}
		break;
		case FLUSH:
		{
			res = "FLUSH";
		}
		break;
		case SPACE_CHAR:
		{
			res = "CHAR SPACE";
		}
		break;
		case SPACE_WORD:
		{
			res = "WORD SPACE";
		}
		break;
		default:
		{
			res = "UNKOWN";
		}
		break;
	}
	return res;
}

/**
 * @brief set text message buffer length
 * @param textBufferLength: length of the buffer
 */
void MorseDecode::SetTextBufferLength(int textBufferLength)
{
	if(IsMemoryLimitReached(mTextBufferLength,std::abs(textBufferLength),sizeof(char)))
		return;
	
	if(mTextBuffer != nullptr)
	{
		delete[] mTextBuffer;
		mTextBuffer = nullptr;
	}
	
	mTextBufferIndex = 0;
	mTextBufferLength = std::abs(textBufferLength);
	if(mTextBufferLength>0)
	{
		mTextBuffer = new char[mTextBufferLength];
	}
}

/**
 * @brief set the amount of memory that should not exceeded
 * @param maxMemory: memory size in bytes
 */
void MorseDecode::SetMaxMemoryConsumption(int maxMemory)
{
	mMemoryToUse = std::abs(maxMemory);
	IsMemoryLimitReached(0,0,0);
}

/**
 * @brief checkes if memory limit was exceeded
 * @return true if limit was reached otherwise false
 */
bool MorseDecode::IsMemoryConsumtionExceeded()
{
	return mMemoryExceeded;
}

/**
 * @brief helper function that calculates the memory consumption if buffer would be changed
 * @param numElmtDeleted: elements that are freed
 * @param numElmtNew: elments for which new memory allocated
 * @param SizeofElmt: size of an element in bytes
 * @return true if the memory consumption after free and allocation operation would exceed the limit, otherwise false
 */
bool MorseDecode::IsMemoryLimitReached(int numElmtDeleted, int numElmtNew,int SizeofElmt)
{
	int dMem = (numElmtNew-numElmtDeleted)*SizeofElmt;
	bool res = (mMemoryConsumption+dMem)>mMemoryToUse;
	if(res)
	{
		mMemoryExceeded = true;
	}
	else
	{
		mMemoryConsumption +=dMem;
	}
	return res;
}