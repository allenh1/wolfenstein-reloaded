/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: The entry point for the network thread.
 
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

#include "nMain.h"

/* The game thread */
namespace Net { Main::mThread nMain( Net::nSetup, Net::nLoop, Net::nCleanup, Net::nWatchdogTimer ); }

/*!
 *	Sets up the network thread.
 */

void Net::nSetup()
{
	cout << "Hello from the network thread!" << endl;
}

/*!
 *	Cleans up the network thread.
 */

void Net::nCleanup()
{
	cout << "Goodbye from the network thread!" << endl;
}

/*!
 *	The network loop.
 */

int Net::nLoop(void * data)
{
	/* Return variable */
	int ret = 0;
	
	/* Network loop */
	while( !rbi( nMain.opts(), THREAD_STOP_BIT ) && !rbi( nMain.opts(), THREAD_KILL_BIT ) )
	{
		/* Main loop code here... */
		
		/* Kick the watchdog */
		nMain.kick();
	}
	
	/* Return */
	return ret;
}
