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

void rWall::preRender() {

}

void rWall::render() {
    /* Set the color */
    glColor4b( _color.r, _color.g, _color.b, _color.a );

    /* Front Face */
    glBindTexture( GL_TEXTURE_2D, front->TexID() );


    /* Start the quad */
    glBegin( GL_QUADS );

    /* Bottom Left Of The Texture and Quad */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( _position.xP, Y(), Z() );
    /* Bottom Right Of The Texture and Quad */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( X() + Width(), Y(), Z() );
    /* Top Right Of The Texture and Quad */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( X() + Width(), Y() + Height(), Z() );
    /* Top Left Of The Texture and Quad */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( X(), Y() + Height(), Z() );

    /* Finish the quad */
    glEnd();

	/* Back Face */
    glBindTexture( GL_TEXTURE_2D, back->TexID() );


    /* Start the quad */
    glBegin( GL_QUADS );

    /* Bottom Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( X(), Y(), Z() + Depth() );
    /* Top Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( X(), Y() + Height(), Z() + Depth() );
    /* Top Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( X() + Width(), Y() + Height(), Z() + Depth() );
    /* Bottom Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( X() + Width(), Y(), Z() + Depth() );

    /* Finish the quad */
    glEnd();

	/* Top Face */
    glBindTexture( GL_TEXTURE_2D, top->TexID() );


    /* Start the quad */
    glBegin( GL_QUADS );

    /* Top Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( X(), Y() + Height(), Z() + Depth() );
    /* Bottom Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( X(), Y() + Height(), Z() );
    /* Bottom Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( X() + Width(), Y() + Height(), Z() );
    /* Top Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( X() + Width(), Y() + Height(), Z() + Depth() );

    /* Finish the quad */
    glEnd();

	/* Bottom Face */
    glBindTexture( GL_TEXTURE_2D, bottom->TexID() );


    /* Start the quad */
    glBegin( GL_QUADS );

    /* Top Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( X() + Width(), Y(), Z() );
    /* Top Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( X(), Y(), Z() );
    /* Bottom Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( X(), Y(), Z() + Depth() );
    /* Bottom Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( X() + Width(), Y(), Z() + Depth() );

    /* Finish the quad */
    glEnd();

	/* Right Face */
    glBindTexture( GL_TEXTURE_2D, right->TexID() );


    /* Start the quad */
    glBegin( GL_QUADS );

    /* Bottom Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( X() + Width(), Y(), Z() + Depth() );
    /* Top Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( X() + Width(), Y() + Height(), Z() + Depth() );
    /* Top Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( X() + Width(), Y() + Height(), Z() );
    /* Bottom Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( X() + Width(), Y(), Z() );

    /* Finish the quad */
    glEnd();

	/* Left Face */
    glBindTexture( GL_TEXTURE_2D, left->TexID() );


    /* Start the quad */
    glBegin( GL_QUADS );

    /* Bottom Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( X(), Y(), Z() + Depth() );
    /* Bottom Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f( X(), Y(), Z() );
    /* Top Right Of The Texture and Quad */
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f( X(), Y() + Height(), Z() );
    /* Top Left Of The Texture and Quad */
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( X(), Y() + Height(), Z() + Depth() );

    /* Finish the quad */
    glEnd();
}

void rWall::postRender() {

}
