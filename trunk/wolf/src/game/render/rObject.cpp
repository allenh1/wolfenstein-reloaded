/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>, Hunter Allen <hunterallen40@gmail.com>
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

#include "rObject.h"

rPoint::rPoint() {
    _x = _y = _z = 0;
}

rPoint::rPoint(float x, float y, float z) {
    setCoords( x, y, z );
}

void rPoint::setCoords(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
}

float rPoint::xPos() {
    return _x;
}

float rPoint::yPos() {
    return _y;
}

float rPoint::zPos() {
    return _z;
}

rTexture::rTexture() {
    _texid = 0;
    _file = NULL;
}

rTexture::rTexture(tFile * file) {
    _texid = 0;
    _file = file;
}

GLuint rTexture::textureID() {
    return _texid;
}

void rTexture::load() {
    if( _file == NULL )
        return;

    /* Variables */
    char * data = NULL;
    size_t length = 0;
    GLuint format = 0;
    SDL_RWops * rw = NULL;
    SDL_Surface * temp = NULL, *surface = NULL;
    bool freeIt = true;

    /* Get data and load it into SDL */
    data = _file->data( length );

    /* Read/write from memory */
    if( data != NULL )
        rw = SDL_RWFromMem( data, length );
    else
        rw = NULL;

    /* Load it as an SDL_Surface */
    temp = IMG_Load_RW( rw, 1 );

    /* Check the image. If the surface is NULL, the image won't work. Fill it with white. */
    if( temp == NULL )
    {
        temp = SDL_CreateRGBSurface( SDL_SWSURFACE, 64, 64, 32, 0, 0, 0, 0 );
        if( temp == NULL )
        {
            cerr << "Fallback failed: File " << _file->path().leaf() << " failed to load (surface creation error)." << endl;
            return;
        }

        if( SDL_FillRect( temp, NULL, 0xffffffff ) != 0 )
        {
            cerr << "Fallback failed: File " << _file->path().leaf() << " failed to load (rectangle filling error)." << endl;
            return;
        }
    }

    /* Normalize image */
    surface = SDL_DisplayFormat( temp );

    /* If the normalization doesn't work, use the old one. */
    if( surface == NULL )
    {
        surface = temp;
        surface->refcount++;
        freeIt = false;
    }

    /* Free memory */
    if( data )
    {
        delete[] data;
        data = NULL;
    }
    if( temp && freeIt )
    {
        SDL_FreeSurface( temp );
        temp = NULL;
    }

    /* Set texture parameters */
    glBindTexture( GL_TEXTURE_2D, _texid );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    /* Determine pixel format */
    if( surface->format->BitsPerPixel == 32 )
        format = GL_RGBA;
    else
        format = GL_RGB;

    /* Make the texture - finally */
    SDL_LockSurface( surface );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, format, GL_BYTE, surface->pixels );
    SDL_UnlockSurface( surface );

    /* Free the surface */
    if( surface )
    {
        SDL_FreeSurface( surface );
        surface = NULL;
    }
}

void rTexture::load(tFile * file) {
    _file = file;
    load();
}

rPoly::rPoly() {
    _visible = true;
}

rPoly::rPoly(rTexture texture) {
    _visible = true;
    setTexture( texture );
}

void rPoly::addVertex(rVertex vertex) {
    _vertices.push_back( vertex );
}

void rPoly::setTexture(rTexture texture) {
    _texture = texture;
}

void rPoly::changeVisibility(bool visibility) {
    _visible = visibility;
}

rTexture rPoly::texture() {
    return _texture;
}

bool rPoly::isVisible() {
    return _visible;
}

vector <rVertex> rPoly::vertices() {
    return _vertices;
}

rObject::rObject() {
    _coords.setCoords( 0, 0, 0 );
}

rObject::rObject(rPoint coords) {
    setCoords( coords );
}

void rObject::addPoly(rPoly poly) {
    _polys.push_back( poly );
}

void rObject::setCoords(rPoint coords) {
    _coords = coords;
}

void rObject::setColor(tColor color) {
    _color = color;
}

void rObject::recalcPolys() {
    vector <float> xBag;
    vector <float> yBag;
    vector <float> zBag;
    for( vector <rPoly>::iterator it = _polys.begin(); it != _polys.end(); it++ )
    {
        vector <rVertex> vertices = it->vertices();
        for( vector <rVertex>::iterator ti = vertices.begin(); ti != vertices.end(); ti++ )
        {
            xBag.push_back( ti->xPos() );
            yBag.push_back( ti->yPos() );
            zBag.push_back( ti->zPos() );
        }
    }
    float max_x = *max_element( xBag.begin(), xBag.end() );
    float max_y = *max_element( yBag.begin(), yBag.end() );
    float max_z = *max_element( zBag.begin(), zBag.end() );
    float min_x = *min_element( xBag.begin(), xBag.end() );
    float min_y = *min_element( yBag.begin(), yBag.end() );
    float min_z = *min_element( zBag.begin(), zBag.end() );
    _ctr = rVertex( max_x - (max_x - min_x) / 2.0, max_y - (max_y - min_y) / 2.0, max_z - (max_z - min_z) / 2.0 );
    _max = rVertex( max_x, max_y, max_z );
    _min = rVertex( min_x, min_y, min_z );
}
