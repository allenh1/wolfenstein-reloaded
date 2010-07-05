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

#include "defs.h"

#include "mThread.h"
#include "tDirectories.h"

#ifndef WOLF_NET_MAIN_H
#define WOLF_NET_MAIN_H

namespace Net {
	
	/* Functions */
	void nSetup();
	void nCleanup();
	int nLoop(void * data);
	
	/* Watchdog timer */
	const uint16_t nWatchdogTimer = 6000;
	
}

#endif /* WOLF_NET_MAIN_H */
