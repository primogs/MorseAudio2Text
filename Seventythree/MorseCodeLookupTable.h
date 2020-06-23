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


#ifndef MORSE_CODE_LOOKUP_TABEL
#define MORSE_CODE_LOOKUP_TABEL

namespace Morse
{
	const char* Sign_1 [] = {"E","T"};
		
	/*const uint16_t SignSequence_2 [] = {
												0b00,
												0b01,
												0b10,
												0b11};*/
	const char* Sign_2 [] = {"I","A","N","M"};
		
	/*const uint16_t SignSequence_3 [] = {
											0b000,
											0b001,
											0b010,
											0b011,
											0b100,
											0b101,
											0b110,
											0b111};*/
	const char* Sign_3 [] = {"S","U","R","W","D","K","G","O"};
		
	/*const uint16_t SignSequence_4 [] = {
											0b0000,	// H
											0b0001,	// V
											0b0010,	// F
											0b0011,	// Ü
											0b0100, // L
											0b0101,	// Ä
											0b0110, // P
											0b0111, // J
											0b1000, // B
											0b1001, // X 
											0b1010, // C
											0b1011, // Y
											0b1100, // Z
											0b1101,	// Q
											0b1110, // Ö
											0b1111};// CH */
	const char* Sign_4 [] = {"H","V","F","Ü","L","Ä","P","J","B","X","C","Y","Z","Q","Ö","CH"};
		
	/*const uint16_t SignSequence_5 [] = {
											0b00000, // 5
											0b00001, // 4
											0b00010, // n.b.
											0b00011, // 3
											0b00100, // É
											0b00101, // n.b.
											0b00110, // n.b.
											0b00111, // 2
											0b01000, // n.b.
											0b01001, // È
											0b01010, // + 
											0b01011, // n.b.
											0b01100, // n.b.
											0b01101, // À
											0b01110, // n.b.
											0b01111, // 1
											0b10000, // 6
											0b10001, // =
											0b10010, // /
											0b10011, // n.b.
											0b10100, // n.b.
											0b10101, // n.b.
											0b10110, // (
											0b10111, // n.b.
											0b11000, // 7
											0b11001, // n.b.
											0b11010, // n.b.
											0b11011, // ~N
											0b11100, // 8 
											0b11101, // n.b.
											0b11110, // 9
											0b11111};// 0 */
	const uint16_t SignSequence_5 [] = {0b00000,0b00001,0b00011,0b00100,0b00111,0b01001,0b01010,0b01101,0b01111,0b10000,0b10001,0b10010,0b10110,0b11000,0b11011,0b11100,0b11110,0b11111};
	const char* Sign_5 [] = {"5","4","3","É","2","È","+","À","1","6","=","/","(","7","Ñ","8","9","0"};

	const uint16_t SignSequence_6 [] = {
											0b011110, // "'"
											0b011010, // "@"
											0b010101, // "."
											0b010010, // "\""
											0b001101, // "_"
											0b001100, // "?"
											0b111000, // ":"
											0b110011, // ","
											0b101101, // ")"
											0b101010, // ";"
											0b100001 // "-"
										};

	const char* Sign_6 [] = { "'","@",".","\"","_","?",":",",",")",";","-"};

	const uint16_t SignSequence_7 [] = {
											0b0001100, // "ß"
										};
	const char* Sign_7 [] = {"ß"};

	const uint16_t SignSequence_8 [] = {
											0b00000000, // " Irrung "
										};
	const char* Sign_8 [] = {" Irrung "};
}
#endif