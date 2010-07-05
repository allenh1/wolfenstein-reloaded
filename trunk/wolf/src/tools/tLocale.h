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

#include "defs.h"

#include <map>

#include "tDirectories.h"

#ifndef WOLF_LOCALE_H
#define WOLF_LOCALE_H

/*!
 *	Stores one language element.
 */	

class tLanguageElement {
public:
	tLanguageElement();
	tLanguageElement(string value);
	virtual ~tLanguageElement();
private:
};

/*!
 *	Stores a ton of language strings.
 */	

class tLanguage {
public:
	tLanguage();
	tLanguage(tFile * langfile);
	virtual ~tLanguage();
	void init();
private:
	tFile * _langfile;
};

/*!
 *	Stores a locale, including the language.
 */	

class tLocale {
public:
	tLocale();
	~tLocale();
private:
	tLanguage _language;
};

#endif /* WOLF_LOCALE_H */
