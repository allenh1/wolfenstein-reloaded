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

#include "tID.h"

bool tID::operator == (const tID &comp) const {
	return this->_id == comp._id;
}

bool tID::operator != (const tID &comp) const {
	return !(*this == comp);
}

bool tID::operator <  (const tID &comp) const {
	return this->_id < comp._id;
}

bool tID::operator >  (const tID &comp) const {
	return this->_id > comp._id;
}

bool tID::operator <= (const tID &comp) const {
	return this->_id <= comp._id;
}

bool tID::operator >= (const tID &comp) const {
	return this->_id >= comp._id;
}

/*!
 *	Returns the ID.
 */	

uint32_t tID::ID() const {
	return _id;
}

/*!
 *	Sets the ID variable.
 */	

void tID::setID(uint32_t value) {
	_id = value;
}
