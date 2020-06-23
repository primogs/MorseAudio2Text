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
#ifndef MORSEDECODE_H
#define MORSEDECODE_H

#include <cstdint>
#include <cmath>
#include <cstring>
#include <iostream>

#include "MorseDataTypes.h"
#include "MorseStatistic.h"

//!  The morse decoder class process a audio stream and output morse signals as a text.
/*!
  The data is processed in a pipe by following functions
  	-# NormalizedAmplitude() \n	
	   Normilize the amplitude and take the absolute value of the audio signal.  
  	-# Lowpass() \n
	   Lowpass the normalized amplitude to get the envelope of the audio signal.
  	-# AutomaticThreshold() \n
	   Determine a threshold from the envelope
  	-# EdgeTrigger() \n
	   Compare the envelope with the threshold to determine if a continues wave (CW) is currently starts or end (edge event)
  	-# Debounce() \n
	   Debounce the edge events to avoid misinterpretation.
  	-# TimeGap() \n
	   Measures the time between two edge events.
  	-# EdgeEvent() \n
	   Calls GetMorseSign() to get the a Morse sign (dot, dash, space,..). The function output is may retarded as long the timing isn't stable. 
	-# GetCharacter() \n
	   Look up the character if all Morse signs of a character are received.

\image html Signal.svg "audio signal of a dot" width=1600cm
\image html NormalizedAmplitudeAndEnvelope.svg "normalized amplitude and envelope of the audio signal" width=1600cm
\image html EnvelopeThresholdEdgestateTimeintervalEvents.svg "envelope threshold and some events" width=1600cm
*/
/**
 * @class MorseDecode
 * @author Matthias Hund
 * @date 05/24/20
 * @file MorseDecode.h
 */
class MorseDecode: public MorseStatistic
{	
public:
	MorseDecode(int samplesPerSecond,double initDotTime = 0.0655);
	~MorseDecode();
	
	void 				Reset();
	
	const char* 		Process(double signal);
	
	int 				GetText(char* str,int length);
	const char* 		GetCharacter(Morse::MorseSign sign);
	double 				GetAmplitude();
	double 				GetEnvelope();
	double 				GetThreshold();
	Morse::EdgeState	GetEdge(); 
	double 				GetTimeIntervall();
	Morse::MorseSign	GetSign();
	Morse::MorseSign	GetRelevantSign();
	static const char*	GetSignStr(Morse::MorseSign);
	double 				GetDotTime();
	int 				GetFillLevel();
	int					GetAudioInSampleRate();
	
	void 				SetAudioInSampleRate(int rate);
	void 				SetMaxAmplitude(double maxAmplitude);
	void				SetAutoThresholdFactor(double factor);
	void 				SetMinThreshold(double minThreshold);
	void 				SetDotTimeLowerLimit(double lowerLimit);
	void 				SetDotTimeUpperLimit(double upperLimit);
	void 				SetStableDotTimeInaccuracy(double maxInaccuracy);
	void 				SetMaxMorseSignsPerChar(uint8_t maxSigns);
	void 				SetDebounceBounceTime(double bounceTime);
	void 				SetLowPassDecayRate(double lowPassDecayRate);
	void 				SetAutoThresholdDecayRate(double autoThresholdDecayRate);
	void 				SetAveTimeBufferLength(uint8_t aveTimeBufferLength);
	void 				SetShortTimeBufferLength(uint8_t shrtTimeBufferLength);
	void 				SetStableDotTimeBufferLength(uint8_t stableDotTimeBufferLength);
	void 				SetEdgeEventBufferLength(uint8_t edgeEventBufferLength);
	void				SetTextBufferLength(int textBufferLength);
	void				SetMaxMemoryConsumption(int maxMemory);
	
	bool 				IsMemoryConsumtionExceeded();
private:
	/*! \enum SignalState 
	 * - UNKOWN:	state is not kown
	 * - LOW:		no tone is detect
	 * - HIGH:	a tone is detect
	 * */
	enum SignalState {UNKOWN,LOW,HIGH};
	
	inline double 		NormalizedAmplitude(double signal);
	double 				Lowpass(double newSample);
	double 				AutomaticThreshold(double envelope);
	Morse::EdgeState 	EdgeTrigger(double input, double threshold);
	Morse::EdgeState 	Debounce(Morse::EdgeState state);
	double 				TimeGap(Morse::EdgeState state);
	inline double 		DistinctionLevel(double lLevel,double hLevel);
	int 				RoundTime(double timeRatio);
	double 				TimeAverage(double newTime);
	double 				TimeShortest(double newTime);
	double 				DetectDotTime(double period);
	Morse::MorseSign 	GetMorseSign(double dotTime,Morse::EdgeState edge,double period);
	bool 				IsDotTimeStable(double dotTime);
	Morse::MorseSign 	EdgeEvent(Morse::EdgeState edge,double period);
	int 				GetIndex(const uint16_t sequence,const uint16_t *signSequences,uint32_t nSequences);
	const char* 		DecodeCharacter(uint16_t signBuffer,int nSigns);
	void 				AppendToTxtBuffer(const char * character);
	bool				IsMemoryLimitReached(int numElmtDeleted, int numElmtNew,int SizeofElmt);
	void				FreeMemory();
	
	double 				mAmplitude;				//!< nomalized amplitude
	double 				mEnvelope;				//!< envelope of the audio signal
	double 				mThreshold;				//!< threshold the envelope is compared with
	Morse::EdgeState 	mEdge;					//!< current trigger state that was detected
	double 				mDt;					//!< time intervall between last two trigger events
	Morse::MorseSign 	mSign;					//!< current morse sign
	Morse::MorseSign 	mRelevantSign;			//!< store a subset of morse signs, e.g. not NO_SIGN
	const char	* 		mCharacter;				//!< last character that was detected
	int 				mSamplesPerSecond;		//!< sample rate of the audio stream
	double 				mMaxAmplitude;			//!< maximal amplitude of the audio stream
	
	double 				mDebounceBounceTime;	//!< lockout time of the debounce function in sceonds
	Morse::EdgeState*	mDebounceBuffer;		//!< FIFO buffer to debounce the trigger state 
	int 				mDebounceBufferLength;	//!< length of the FIFO debounce buffer
	int 				mDebouncBufferIdxFront; //!< saves the las signal state to determine a if rising or falling edge
	int 				mDebouncBufferIdxEnd; 	//!< saves the las signal state to determine a if rising or falling edge
	
	double 				mLowPassDecayRate;		//!< decay rate (1/time constant) of the low pass filter in Hz
	int 				mLowPassFilterLength;	//!< length of the low pass filter
	int 				mLowPassfIndex;			//!< current index of the low pass filter
	double		*		mLowPassFilterBuffer;	//!< buffer to store filter elements
	double 				mLowpassDamping;		//!< damping value each filter element is multiplied with
	
	double 				mAutoThresholdDecayRate;	//!< decay rate (1/time constant) of the threshold damping in Hz
	double 				mAutoThresholdDamping;		//!< damping value each filter element is multiplied with
	double				mAutoThresholdMinThreshold;	//!< lower limit for the threshold
	double				mAutoThresholdFactor;		//!< target factor of the threshold/max(envelope) ratio
	
	SignalState 		mEdgeTriggerLastState; 	//!< saves the las signal state to determine a if rising or falling edge
	
	unsigned int 		mTimerDigitalTime; 		//!< timer to count time between to signal states
	unsigned int 		mTimerStartTime;		//!< start time of the timer
	
	const double 		mRoundTimeLevel[4];		//!< integer values for the time ratio to which may be rounded
	
	int 				mTimeAveBufferLength;	//!< length of the average time buffer 
	double 		*		mTimeAveBuffer;			//!< average time buffer
	int 				mTimeAveFillLevel;		//!< numbers of buffer elements that are stored in the buffer 
	int					mTimeAveIndex;			//!< index on the buffer element currently used
	
	int 				mShrtTimeBufferLength;	//!< length of the shortest time buffer
	double 		*		mShrtTimeBuffer;		//!< shortest time buffer
	int 				mShrtTimeFillLevel;		//!< numbers of buffer elements that are stored in the shortest time buffer 
	int					mShrtTimeIndex;			//!< index on the shortest time buffer element currently used
	
	const double 		mInitDotTime;			//!< inital value for the dot time
	double 				mDotTime;				//!< time that a dot takes 
	double 				mDotTimeLowerLimit;		//!< lower limit for the dot time
	double 				mDotTimeUpperLimit;		//!< upper limit for the dot time
	
	double 		*		mStableDotTimeBuffer;		//!< buffer to store the last dot times
	int					mStableDotTimeIndex = 0;	//!< index on the last dot time buffer element currently used
	int 				mStableDotTimeBufferLength; //!< length of the dot time buffer
	double 				mStableDotTimeInaccuracy;	//!< acceptable inaccuracy of the dot time in the buffer 
	
	bool 				mEdgeEventDotTimeValid;	//!< indicates that the dot time varries only a little
	int 				mEdgeEventBufferLength; //!< length of the edge event buffers
	int 				mEdgeEventIdxFill;		//!< index of the edge event buffer where the next input element is stored
	int 				mEdgeEventIdxEmpty;		//!< index of the edge event buffer where the nect output element is taken from
	int 				mEdgeEventFillLevel;	//!< number of edge event buffer entries currently in use 
	double 		*		mEdgeEventPeriodBuffer;	//!< edge event buffer to store the time period between to trigger events
	Morse::EdgeState *	mEdgeEventStateBuffer;	//!< edge event buffer to store the trigger event
	
	uint8_t  			mGetCharMaxSign;		//!< the maximal amount of dots/dashes of a character
	uint16_t 			mGetCharBuffer;			//!< buffer to store a binary dot/dash sequence. Dots are 0 and dashes are 1. 
	uint8_t 			mGetCharBufferIndex;	//!< number of dots/dashes stored in the buffer
	char 				mGetCharStr[4];			//!< char buffer used if a blank space need to be append
	
	int 				mTextBufferLength;		//!< length of text buffer 
	int 				mTextBufferIndex;		//!< index of the text buffer
	char			*	mTextBuffer;			//!< text buffer to store decoded message temporarely
	
	int					mMemoryConsumption;		//!< size of allocated memory
	int					mMemoryToUse;			//!< maximal memory that should be used
	bool				mMemoryExceeded;		//!< flag to indicate if memory limit was exceeded
};

#endif // MORSEDECODE_H
