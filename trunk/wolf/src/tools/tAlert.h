/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Configuration manager
 
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

#ifdef MACOSX // NEEDS_PORTABILITY
#include <AppKit/NSAlert.h>
#include <Cocoa/Cocoa.h>
#endif // MACOSX

#include <cstdarg>
#include <sstream>

#include "mThread.h"

#ifndef WOLF_ALERT_H
#define WOLF_ALERT_H

/* Alert type enum */
typedef enum { tWarningAlertStyle, tInformationAlertStyle, tCriticalAlertStyle } tAlertStyle;

/* Alert button enum */
enum { tAlertDefaultButton = 1, tAlertAlternateButton = 0, tAlertOtherButton = -1, tAlertNoButton = 255 };

/*!
 *	A platform-specific alert window.
 */

#ifdef MACOSX // NEEDS_PORTABILITY
class tAlert {
public:
	tAlert();
	tAlert(const char * title = NULL, const char * info = NULL, tAlertStyle style = tInformationAlertStyle, const char * default_button = NULL, const char * alternate_button = NULL, const char * other_button = NULL);
	void setAlertProperties(const char * title = NULL, const char * info = NULL, tAlertStyle style = tInformationAlertStyle, const char * default_button = NULL, const char * alternate_button = NULL, const char * other_button = NULL);
	int run();
	bool running();
private:
	NSAlert * _alert;
	bool _running;
};
#endif // MACOSX

#endif /* WOLF_ALERT_H */
