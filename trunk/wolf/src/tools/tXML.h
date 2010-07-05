/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: XML parser classes
 
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

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <cstdarg>
#include <vector>

#ifndef WOLF_XML_H
#define WOLF_XML_H

/*!
 *	Vector of XML stuff
 */	

typedef vector <string> tXMLVector;

/*!
 *	Abstracts an XML file
 */	

class tXML {
public:
	tXML();
	tXML(tFile * doc);
	~tXML();
	void load(tFile * doc);
	void release();
	tXMLVector getPropertyValuesFor(string property_name, int num_nodes, ...);
	tXMLVector getPropertyValuesForInternal(string property_name, xmlNode * base, tXMLVector args);
	tXMLVector getInnerXMLFor(int num_nodes, ...);
	tXMLVector getInnerXMLForInternal(xmlNode * base, tXMLVector args);
private:
	xmlDoc  * _tree;
	xmlNode * _root;
};

#endif /* WOLF_XML_H */
