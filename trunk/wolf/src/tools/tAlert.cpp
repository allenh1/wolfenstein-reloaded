/*
 
 **************************************************************************
 
 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Localization manager
 
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

#include "tAlert.h"

#ifdef MACOSX
/*!
 *	Creates a tAlert.
 */

tAlert::tAlert() {
	_alert = NULL;
	_running = false;
}

/*!
 *	Creates an alert and sets some properties.
 */

tAlert::tAlert(const char * title, const char * info, tAlertStyle style, const char * default_button, const char * alternate_button, const char * other_button) {
	setAlertProperties( title, info, style, default_button, alternate_button, other_button );
	_running = false;
}

/*!
 *	Sets alert properties.
 */

void tAlert::setAlertProperties(const char * title, const char * info, tAlertStyle style, const char * default_button, const char * alternate_button, const char * other_button) {
	/* Declare stuff */
	NSString *NSTitle, *NSInfo, *NSDefaultButton, *NSAlternateButton, *NSOtherButton;
	
	/* Configure NSStrings */
	if( !title )
		NSTitle = nil;
	else
		NSTitle = [ NSString stringWithCString: title encoding: [ NSString defaultCStringEncoding ] ];
	
	if( !info )
		NSInfo = nil;
	else
		NSInfo = [ NSString stringWithCString: info encoding: [ NSString defaultCStringEncoding ] ];
	
	if( !default_button )
		NSDefaultButton = nil;
	else
		NSDefaultButton = [ NSString stringWithCString: default_button encoding: [ NSString defaultCStringEncoding ] ];
	
	if( !alternate_button )
		NSAlternateButton = nil;
	else
		NSAlternateButton = [ NSString stringWithCString: alternate_button encoding: [ NSString defaultCStringEncoding ] ];
	
	if( !other_button )
		NSOtherButton = nil;
	else
		NSOtherButton = [ NSString stringWithCString: other_button encoding: [ NSString defaultCStringEncoding ] ];
	
	/* Make the alert */
	_alert = [ NSAlert alertWithMessageText: NSTitle defaultButton: NSDefaultButton alternateButton: NSAlternateButton otherButton: NSOtherButton informativeTextWithFormat: NSInfo ];
	[ _alert setAlertStyle: (NSAlertStyle)style ];
	
	/* Pre-render the alert */
	[ _alert layout ];
}

/*!
 *	Runs the alert.
 */

int tAlert::run() {
	/* Return variable */
	int ret = tAlertNoButton;
	
	/* Running already? */
	if( _running )
		return ret;
	
	/* Run the alert */
	_running = true;
	ret = [ _alert runModal ];
	_running = false;
	
	/* Return */
	return ret;
}

/*!
 *	Returns true if the alert is currently running.
 */

bool tAlert::running() {
	return _running;
}

#endif // MACOSX