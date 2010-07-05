/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Wolfenstein string library
 
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

#ifndef WOLF_STRING_H
#define WOLF_STRING_H

#include "defs.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include "tColor.h"

class tCharacterInfo {
public:
	tCharacterInfo & operator =  (tCharacterInfo value);
	tColor color;
	string::iterator pos;
};

typedef vector <tCharacterInfo> tCharacterVector;

class tString : public string {
public:
	tString();
	tString(tString &value);
	
	tString & operator =  (tString &value);
	tString & operator += (tString &value);
	
	tString & operator << (tString &value);
	tString & operator << (string  value);
	tString & operator << (const char * value);
	tString & operator << (tColor   value);
	
	const tString & operator + (tString &other);
	
	const bool operator == (tString comp) const;
	const bool operator != (tString comp) const;

	void updateColors();
	void removeColors();
	void replaceColors(tColor replace, tColor replace_with);
	
	void setColor(tColor new_color);
	void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff);
	void setColor(string new_color);
	
	static tColor colorString(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff);
	static tColor colorString(string color);
protected:
	tString & operator << (tCharacterInfo value);
private:
	tCharacterVector _charInfo;
};

#endif // WOLF_STRING_H
