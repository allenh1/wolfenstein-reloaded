/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Utility classes for managing IDs and lists of IDs
 
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

#include <list>
#include <memory>
#include <utility>
#include <algorithm>

#ifndef WOLF_ID_H
#define WOLF_ID_H

/*!
 *	Maintains an ID variable. Derive stuff from this class.
 */	

class tID {
public:
	bool operator == (const tID &comp) const;
	bool operator != (const tID &comp) const;
	bool operator <	 (const tID &comp) const;
	bool operator >	 (const tID &comp) const;
	bool operator <= (const tID &comp) const;
	bool operator >= (const tID &comp) const;
	uint32_t ID() const;
	void setID(uint32_t value);
protected:
	uint32_t _id;
};

/*!
 *	An expandable list designed to store objects derived from tID.
 */	

template <typename T> class tIDList : public list <T> {
public:
private:
};

/*!
 *	Manages a list of IDs.
 */	

template <typename T> class tIDManager {
public:
	static uint32_t numIDs()		{ return list()->size(); }
	static uint32_t lastID()		{ return _last_id; }
protected:
	static tIDList <T*> * list()	{ if( !_ids ) { static tIDList <T*> temp; _ids = &temp; } return _ids; }
	static void pushID(T* newID)	{ newID->setID( _last_id++ ); list()->push_back( newID ); }
	static void popID()				{ list()->pop_back(); _last_id++; }
	static void deleteID(T* ID)		{ list()->remove( ID ); _last_id++; }
	static void clearIDs()			{ list()->clear(); _last_id = 0; }
private:
	static uint32_t _last_id;
	static tIDList <T*> *_ids;
};

/* Recursive derivation: warning - weird syntax */
template <typename T> tIDList <T*> *tIDManager <T>::_ids = NULL;
template <typename T> uint32_t tIDManager <T>::_last_id = 0;

/*!
 *	Maintains a list of LOCAL IDs.
 */	

template <typename T> class tLIDManager {
public:
	uint32_t numIDs()		{ return list()->size(); }
	uint32_t lastID()		{ return _last_id; }
protected:
	tIDList <T*> * list()	{ return &_ids; }
	void pushID(T* newID)	{ list()->push_back( newID ); newID->setID( _last_id++ ); }
	void popID()			{ list()->pop_back(); _last_id++; }
	void deleteID(T* ID)	{ list()->remove( ID ); _last_id++; }
	void clearIDs()			{ list()->clear(); _last_id = 0; }
private:
	tIDList <T*> _ids;
	uint32_t _last_id;
};

/*!
 *	Manages a list of LOCAL IDs. Same as tLIDManager.
 */	

template <typename T> class tLIDManager1 {
public:
	uint32_t numIDs1()		{ return List1()->size(); }
	uint32_t lastID1()		{ return _last_id1; }
protected:
	tIDList <T*> * List1()	{ return &_ids1; }
	void pushID1(T* newID)	{ List1()->push_back( newID ); newID->setID( _last_id1++ ); }
	void popID1()			{ List1()->pop_back(); _last_id1++; }
	void deleteID1(T* ID)	{ List1()->remove( ID ); _last_id1++; }
	void clearIDs1()		{ List1()->clear(); _last_id1 = 0; }
private:
	tIDList <T*> _ids1;
	uint32_t _last_id1;
};

/*!
 *	Manages a list of LOCAL IDs. Same as tLIDManager.
 */	

template <typename T> class tLIDManager2 {
public:
	uint32_t numIDs2()		{ return List2()->size(); }
	uint32_t lastID2()		{ return _last_id2; }
protected:
	tIDList <T*> * List2()	{ return &_ids2; }
	void pushID2(T* newID)	{ List2()->push_back( newID ); newID->setID( _last_id2++ ); }
	void popID2()			{ List2()->pop_back(); _last_id2++; }
	void deleteID2(T* ID)	{ List2()->remove( ID ); _last_id2++; }
	void clearIDs2()		{ List2()->clear(); _last_id2 = 0; }
private:
	tIDList <T*> _ids2;
	uint32_t _last_id2;
};

#endif /* WOLF_ID_H */
