/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Configuration manager
 
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

#include "tResource.h"

tResource::tResource(tResourceType type) {
	_type = type;
}

tResource::tResource(tDirectoryBase * dir, tResourceType type) {
	loadResource( dir, type );
}

tResourceType tResource::type() {
	return _type;
}

void tResource::loadResource(tDirectoryBase * dir, tResourceType type) {
	_type = type;
	_dir  = dir;
	
	load();
}

void tResource::load() {
	/* Check to make sure it's not NULL */
	if( !_dir ) {
		_type = tInvalidResource;
		return;
	}
	
	/* Open it */
	try {
		if( !_dir->Good() )
			_dir->openMe();
		throw _dir->Good() && _dir;
	}
	catch( bool good ) {
		if( !good ) {
			_type = tInvalidResource;
			return;
		}
	}
	
	/* Load inventory XML */
	tFile * inventory = _dir->fileWithName( _dir->name() + string( tResourceXMLSuffix ) );
	
	/* Not there */
	if( !inventory ) {
		_type = tInvalidResource;
		return;
	}
	
	/* Open it */
	try {
		if( !inventory->is_open() || !inventory->good() )
			inventory->openMe();
		throw inventory->good() && inventory->is_open() && inventory;
	}
	catch( bool good ) {
		if( !good ) {
			_type = tInvalidResource;
			return;
		}
	}
	
	/* Load/parse the inventory XML file */
	tXML xml( inventory );
}