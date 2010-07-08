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
	rScreen::initDisplay( 640, 480, 32, false );
	rWall * wall = new rWall;
	rPlayer * player = new rPlayer;
	wall->setDims( 10, 10, 10 );
	wall->setCoords( rPoint( 20, 20, 20 ) );
	wall->setColor( tColor( 255, 255, 255 ) );
	wall->recalcPolys();

	rRender::pushObject( wall );
	rPlayerManager::addPlayer( player );
}

/*!
 *	Cleans up the game thread.
 */

void Game::gCleanup()
{
	rScreen::releaseDisplay();
}

/*!
 *	The game loop.
 */

int Game::gLoop(void * data)
{
	/* Return variable */
	int ret = 0;

	/* Game loop */
	while( !rbi( gMain.opts(), THREAD_STOP_BIT ) && !rbi( gMain.opts(), THREAD_KILL_BIT ) )
	{
		/* Render everything */
        rRender::renderAll();

		/* Kick the watchdog */
		gMain.kick();
	}

	/* Return */
	return ret;
}
