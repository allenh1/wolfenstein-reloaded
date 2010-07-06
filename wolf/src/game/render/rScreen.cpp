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

rScreen::rScreen() {
    _width = _height = _depth = 0;
    _fullScreen = false;
    _screen = NULL;
}

rScreen::rScreen(uint32_t width, uint32_t height, uint32_t depth, bool fullScreen) {
    _width = width;
    _height = height;
    _depth = depth;
    _fullScreen = fullScreen;
    _screen = NULL;
}

void rScreen::initDisplay(uint32_t width, uint32_t height, uint32_t depth, bool fullScreen) {
    /* Set GL attributes */
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, depth );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, depth );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	_videoInfo = SDL_GetVideoInfo();

    if ( !_videoInfo )
	{
		cerr << "SDL Error: Error getting video info: " << SDL_GetError() << endl;
		exit( EXIT_FAILURE );
	}

	/* SDL video flags */
    _vflags  = SDL_OPENGL | SDL_HWPALETTE;

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

    /* Set the surface */
	_screen = SDL_SetVideoMode( _width, _height, _depth, _vflags );

	if( _screen == NULL )
	{
		cerr << "SDL Error: setting video mode: " << SDL_GetError() << endl;
		exit( EXIT_FAILURE );
	}

	// Start setting up GL stuff
}
