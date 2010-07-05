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

#include "tXML.h"

tXML::tXML() {
	_tree = NULL;
	_root = NULL;
}

tXML::tXML(tFile * doc) {
	_tree = NULL;
	_root = NULL;
	load( doc );
}

tXML::~tXML() {
	release();
}

void tXML::load(tFile * doc) {	
	if( _tree )
		return;
	
	/* Parse */
	_tree = xmlReadFile( doc->path().string().c_str(), NULL, 0x00 );
	if( !_tree ) {
		cerr << "Failed to parse " << doc->path().leaf() << endl;
		return;
	}
	
	/* Root element */
	_root = xmlDocGetRootElement( _tree );
	if( !_root ) {
		cerr << "No root element for " << doc->path().leaf() << endl;
		release();
		return;
	}
}

void tXML::release() {
	if( _tree ) {
		xmlFreeDoc( _tree );
		_tree = NULL;
		_root = NULL;
	}
}

tXMLVector tXML::getPropertyValuesFor(string property_name, int num_nodes, ...) {
	va_list args;
	tXMLVector arg_vector;
	va_start( args, num_nodes );
	for( int a = 0; a < num_nodes; a++ )
		arg_vector.push_back( va_arg( args, const char * ) );
	va_end( args );
	
	return getPropertyValuesForInternal( property_name, _root, arg_vector );
}

tXMLVector tXML::getPropertyValuesForInternal(string property_name, xmlNode * base, tXMLVector args) {
	/* Start it out */
	string str, arg = *args.begin();
	tXMLVector ret;
	tXMLVector::iterator it = args.begin();
	xmlNode * cur_node = base;
	
	/* Recurse through the nodes */
	while( cur_node ) {
		if( string( (const char *)cur_node->name ) == arg && cur_node->type == XML_ELEMENT_NODE ) {
			/* Get the children if we need to */
			if( it != args.end() )
			{
				/* Increment it */
				it++;
				
				/* Recurse if necessary */
				if( it != args.end() )
				{
					/* Set the pointer */
					cur_node = cur_node->children;
					
					/* Set the arg, move on */
					arg = *it;
					continue;
				}
			}
			
			/* Was this the last node in the array? Find the property! */
			if( it == args.end() ) {
				bool found = false;
				for( xmlAttr * cur_attr = cur_node->properties; cur_attr; cur_attr = cur_attr->next ) {
					if( string( (const char *)cur_attr->name ) == property_name ) /* match */ {
						/* Check the match */
						if( cur_attr && cur_attr->children && cur_attr->children->content )
							ret.push_back( (const char *)cur_attr->children->content );
						else
							ret.push_back( string() );
						
						/* GTFO */
						found = true;
						break;
					}
				}
				if( !found ) /* Not in this tag. Add a blank string. */
					ret.push_back( string() );
			}
		}
		
		/* Move on */
		if( cur_node )
			cur_node = cur_node->next;
	}
	
	/* Goodbye */
	return ret;	
}

tXMLVector tXML::getInnerXMLFor(int num_nodes, ...) {
	va_list args;
	tXMLVector arg_vector;
	va_start( args, num_nodes );
	for( int a = 0; a < num_nodes; a++ )
		arg_vector.push_back( va_arg( args, const char * ) );
	va_end( args );
	return getInnerXMLForInternal( _root, arg_vector );
}

tXMLVector tXML::getInnerXMLForInternal(xmlNode * base, tXMLVector args) {
	/* Start it out */
	string str, arg = *args.begin();
	tXMLVector ret;
	tXMLVector::iterator it = args.begin();
	xmlNode * cur_node = base;
	
	/* Recurse through the nodes */
	while( cur_node ) {
		if( string( (const char *)cur_node->name ) == arg && cur_node->type == XML_ELEMENT_NODE ) {
			/* Get the children if we need to */
			if( it != args.end() ) {
				/* Increment it */
				it++;
				
				/* Recurse if necessary */
				if( it != args.end() )
				{
					/* Set the pointer */
					cur_node = cur_node->children;
					
					/* Set the arg, move on */
					arg = *it;
					continue;
				}
			}
			
			/* Was this the last node in the array? Get the inner XML. */
			if( it == args.end() ) {
				if( cur_node->children && cur_node->children->content )
					ret.push_back( (const char *)cur_node->children->content );
				else
					ret.push_back( string() );
			}
		}
		
		/* Move on */
		if( cur_node )
			cur_node = cur_node->next;
	}
	
	/* Goodbye */
	return ret;		
}