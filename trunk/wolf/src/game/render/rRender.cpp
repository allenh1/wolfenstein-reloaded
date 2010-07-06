/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Hunter Allen <hunterallen40@gmail.com>
 File Description: Prototype for all other files

 **************************************************************************

 Copyright © 2010 Hunter Alle

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


#include "rRender.h"

list <rObject*> rRender::_objects;

/*!
 *	This function renders all objects and displays them on the screen.
 *  @param  name A description of the parameter
 *  @return <optional>
 */

void rRender::renderAll()
{
    for( list<rObject*>::iterator it = _objects.begin(); it != _objects.end(); it++ ) {
        (*it)->preRender();
        (*it)->render();
        (*it)->postRender();
    }
}

