/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Base class for game objects

 **************************************************************************

 Copyright © 2010 Morgan Jones, Hunter Allen

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

#include <vector>

#include "tSDL.h"
#include "tSSL.h"
#include "tGL.h"
#include "tID.h"
#include "tColor.h"
#include "tDirectories.h"

#ifndef WOLF_OBJECT_H
#define WOLF_OBJECT_H

/*!
 *	This class handles vertices.
 */

class rVertex {
public:
    rVertex();
    rVertex(int32_t x, int32_t y, int32_t z);
    void setCoords(int32_t x, int32_t y, int32_t z);
    int32_t xPos(), yPos(), zPos();
private:
    int32_t _x, _y, _z;
 };

/*!
 *	This class is a texture.
 */

class rTexture {
public:
    rTexture();
    rTexture(tFile * file);
    GLuint textureID();
    void load();
    void load(tFile * file);
private:
    GLuint _texid;
    tFile * _file;
 };

/*!
 *	This class is a polygon.
 */

class rPoly {
public:
    rPoly();
    rPoly(rTexture texture);
    void addVertex(rVertex vertex);
    void setTexture(rTexture texture);
    void changeVisibility(bool visibility);
    rTexture texture();
    bool isVisible();
private:
    vector <rVertex> _vertices;
    rTexture _texture;
    bool _visible;
 };

/*!
 *	This class handles objects in the game.
 */

class rObject : public tID {
    rObject();
    rObject(rVertex coords);
    void addPoly(rPoly poly);
    void setCoords(rVertex coords);
private:
    rVertex _coords;
    vector <rPoly> _polys;
};

#endif /* WOLF_OBJECT_H */
