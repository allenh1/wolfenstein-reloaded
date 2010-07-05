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

#include "defs.h"

#include "tDirectories.h"
#include "tXML.h"

#ifndef WOLF_RESOURCE_H
#define WOLF_RESOURCE_H

/* Resource type enumeration */
typedef enum { tLocaleResource, tAutoResource, tInvalidResource } tResourceType;

/* Resource exception enumeration */
typedef enum { tInvalidDirectory, tMissingInventoryFile, tNoResourceData } tResourceExceptionType;

/*!
 *	Abstracts a Wolfenstrin resource type
 */	

class tResource {
public:
	tResource(tResourceType type = tAutoResource);
	tResource(tDirectoryBase * dir, tResourceType type = tAutoResource);
	tResourceType type();
	void loadResource(tDirectoryBase * dir, tResourceType type = tAutoResource);
protected:
	void load();
private:
	tResourceType _type;
	tDirectoryBase * _dir;
};

const char tResourceXMLSuffix[] = "-inventory.xml";

#endif /* WOLF_RESOURCE_H */
