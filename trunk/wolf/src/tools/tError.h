/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Error handling functions
 
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

#include <string>
#include <sstream>
#include <exception>

#ifndef WOLF_ERROR_H
#define WOLF_ERROR_H

typedef enum { tAssertion, tWarning, tFatal } tErrorType;

void PresentError(const char * message, const char * file, const char * function, uint32_t line, uint32_t thread, tErrorType type);

#define tASSERT( x ) \
if ( !( x ) ) \
PresentError( #x, __FILE__, __PRETTY_FUNCTION__, __LINE__, SDL_ThreadID(), tAssertion )

#endif /* WOLF_ERROR_H */
