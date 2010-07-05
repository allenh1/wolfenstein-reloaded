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

#include "mThread.h"

uint8_t Main::mThreadManager::_opts = mThreadDefaultOpts;

/*!
 *	Initializes a thread object. Setup is run first, loop next, and cleanup last.
 */

Main::mThread::mThread(void (*setup)(), int (*loop)(void*), void (*cleanup)(), uint16_t watchdog_ms) {
	/* Initialize vars */
	_setup = setup;
	_loop = loop;
	_cleanup = cleanup;
	_thread = NULL;
	_lock = NULL;
	_opts = mThreadDefaultOpts;
	
	/* This is the only 100% necessary function. Validate it. */
	if( !loop )
		return;
	
	/* Normalize watchdog time variable to a multiple of mThreadWatchdogMultiple milliseconds */
	if( watchdog_ms % mThreadWatchdogMultiple != 0 ) {
		float x = (float)watchdog_ms / (float)mThreadWatchdogMultiple;
		float intpart_f;
		float fraction = modf( x, &intpart_f );
		watchdog_ms = (int)intpart_f;
		
		if( fraction >= 0.5f )
			watchdog_ms++;
		
		watchdog_ms *= mThreadWatchdogMultiple;
	}
	
	/* Set final watchdog time */
	_watchdog_ms = _cur_watchdog = watchdog_ms;
	
	/* Add the thread to the thread list */
	Main::mThreadManager::addThread( this );
}

/*!
 *	Keeps a thread alive by waking up the watchdog.
 */

void Main::mThread::kick() {
	/* Wait on the semaphore */
	SDL_SemWait( _lock );
	
	/* Kick the watchdog */
	_cur_watchdog = _watchdog_ms;
	
	/* Unlock the semaphore */
	SDL_SemPost( _lock );
}

/*!
 *	Initializes a thread without starting it. Runs setup() code.
 */

void Main::mThread::init() {
	/* Run thread setup code if applicable */
	if( _setup )
		_setup();
}

/*!
 *	Returns a bitmask of the thread options.
 */

uint8_t Main::mThread::opts() {
	return _opts;
}

/*!
 *	Spawns the thread, passing it a pointer to arbitrary data that may or may not be used.
 */

void Main::mThread::spawn(void * data) {
	/* Reset options */
	_opts = mThreadDefaultOpts;
	
	/* Create thread and set ID */
	_thread = SDL_CreateThread( _loop, data );
	setID( SDL_GetThreadID( _thread ) );
	
	/* Make the semaphore */
	_lock = SDL_CreateSemaphore( 1 );
}

/*!
 *	Stops the thread safely.
 */
int Main::mThread::stop() {	
	/* Set up return var */
	int ret = 0;
	
	/* Return if we're already trying to kill or stop this thread */
	if( rbi( _opts, THREAD_STOP_BIT ) || rbi( _opts, THREAD_KILL_BIT ) )
		return ret;
	
	/* Set the stop bit, clear the kill bit */
	sbi( _opts, THREAD_STOP_BIT );
	cbi( _opts, THREAD_KILL_BIT );
	
	/* Wait on the thread to nicely finish */
	if( _thread )
		SDL_WaitThread( _thread, &ret );
	
	/* Cleanup */
	if( _cleanup )
		_cleanup();
	
	/* Nullify the thread */
	if( _thread )
		_thread = NULL;
	
	/* Destroy the semaphore */
	if( _lock ) {
		SDL_DestroySemaphore( _lock );
		_lock = NULL;
	}
	
	/* Reset the ID */
	_id = 0x00;
	
	/* Cleanup */
	return ret;
}

/*!
 *	Kills the thread gracelessly and runs its cleanup code.
 */

void Main::mThread::kill() {
	/* Let kill() take priority over stop() */
	if( rbi( _opts, THREAD_KILL_BIT ) )
		return;
	
	/* Set both bits */
	sbi( _opts, THREAD_STOP_BIT );
	sbi( _opts, THREAD_KILL_BIT );
	
	/* Kill the thread */
	if( _thread )
		SDL_KillThread( _thread );
	
	/* Cleanup */
	if( _cleanup )
		_cleanup();
	
	/* Nullify the thread */
	if( _thread )
		_thread = NULL;
	
	/* Destroy the semaphore */
	if( _lock ) {
		SDL_DestroySemaphore( _lock );
		_lock = NULL;
	}
	
	/* Reset the ID */
	_id = 0x00;
}

/*!
 *	Decrements a thread's watchdog value.
 */

void Main::mThread::decay() {
	/* Wait on the semaphore */
	SDL_SemWait( _lock );
	
	/* Decay the watchdog timer */
	if( _cur_watchdog > 0 )
		_cur_watchdog -= mThreadWatchdogMultiple;
	
	/* Unlock the semaphore */
	SDL_SemPost( _lock );
}

/*!
 *	Returns the thread's current watchdog timer value.
 */

uint16_t Main::mThread::watchDog() {
	return _cur_watchdog;
}

/*!
 *	Runs all threads.
 *  WARNING! THIS FUNCTION IS CRITICAL FOR PROPER GAMEPLAY.
 *  DO NOT MESS WITH THIS CODE! TEST THOROUGHLY.
 */
 
int Main::mThreadManager::runAll() {
	/* Step 1: Set up some variables. */
	mThread * curr_thread = NULL;
	size_t size = numThreads();
	valarray <int> ret( size );
	SDL_Event event;
	
	/* Step 2: Go through the list and init/start all threads. */
	for( mThreadList::iterator it = list()->begin(); it != list()->end(); it++ ) {
		(*it)->init();
		(*it)->spawn( NULL );
	}
	
	/* Step 3: Runtime. Watch the threads for crashes. */
	while( !rbi( _opts, THREAD_STOP_BIT ) ) {
		/* Iterate through all threads */
		for( mThreadList::iterator it = list()->begin(); it != list()->end(); it++ ) {
			/* Decay the thread. */
			curr_thread = *it;
			curr_thread->decay();
			
			/* A thread is frozen, so kill it and exit. */
			if( curr_thread->watchDog() <= 0 ) {
				curr_thread->kill();
				sbi( _opts, THREAD_STOP_BIT );
			}
			
			/* Check the stop bit and kill bit. If set, quit. */
			if( rbi( curr_thread->opts(), THREAD_STOP_BIT ) || rbi( curr_thread->opts(), THREAD_KILL_BIT ) )
				sbi( _opts, THREAD_STOP_BIT );
		}
		
		/* Check SDL events */
		SDL_PollEvent( &event );
		
		/* Quit if necessary */
		if( event.type == SDL_QUIT ) {
			sbi( _opts, THREAD_STOP_BIT );
			break;
		}
		
		/* Delay */
		SDL_Delay( mThreadWatchdogMultiple );
	}
	
	/* Step 4: Clean up all threads. A value of 0 indicates a successful stop. */
	size_t a = 0;
	mThreadList::iterator it = list()->begin();
	while( it != list()->end() && a < size ) {
		ret[a] = (*it)->stop();
		it++;
		a++;
	}
	
	/* Step 5: Reset memory. */
	list()->clear();
	_opts = mThreadDefaultOpts;
	
	/* Step 6: Return the greatest error value. */
	return ret.max();
}

/*!
 *	Returns the number of active threads.
 */

size_t Main::mThreadManager::numThreads() {
	size_t ret = 0;
	
	/* Go through the list. */
	for( mThreadList::iterator it = list()->begin(); it != list()->end(); it++ ) {
		if( !rbi( (*it)->opts(), THREAD_STOP_BIT ) && !rbi( (*it)->opts(), THREAD_KILL_BIT ) ) /* Running */
			ret++;
	}
	
	return ret;
}

/*!
 *	Adds a thread to the global thread manager.
 */

void Main::mThreadManager::addThread(mThread * thread) {
	pushID( thread );
}
