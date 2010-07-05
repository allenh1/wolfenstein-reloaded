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
 but WITHOUT ANY WARRANTY {
 
 }
 without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 **************************************************************************
 
 */

#include "tString.h"

tCharacterInfo & tCharacterInfo::operator =  (tCharacterInfo value) {
	color = value.color;
	pos = value.pos;
	return *this;
}

tString::tString() {
}

tString::tString(tString &value) {
	if( this != &value )
		*this = value;
}

tString & tString::operator =  (tString &value) {
	if( this != &value )
	{
		*this = value;
		this->_charInfo = value._charInfo;
	}
	return *this;
}

tString & tString::operator += (tString &value) {
	if( this != &value )
		*this << value;
	return *this;
}

tString & tString::operator << (tString &value) {	
	/* Get the end iterator */
	string::iterator last = end();
	
	/* Append the value */
	append( value );
	
	/* Normalize the character info to this string */
	for( tCharacterVector::iterator it = value._charInfo.begin(); it != value._charInfo.end(); it++ )
	{
		/* Set the color */
		tCharacterInfo info;
		info.color = it->color;
		
		/* Use iterator trickery to get the position */
		cout << ( it->pos - value.begin() );
		info.pos = last + ( it->pos - value.begin() );
		cout << *info.pos;
		
		/* Push it back */
		_charInfo.push_back( info );
	}
	
	return *this;
}

tString & tString::operator << (string value) {
	if( this != &value )
		append( value );
	return *this;
}

tString & tString::operator << (const char * value) {
	return *this << string( value );
}

tString & tString::operator << (tColor value) {
	/* Set up the info */
	tCharacterInfo info;
	info.color = value;
	info.pos = end();
	
	/* Push it back */
	_charInfo.push_back( info );
	
	return *this;
}

tString & tString::operator << (tCharacterInfo value)
{
	/* Push it back */
	_charInfo.push_back( value );
	return *this;
}

const tString & tString::operator + (tString &other) {
	if( this != &other )
		*this << other;
	return *this;
}

const bool tString::operator == (tString comp) const {
	return *this == comp;
}

const bool tString::operator != (tString comp) const {
	return !(*this == comp);
}

void tString::updateColors() {
	for( tCharacterVector::reverse_iterator it = _charInfo.rbegin(); it != _charInfo.rend(); it++ ) {
		if( it->pos > end() )
			_charInfo.pop_back();
	}
}

void tString::removeColors() {
	_charInfo.clear();
}

void tString::replaceColors(tColor replace, tColor replace_with) {
	for( tCharacterVector::iterator it = _charInfo.begin(); it != _charInfo.begin(); it++ ) {
		if( it->color == replace )
			it->color = replace_with;
	}
}

void tString::setColor(tColor new_color) {
	/* Set up a new char info */
	tCharacterInfo info;
	info.color = new_color;
	info.pos = begin();
	
	/* Clear information vector */
	_charInfo.clear();
	
	/* Push it */
	_charInfo.push_back( info );
}

void tString::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	setColor( tColor( r, g, b, a ) );
}

void tString::setColor(string new_color) {
	setColor( tColor( new_color ) );
}

tColor tString::colorString(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return tColor( r, g, b, a );
}

tColor tString::colorString(string color) {
	return tColor( color );
}
