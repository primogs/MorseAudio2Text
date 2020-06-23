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
#include <sstream>
#include <algorithm>
#include "ConfigFile.h"

ConfigFile::ConfigFile(): mpConfigFileName("config.txt")
{
}

ConfigFile::~ConfigFile()
{
}

/**
 * @brief check if config file is available in folder of the program
 * @return true if a config file was found, otherwise false
 */
bool ConfigFile::IsConfigFileAvailable()
{
	std::ifstream fs;
	fs.open(mpConfigFileName);
	bool res = fs.is_open();
	if(res)
	{
		fs.close();
	}
	return res;
}

/**
 * @brief check if the string starts with a hash. Leading whitespaces are ignored.
 * @param str: string to be searched
 * @return true if the string starts with a hash, otherwise false
 */
bool ConfigFile::StartWithHash(std::string str)
{
	bool res = false;
	std::size_t pos = str.find_first_of('#');
	if(pos != std::string::npos)
	{
		res = true;
		for(std::size_t i = 0;i<pos;i++)
		{
			if(!std::isspace(str.at(i)))
				res = false;
		}
	}
	return res;
}

/**
 * @brief reads the config file line by line and stores every parameter 
 */
void ConfigFile::ReadConfigFile()
{
	std::ifstream fs;
	fs.open(mpConfigFileName);
	std::string line;
	while (std::getline(fs, line))
	{
		if(StartWithHash(line) or line.length() < 3) // hash is comment and a valid line needs at least 1 char for name 1 delimeter and 1 char for value
			continue;
		std::stringstream sstr(line);
		std::string varName;
		sstr >> varName;
		double varValue;
		sstr >> varValue;
		
		if(varName.length() < 64)
		{
			mVariables.push_back(std::make_tuple(varName,varValue));
		}
	}
}

/**
 * @brief deletes the stored parameters 
 */
void ConfigFile::Reset()
{
	mVariables.clear();	
}

/**
 * @brief counts the number of stored parameters 
 * @return number of parameters 
 */
int	ConfigFile::GetNumberOfVariables()
{
	return mVariables.size();
}

/**
 * @brief looks if a the parameter is stored and if it is, copies the parameter value
 * @param varName: name of the parameter searched for 
 * @param varValue: value of the parameter if it was stored
 * @return true if the parameter was found, otherwise false
 */
bool ConfigFile::GetVariable(std::string varName, double &varValue)
{
	for(std::list<std::tuple<std::string,double> >::iterator it=mVariables.begin(); it != mVariables.end();it++ )
	{
		if(std::get<0>(*it) == varName)
		{
			varValue = std::get<1>(*it);
			return true;
		}
	}
	return false;
}

