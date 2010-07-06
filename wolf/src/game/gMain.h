/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: The entry point for the game thread.

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

#include "mThread.h"
#include "tDirectories.h"
#include "tRandom.h"
#include "rScreen.h"
#include "rRender.h"

#ifndef WOLF_GAME_MAIN_H
#define WOLF_GAME_MAIN_H

namespace Game {

	/* Functions */
	void gSetup();
	void gCleanup();
	int gLoop(void * data);

	/* Watchdog timer */
	const uint16_t gWatchdogTimer = 3000;

}

#endif /* WOLF_GAME_MAIN_H */
