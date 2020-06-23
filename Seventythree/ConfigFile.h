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
#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <fstream>
#include <list>
#include <string>
#include <tuple>
/**
 * @class ConfigFile
 * @author Matthias Hund
 * @date 06/06/20
 * @file ConfigFile.h
 * @brief Reads configuration from a file. Each line of the file should consist a empty, a comment or ar parameter name/value pair. 
 */
class ConfigFile
{
public:
	ConfigFile();
	virtual ~ConfigFile();
	
	void 	Reset();
	int		GetNumberOfVariables();
	bool 	GetVariable(std::string varName, double &varValue);
	bool 	IsConfigFileAvailable();
	void 	ReadConfigFile();
	
private:
	bool 	StartWithHash(std::string str);
	
	const std::string 							mpConfigFileName;	//!< file name of the config file
	std::list<std::tuple<std::string,double> >	mVariables;			//!< parameter list. Each list element is a name/value tuple
};

#endif // CONFIGFILE_H
