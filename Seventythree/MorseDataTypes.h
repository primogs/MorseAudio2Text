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
#ifndef MORSE_DATA_TYPE
#define MORSE_DATA_TYPE

namespace Morse
{
    /*! \enum EdgeState
	 * - NONE:	no edge is detected
	 * - RISING:	a tone is rise
	 * - FALLING:	a tone is fading
	 * */
	enum EdgeState {NONE,RISING,FALLING};
	
	/*! \enum MorseSign
	 * - UNKOWN_SIGN:	state is not kown
	 * - NO_SIGN:		no sign is found
	 * - FLUSH:		to flush the processing pipe 
	 * - DOT:			a short tone 
	 * - DASH:		a long tone 	( 3 times longer than DOT )
	 * - SPACE:		a short pause 	( as long as DOT )
	 * - SPACE_CHAR:	a mid pause 	( 3 times longer than DOT )
	 * - SPACE_WORD:	a long pause 	( 7 times longer than DOT )
	 * */
	enum MorseSign {UNKOWN_SIGN,NO_SIGN,FLUSH,	
						DOT,
						DASH,
						SPACE,
						SPACE_CHAR,
						SPACE_WORD};
}
						
#endif