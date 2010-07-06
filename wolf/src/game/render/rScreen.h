/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Screen management

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

#include "tSDL.h"

#ifndef WOLF_SCREEN_H
#define WOLF_SCREEN_H

/*!
 *	This class manages one screen.
 */

class rScreen {
public:
    rScreen();
    rScreen(uint32_t width, uint32_t height, uint32_t depth, bool fullScreen);
    void initDisplay(uint32_t width, uint32_t height, uint32_t depth, bool fullScreen);
private:
    uint32_t _width, _height, _depth, _vflags, _fullScreen;
    SDL_Surface * _screen;
    const SDL_VideoInfo *_videoInfo;
};

static rScreen rApplicationScreen;

#endif /* WOLF_PROTOTYPE_H */
