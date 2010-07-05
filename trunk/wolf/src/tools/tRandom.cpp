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

#include "tRandom.h"

/*!
 *	Initializes and reseeds the global randomizer.
 */	

tRandomizer::tRandomizer() {
	Reseed();
}

/*!
 *	Returns a pseudo-random floating point number.
 */	

float tRandomizer::get() {
	return FixedN <float> ();
}

/*!
 *	Returns a psuedo-random integer in [0, max]
 */	

int tRandomizer::get(int max) {
	return IntegerC <int> ( max );
}

/*!
 *	Returns a psuedo-random integer in [min, max]
 */	

int tRandomizer::get(int min, int max) {
	return IntegerC <int> ( min, max );
}

/*!
 *	Makes a pseudo-random string with the given length and acceptable characters.
 *  If the second parameter is NULL, we return a random ASCII human-readable character, excluding spaces.
 */	

string tRandomizer::randomString(size_t length, const char * safe_characters) {
	/* Initialize the return-string */
	string ret;
	ret.reserve( length );
	
	if( !safe_characters ) {
		/* Return a random ASCII human-readable character, excluding spaces */
		for( size_t a = 0; a < length; a++ )
			ret.append( 1, IntegerC <char> ( 0x21, 0x7e ) );
	}
	else {
		/* Return a random character from safe_characters */
		size_t safe_length = strlen( safe_characters );
		for( size_t a = 0; a < length; a++ )
			ret.append( 1, safe_characters[Integer <size_t> ( safe_length )] );
	}
	return ret;
}

/*!
 *	Reseeds and checks the random engine.
 */	

void tRandomizer::reseed() {
	/* Reseed the generator. */
	Global.Reseed();
	
	/* Run the built-in self-check. */
	try { RandomLib::SRandomGenerator32::SelfTest(); }
	catch (std::out_of_range& e) { cerr << "Mersenne Twister generator failed test: " << e.what() << endl; }	
	
	/* Run a sanity check by comparing the actual to the predicted. Warn if it's wrong. */
	RandomLib::SRandomGenerator32 s( "0x1234,0x5678,0x9abc,0xdef0" );
	s.SetCount( 999 );
	if( s() != 0x2eff7539 ) /* magic number... don't change or tests WILL fail */
		cerr << "Mersenne Twister generator failed test: sanity check failed" << endl;
}

/*!
 *	Gets an instance of the global public randomizer.
 */	

tRandomizer & tRandomizer::getInstance() {
	static tRandomizer randomizer;
    return randomizer;
}
