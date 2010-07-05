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

#include "tCommandLine.h"

/*!
 *	Creates a command line argument
 */	

tCommandLineArg::tCommandLineArg(string value) {
	_value = value;
}

/*!
 *	Returns this element's value
 */	

string tCommandLineArg::value() {
	return _value;
}

/*!
 *	Creates a command entity.
 *  Long name:  --test-option value
 *  Short name: -t value OR -tvalue
 *  Easy Mode:  -t (registers a boolean TRUE)
 */	

tCommandEntity::tCommandEntity(string long_name, string short_name, bool easy) {
	_parsed = false;
	_easy = easy;
	_long_name = long_name;
	_short_name = short_name;
}

bool tCommandEntity::operator == (const tCommandEntity &comp) const {
	return _long_name == comp._long_name;
}

bool tCommandEntity::operator != (const tCommandEntity &comp) const {
	return !(*this == comp);
}

bool tCommandEntity::operator <  (const tCommandEntity &comp) const {
	return _long_name < comp._long_name;
}

bool tCommandEntity::operator >  (const tCommandEntity &comp) const {
	return _long_name > comp._long_name;
}

/*!
 *	Returns the short name of the entity, e.g. -s
 */	

string tCommandEntity::shortName() {
	return _short_name;
}

/*!
 *	Returns the long name of the entity, e.g. --setting-name
 */	

string tCommandEntity::longName() {
	return _long_name;
}

/*!
 *	Returns true if this entity has been parsed.
 */	

bool tCommandEntity::parsed() {
	return _parsed;
}

/*!
 *	Returns the easy mode flag.
 */	

bool tCommandEntity::easy() {
	return _easy;
}

/*!
 *	Sets this entity as parsed.
 */	

void tCommandEntity::parseMe() {
	_parsed = true;
}

/*!
 *	Makes a parser object and command line args.
 */	

tCommandLineParser::tCommandLineParser(int argc, char **argv) {
	parse( argc, argv );
}

/*!
 *	Parses command line args.
 */	

void tCommandLineParser::parse(int argc, char **argv) {
	if( _vec.empty() ) {
		_launch_path = argv[0];
		return;
	}
		
	vector <string> args( argv, argv + argc );
	_launch_path = *args.begin();
	
	for( vector <string>::iterator it = args.begin() + 1; it != args.end(); it++ ) {
		bool this_parsed = false;
		for( tCommandVector::iterator it2 = _vec.begin(); it2 != _vec.end() && !this_parsed; it2++ ) {
			/* Parsed? Skip all of this crap. This ignores all invalid entry. */
			if( it2->parsed() )
				continue;
			
			/* Example: -a8 */
			bool combined = it->find( it2->shortName() ) == 0;
			/* Example: --a-setting 8 or -a 8 */
			bool separated = *it == it2->longName() || *it == it2->shortName();
			
			if( combined && !separated && !it2->parsed() ) {
				if( !it2->easy() )
					_map.insert( make_pair( *it2, tCommandLineArg( it->substr( it2->shortName().length() ) ) ) );
				else
					_map.insert( make_pair( *it2, tCommandLineArg( "1" ) ) );
				
				it2->parseMe();
				this_parsed = true;
			}
			else if( separated && !it2->parsed() ) {
				if( !it2->easy() && it != args.end() - 1 )
					_map.insert( make_pair( *it2, *(++it) ) );
				else if( !it2->easy() && it == args.end() - 1 )
					continue;
				else
					_map.insert( make_pair( *it2, "1" ) );
				
				it2->parseMe();
				this_parsed = true;
			}
		}
	}
	
	args.clear();
}

/*!
 *	Registers a command line option to look out for.
 */	

void tCommandLineParser::addOption(string long_name, string short_name, bool easy) {
	if( long_name.empty() || short_name.empty() || parsed() )
		return;
	if( long_name.find( "--" ) != 0 )
		long_name.assign( "--" + long_name );
	if( short_name.find( "-" ) != 0 )
		short_name.assign( "-" + short_name );
	
	_vec.push_back( tCommandEntity( long_name, short_name, easy ) );
}

/*!
 *	Returns true if the command line has been already parsed.
 */	

bool tCommandLineParser::parsed() {
	return !_launch_path.empty() && !_map.empty() && !_vec.empty();
}

/*!
 *	Returns the traditional launch path of the executable, e.g. argv[0]
 */	

string tCommandLineParser::launchPath() {
	return _launch_path;
}

/*!
 *	Returns the value of the element identified with the long value or an empty string if there's a problem.
 */	

string tCommandLineParser::elementWithKey(string key) {
	if( key.empty() || !parsed() )
		return string();
	if( key.find( "--" ) != 0 )
		key.assign( "--" + key );
	
	tCommandLineMap::iterator it = _map.find( tCommandEntity( key, key, false ) );
	if( it == _map.end() )
		return string();
	return it->second.value();
}
