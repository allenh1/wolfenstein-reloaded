/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Global definitions

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

 Coding Log:
 1823 lines of code as of July 7, 2009 4:30 PM
 2224 lines of code as of July 9, 2009 3:46 PM
 2749 lines of code as of July 21, 2009 8:01 PM: Added to SVN

 **************************************************************************

 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <stdint.h>

/* Compiler defines */
#if defined(__APPLE__) || defined(TARGET_OS_MAC)
#define MACOSX 1
#define SNOW_LEOPARD 1
#elif defined(linux) || defined(__linux__) || defined(__LINUX__) || defined(TARGET_OS_UNIX)
#define LINUX 1
#elif defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64) || defined(TARGET_OS_WIN32)
#define WINDOWS 1
#endif

#if defined(MACOSX) /* Mac specific defines */
#include <unistd.h>
#elif defined(WINDOWS) /* Windows specific defines */
#include <windows.h>
#include <winbase.h>
#elif defined(LINUX) /* Linux specific defines */
#include <unistd.h>
#endif

/* Name defines */
#define PROG_NAME "Wolfenstein Reloaded"
#define CODE_NAME "Ronan"

/* Bit read/write defines */
#define BV(x) ( 0x01 << x )
#define rbi(x, y) ( x & BV(y) )
#define sbi(x, y) ( x |= BV(y) )
#define cbi(x, y) ( x &= ~BV(y) )

using namespace std;
