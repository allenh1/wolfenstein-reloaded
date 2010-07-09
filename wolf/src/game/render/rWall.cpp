/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Wall rendering code

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

#include "rWall.h"

rWall::rWall() {

}

void rWall::setDims(float width, float height, float depth) {
    _width = fabs( width );
    _height = fabs( height );
    _depth = fabs( depth );
}

void rWall::setTexture(rTexture texture) {
    _tex = texture;
}

void rWall::setInitialPolys() {
    if( _width == 0.0f || _height == 0.0f || _depth == 0.0f )
        return;

    /* Add an assload of vertices */
    rPoly faces[6];
    faces[1].addVertex( rVertex( _coords.xPos(), _coords.yPos(), _coords.zPos() ) );
    faces[1].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos(), _coords.zPos() ) );
    faces[1].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos() + _height, _coords.zPos() ) );
    faces[1].addVertex( rVertex( _coords.xPos(), _coords.yPos() + _height, _coords.zPos() ) );

    faces[2].addVertex( rVertex( _coords.xPos(), _coords.yPos(), _coords.zPos() + _depth ) );
    faces[2].addVertex( rVertex( _coords.xPos(), _coords.yPos() + _height, _coords.zPos() + _depth ) );
    faces[2].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos() + _height, _coords.zPos() + _depth ) );
    faces[2].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos(), _coords.zPos() + _depth ) );

    faces[3].addVertex( rVertex( _coords.xPos(), _coords.yPos() + _height, _coords.zPos() + _depth ) );
    faces[3].addVertex( rVertex( _coords.xPos(), _coords.yPos() + _height, _coords.zPos() ) );
    faces[3].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos() + _height, _coords.zPos() ) );
    faces[3].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos() + _height, _coords.zPos() + _depth ) );

    faces[4].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos(), _coords.zPos() ) );
    faces[4].addVertex( rVertex( _coords.xPos(), _coords.yPos(), _coords.zPos() ) );
    faces[4].addVertex( rVertex( _coords.xPos(), _coords.yPos(), _coords.zPos() + _depth ) );
    faces[4].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos(), _coords.zPos() + _depth ) );

    faces[5].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos(), _coords.zPos() + _depth ) );
    faces[5].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos() + _height, _coords.zPos() + _depth ) );
    faces[5].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos() + _height, _coords.zPos() ) );
    faces[5].addVertex( rVertex( _coords.xPos() + _width, _coords.yPos(), _coords.zPos() ) );

    faces[6].addVertex( rVertex( _coords.xPos(), _coords.yPos(), _coords.zPos() + _depth ) );
    faces[6].addVertex( rVertex( _coords.xPos(), _coords.yPos(), _coords.zPos() ) );
    faces[6].addVertex( rVertex( _coords.xPos(), _coords.yPos() + _height, _coords.zPos() ) );
    faces[6].addVertex( rVertex( _coords.xPos(), _coords.yPos() + _height, _coords.zPos() + _depth ) );

    /* Define the polygons */
    for( size_t a = 1; a <= 6; a++ )
        _polys.push_back( faces[a] );
}

void rWall::preRender() {

}

void rWall::render() {
    /* Set the color */
    glColor4b( _color.r, _color.g, _color.b, _color.a );

    /* Go through all polys */
    for( vector <rPoly>::iterator it = _polys.begin(); it != _polys.end(); it++ )
    {
        /* Make pointer to a vector */
        vector <rVertex> * vertices = it->vertices();

        /* Texture coordinate index */
        size_t x = 0;

        /* Bind the texture */
        //glBindTexture( GL_TEXTURE_2D, _tex.textureID() );

        /* Start a quad */
        glBegin( GL_QUADS );

        /* Draw all vertices */
        for( vector <rVertex>::iterator ti = vertices->begin(); ti != vertices->end(); ti++ )
        {
            /* Set the texture coordinates */
            //glTexCoord2f( texCoords[x++], texCoords[x++] );

            /* Make a vertex */
            float x = ti->xPos();
            float y = ti->yPos();
            float z = ti->zPos();
            glVertex3f( x, y, z );
        }

        /* End the polygon */
        glEnd();
    }
}

void rWall::postRender() {

}
