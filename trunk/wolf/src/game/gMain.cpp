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

#include "gMain.h"

/* The game thread */
namespace Game { static Main::mThread gMain( Game::gSetup, Game::gLoop, Game::gCleanup, Game::gWatchdogTimer ); }

/*!
 *	Sets up the game thread.
 */

void Game::gSetup()
{
	rScreen::initDisplay( 1024, 768, 32, false );
}

/*!
 *	Cleans up the game thread.
 */

void Game::gCleanup()
{
	cout << "Goodbye from the game thread!" << endl;
}

/*!
 *	The game loop.
 */

int Game::gLoop(void * data)
{
	/* Return variable */
	int ret = 0;

	/* Network loop */
	while( !rbi( gMain.opts(), THREAD_STOP_BIT ) && !rbi( gMain.opts(), THREAD_KILL_BIT ) )
	{
		/* Main loop code here... */
        rRender::renderAll();

		/* Kick the watchdog */
		gMain.kick();
	}

	/* Return */
	return ret;
}
