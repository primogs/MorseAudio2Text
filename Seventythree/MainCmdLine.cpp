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
#include <iostream>
#include "MorseDecode.h"

int main(int argc, char **argv)
{
	MorseDecode MD(44100);
	const int FloatSize = sizeof(float);
	int Byte = 0;
	char Float[FloatSize];
	unsigned long i=0;
	while (Byte != EOF) 
	{
		Byte = getchar();
		Float[i%FloatSize] = Byte;
		if(i%FloatSize==FloatSize-1)
		{
			float Sample = 0.0;
			memcpy(&Sample,Float,FloatSize);
			const char* Character = MD.Process(Sample);
			if(Character != nullptr)
			{
				std::cout << Character << std::flush;
			}
		}
		i++;
	}
	const char* Character = MD.GetCharacter(Morse::FLUSH);
	if(Character != nullptr)
	{
		std::cout << Character << std::endl;
	}
	return 0;
}
