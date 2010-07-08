/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Prototype for all other files

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

#include "rObject.h"

#ifndef WOLF_WALL_H
#define WOLF_WALL_H

/*!
 *	This class is a test.
 *  Detailed description is in this block.
 */

class rWall : public rObject {
public:
    rWall();
    void setDims(float width, float height, float depth);
    void setTexture(rTexture texture);
protected:
    void setInitialPolys();
    void preRender();
    void render();
    void postRender();
    float _width, _height, _depth;
private:
    rTexture _tex;
};

#endif /* WOLF_PROTOTYPE_H */
