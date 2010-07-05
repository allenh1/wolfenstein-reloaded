/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Main file containing program entry point.

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

#include "mMain.h"
#include "tString.h"

/*!
 *	Library init code
 */

void library_init() {
	/* SDL */
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
        cerr << "Error initializing SDL: " << SDL_GetError() << endl;
        exit( EXIT_FAILURE );
	}

	/* SDL_Mixer */
	if( Mix_Init( MIX_INIT_EVERYTHING ) == 0 ) {
        cerr << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
        exit( EXIT_FAILURE );
	}

	/* SDL_Image */
	if( IMG_Init( IMG_INIT_EVERYTHING ) == 0 ) {
	    cerr << "Error initializing SDL_image: " << IMG_GetError() << endl;
	    exit( EXIT_FAILURE );
	}

	/* SDL_TTF */
	if( TTF_Init() != 0 ) {
		cerr << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
		exit( EXIT_FAILURE );
	}

	/* libxml2 */
	LIBXML_TEST_VERSION;
}

/*!
 *	Library cleanup code
 */

void library_cleanup() {
	/* SDL */
	SDL_Quit();

	/* SDL_Mixer */
	Mix_Quit();

	/* SDL_Image */
	IMG_Quit();

	/* SDL_TTF */
	TTF_Quit();

	/* libxml2 */
	xmlCleanupParser();
}

/*!
 *	The main entry point of the application.
 */

int main(int argc, char **argv) {
	/* Variables */
	int ret;
	uint8_t opts = 0x00;

	/* Library loading and verification */
	library_init();

	/* Library cleanup registration function */
	atexit( library_cleanup );

	/* Parse the command line */
	tCommandLineParser parser( argc, argv );

	/* For now, set the loop bit. */
	sbi( opts, MAIN_LOOP_BIT );

	/* Start up directory and file management */
	tDirectoryManager::InitAll();

	/* Play the game! */
	if( rbi( opts, MAIN_LOOP_BIT ) )
		ret = Main::mThreadManager::runAll();

	/* Return! */
	return ret;
}
