/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Colors
 
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

#include "tColor.h"

/*!
 *	Creates a tColor, initializing it to opaque white.
 */

tColor::tColor() {
	/* Default to opaque white */
	r = g = b = a = 255;
}

/*!
 *	Creates a tColor, initializing it to any set of values.
 */

tColor::tColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
	r = R;
	g = G;
	b = B;
	a = A;
}

/*!
 *	Creates a tColor, initializing it from a string.
 */

tColor::tColor(string fill_from) {
	r = g = b = a = 255;
	parseString( fill_from );
}

/*!
 *	Uses a string to populate the class's fields. Example: 0x1235678, #123456, ffffff, etc.
 */

void tColor::parseString(string parse) {
	/* Vars */
	size_t length = parse.length(), bias = 0;
	
	/* Check it */
	if( length == 0 || parse.empty() )
		return;
	
	/* 0x123456 */
	if( parse.find( "0x" ) == 0 )
		bias = 2;
	
	/* #123456 */
	else if( *parse.begin() == '#' )
		bias = 1;
	
	/* 123456 */
	else if( length != 6 && length != 8 )
		return;
	
	/* Make sure at least 6 chars are hexadecimal values. If not, return. */
	for( size_t i = bias; i < length; i++ ) {
		if( !isxdigit( parse[i] ) && i < 6 )
			return;
		else if( !isxdigit( parse[i] ) && i >= 6 )
			length -= 2;
		else
			parse[i] = toupper( parse[i] );
	}
	
	/* For a string with 3 color values, set those. */
	if( length - bias >= 6 ) {
		r = hti( parse[bias + 0], parse[bias + 1] );
		g = hti( parse[bias + 2], parse[bias + 3] );
		b = hti( parse[bias + 4], parse[bias + 5] );
	}
	
	/* Take care of the alpha if applicable. */
	if( length - bias >= 8 )
		a = hti( parse[bias + 6], parse[bias + 7] );
}

tColor & tColor::operator = (tColor &value) {
    if( this == &value )
        return *this;
    else {
		r = value.r;
		g = value.g;
		b = value.b;
		a = value.a;
    }
	return *this;
}

tColor & tColor::operator += (tColor &value) {
	if( this == &value )
        return *this;
    else {
		r += value.r;
		g += value.g;
		b += value.b;
		a += value.a;
    }
	return *this;
}

tColor & tColor::operator -= (tColor &value) {
	if( this == &value )
        return *this;
    else {
		r -= value.r;
		g -= value.g;
		b -= value.b;
		a -= value.a;
    }
	return *this;
}

tColor & tColor::operator *= (tColor &value) {
	if( this == &value )
        return *this;
	else {
		r *= value.r;
		g *= value.g;
		b *= value.b;
		a *= value.a;
    }
	return *this;
}

tColor & tColor::operator /= (tColor &value) {
	if( this == &value )
        return *this;
    else {
		/* Use floating point for better accuracy */
		r = ( (float)r / (float)value.r ) * 255;
		g = ( (float)g / (float)value.g ) * 255;
		b = ( (float)b / (float)value.b ) * 255;
		a = ( (float)a / (float)value.a ) * 255;
    }
	return *this;
}

tColor & tColor::operator &= (tColor &value) {
	if( this == &value )
        return *this;
	else {
		r &= value.r;
		g &= value.g;
		b &= value.b;
		a &= value.a;
    }
	return *this;
}

tColor & tColor::operator |= (tColor &value) {
	if( this == &value )
        return *this;
    else {
		r |= value.r;
		g |= value.g;
		b |= value.b;
		a |= value.a;
    }
	return *this;
}

tColor & tColor::operator ^= (tColor &value) {
	if( this == &value )
        return *this;
    else {
		r ^= value.r;
		g ^= value.g;
		b ^= value.b;
		a ^= value.a;
    }
	return *this;
}

const tColor tColor::operator + (tColor &other) const {
	return tColor(*this) += other;
}

const tColor tColor::operator - (tColor &other) const {
	return tColor(*this) -= other;
}

const tColor tColor::operator * (tColor &other) const {
	return tColor(*this) *= other;
}

const tColor tColor::operator / (tColor &other) const {
	return tColor(*this) /= other;
}

const tColor tColor::operator & (tColor &other) const {
	return tColor(*this) &= other;
}

const tColor tColor::operator | (tColor &other) const {
	return tColor(*this) |= other;
}

const tColor tColor::operator ^ (tColor &other) const {
	return tColor(*this) ^= other;
}

const bool tColor::operator == (const tColor comp) const {
	return memcmp( this, &comp, sizeof( tColor ) ) == 0;
}

const bool tColor::operator != (const tColor comp) const {
	return !( *this == comp );
}

const bool tColor::operator < (const tColor comp) const {
	return memcmp( this, &comp, sizeof( tColor ) ) < 0;
}

const bool tColor::operator > (const tColor comp) const {
	return memcmp( this, &comp, sizeof( tColor ) ) > 0;
}

const bool tColor::operator <= (const tColor comp) const {
	return memcmp( this, &comp, sizeof( tColor ) ) <= 0;
}

const bool tColor::operator >= (const tColor comp) const {
	return memcmp( this, &comp, sizeof( tColor ) ) >= 0;
}

/*!
 *	Returns the equivalent SDL_Color
 */

SDL_Color tColor::SDL() {
	SDL_Color ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.unused = a;
	
	return ret;
}

/*!
 *	Uses a simple algorithm including bitwise operators and ASCII math to convert a hex color pair to an integer.
 */

uint8_t tColor::hti(char x, char y) {
	/* Vars */
	uint8_t ret = 0;
	
	/* Convert first character */
	if( isalpha( x ) )
		x -= 0x07;
	ret |= (x - 0x30) << 4;
	
	/* Convert second character */
	if( isalpha( y ) )
		y -= 0x07;
	ret |= (y - 0x30);
	
	return ret;
}
