/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Main thread manager. This is CRITICAL code.

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

#include <valarray>

#include "tID.h"
#include "tSDL.h"

#define THREAD_STOP_BIT 0x00
#define THREAD_KILL_BIT 0x01

#ifndef WOLF_THREADS_H
#define WOLF_THREADS_H

namespace Main {

	/* Forward declaration */
	class mThreadManager;

	/*!
	 *	Abstracts the complexity of an SDL_thread.
	 */

	class mThread : public tID {
	public:
		friend class mThreadManager;
		mThread(void (*setup)(), int (*loop)(void*), void (*cleanup)(), uint16_t watchdog_ms);
		void kick();
		uint8_t opts();
	protected:
		void init();
		void spawn(void * data);
		int stop();
		void kill();
		void decay();
		uint16_t watchDog();
	private:
		void (*_setup)();
		void (*_cleanup)();
		int  (*_loop) (void*);
		uint16_t _watchdog_ms, _cur_watchdog;
		uint8_t  _opts;
		SDL_Thread * _thread;
		SDL_sem * _lock;
	};

	/*!
	 *	Manages mThreads statically.
	 */

	class mThreadManager : public tIDManager <mThread> {
	public:
		static int runAll();
		static size_t numThreads();
		static void addThread(mThread * thread);
	private:
		static uint8_t _opts;
	};

	/* Constants */
	const uint8_t mThreadDefaultOpts = 0x00;
	const uint16_t mThreadWatchdogMultiple = 1500;

	/* Typedef */
	typedef tIDList <mThread*> mThreadList;

}

#endif /* WOLF_THREADS_H */
