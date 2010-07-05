/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Pseudo-random number generation class
 
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

#include <RandomLib/Random.hpp>
#include <string>

#ifndef WOLF_RANDOM_H
#define WOLF_RANDOM_H

/*!
 *	Generates pseudo-random numbers.
 */	

class tRandomizer : private RandomLib::Random {
public:
	tRandomizer();
	float get();
	int get(int max);
	int get(int min, int max);
	string randomString(size_t length, const char * safe_characters = NULL);
	void reseed();
	static tRandomizer & getInstance();
};

#endif /* WOLF_RANDOM_H */
