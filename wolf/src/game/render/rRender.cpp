/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Hunter Allen <hunterallen40@gmail.com>
 File Description: Prototype for all other files

 **************************************************************************

 Copyright � 2010 Hunter Alle

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

/*!
 *	This function renders all objects and displays them on the screen.
 *  @param  name A description of the parameter
 *  @return <optional>
 */

void rRender::renderAll() {
    /* Clear the screen */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Load identity */
    //glLoadIdentity();

    /* Move the camera */
    //rPlayerManager::renderAllViewports();

    /* Render everything */
    for( tIDList<rObject*>::iterator it = list()->begin(); it != list()->end(); it++ ) {
        /* Set up a pointer */
        rObject * object = *it;

        /* Push the matrix */
        glPushMatrix();

        /* Call render code */
        object->preRender();
        object->render();
        object->postRender();

        /* Pop the matrix */
        glPopMatrix();
    }

    /* Swap buffers */
    SDL_GL_SwapBuffers();
}

void rRender::pushObject(rObject * object) {
    pushID( object );
}
