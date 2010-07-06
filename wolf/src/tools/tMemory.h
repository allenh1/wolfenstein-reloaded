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

#include <memory>

#ifndef WOLF_MEMORY_H
#define WOLF_MEMORY_H

/*!
 *	Simple automatic pointer and the size.
 */

template <typename T> struct tPointer {
    tPointer()
    {
        memory = auto_ptr <T> ();
        size = 0;
    }

    tPointer(auto_ptr <T> new_memory, size_t new_size)
    {
        memory = new_memory;
        size = new_size;
    }
	auto_ptr <T> memory;
	size_t size;
};

#endif /* WOLF_MEMORY_H */
