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

#ifndef WOLF_COLOR_H
#define WOLF_COLOR_H

#include "defs.h"

#include <string>
#include <cctype>

#include "tSDL.h"

/*!
 *	A simple color mixing class.
 */

class tColor {
public:
	tColor();
	tColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255);
	explicit tColor(string fill_from);

	void parseString(string parse);

	tColor & operator =  (tColor &value);
	tColor & operator += (tColor &value);
	tColor & operator -= (tColor &value);
	tColor & operator *= (tColor &value);
	tColor & operator /= (tColor &value);
	tColor & operator &= (tColor &value);
	tColor & operator |= (tColor &value);
	tColor & operator ^= (tColor &value);

	const tColor operator + (tColor &other) const;
	const tColor operator - (tColor &other) const;
	const tColor operator * (tColor &other) const;
	const tColor operator / (tColor &other) const;
	const tColor operator & (tColor &other) const;
	const tColor operator | (tColor &other) const;
	const tColor operator ^ (tColor &other) const;

	const bool operator ==	(const tColor comp) const;
	const bool operator !=	(const tColor comp) const;
	const bool operator <	(const tColor comp) const;
	const bool operator >	(const tColor comp) const;
	const bool operator <=	(const tColor comp) const;
	const bool operator >=	(const tColor comp) const;

	SDL_Color SDL();

	uint8_t r, g, b, a;
private:
	uint8_t hti(char x, char y);
};

#endif /* WOLF_COLOR_H */
