/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Parses argv and argc into a std::map
 
 **************************************************************************
 
 Copyright © 2010 Morgan Jones
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 **************************************************************************
 
 */

#include "defs.h"

#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

#ifndef WOLF_COMMAND_LINE_H
#define WOLF_COMMAND_LINE_H

/*!
 *	Represents one command line argument.
 */	

class tCommandLineArg {
public:
	tCommandLineArg(string value);
	string value();
private:
	string _value;
};

/*!
 *	Represents the possible values a key can take
 */	

class tCommandEntity {
public:
	tCommandEntity(string long_name, string short_name, bool easy);
	bool operator == (const tCommandEntity &comp) const;
	bool operator != (const tCommandEntity &comp) const;
	bool operator <	 (const tCommandEntity &comp) const;
	bool operator >	 (const tCommandEntity &comp) const;
	string shortName();
	string longName();
	bool parsed();
	bool easy();
	void parseMe();
protected:
	string _long_name, _short_name;
	bool _parsed, _easy;
};

typedef map <tCommandEntity, tCommandLineArg> tCommandLineMap;
typedef vector <tCommandEntity> tCommandVector;

/*!
 *	Parses command line args
 */	

class tCommandLineParser {
public:
	tCommandLineParser(int argc, char **argv);
	void parse(int argc, char **argv);
	void addOption(string long_name, string short_name, bool easy = false);
	bool parsed();
	string launchPath();
	string elementWithKey(string key);
private:
	string _launch_path;
	tCommandLineMap _map;
	tCommandVector  _vec;
};

#endif /* WOLF_COMMAND_LINE_H */
