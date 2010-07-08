/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Screen abstraction class

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

#include "rScreen.h"

uint32_t rScreen::_width, rScreen::_height, rScreen::_depth, rScreen::_vflags, rScreen::_fullScreen;
SDL_Surface * rScreen::_screen = NULL;
const SDL_VideoInfo * rScreen::_videoInfo;

void rScreen::initDisplay(uint32_t width, uint32_t height, uint32_t depth, bool fullScreen) {
    /* Set variables */
    _width = width;
    _height = height;
    _depth = depth;
    _fullScreen = fullScreen;

    /* Set GL attributes */
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	_videoInfo = SDL_GetVideoInfo();

    if ( !_videoInfo ) {
		cerr << "SDL Error: Error getting video info: " << SDL_GetError() << endl;
		exit( EXIT_FAILURE );
	}

	/* SDL video flags */
    _vflags = SDL_OPENGL | SDL_HWPALETTE;

    /* Can we store surfaces in graphics memory? GPU accelerate it! */
    if( _videoInfo->hw_available )
		_vflags |= SDL_HWSURFACE;
    else
		_vflags |= SDL_SWSURFACE;

    /* Can we do hardware blits? */
    if( _videoInfo->blit_hw )
		_vflags |= SDL_HWACCEL;

	/* Fullscreen? */
	if( _fullScreen )
		_vflags |= SDL_FULLSCREEN;

    /* Optionally free the surface if we're changing the video mode */
    if( _screen )
        SDL_FreeSurface( _screen );

    /* Set the surface */
    _screen = SDL_SetVideoMode( _width, _height, 0, _vflags );

	if( _screen == NULL ) {
		cerr << "SDL Error: Setting video mode failed: " << SDL_GetError() << endl;
		exit( EXIT_FAILURE );
	}

	/* OpenGL setup: Clear color and depth buffers */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth( 1.0f );

	/* OpenGL setup: glEnable calls */
    glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glEnable( GL_TEXTURE_2D );

	/* OpenGL setup: GL perspective correction and other cool stuff */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glDepthFunc( GL_LESS );
	glShadeModel( GL_SMOOTH );

    /* OpenGL setup: Finish clearing the screen */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* OpenGL setup: GL perspective */
	glViewport( 0, 0, (GLsizei)width, (GLsizei)height );
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0f, (float)width / (float)height, 1.0f, 200.0f );
    glMatrixMode( GL_MODELVIEW );
}

void rScreen::releaseDisplay() {
    if( _screen )
    {
        SDL_FreeSurface( _screen );
        _screen = NULL;
    }
}
