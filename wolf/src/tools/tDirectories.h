/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Directory and file management

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

#include <string>
#include <fstream>
#include <memory>
#include <cstdarg>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/convenience.hpp>

#if defined(MACOSX) || defined(LINUX)
#include <unistd.h>
#endif

#ifdef MACOSX
#include <Foundation/Foundation.h>
#elif defined(WINDOWS)
#include <windows.h>
#include <winbase.h>
#include <direct.h>
#include <shlobj.h>
#endif

#include "tID.h"
#include "tColor.h"
#include "tError.h"
#include "tRandom.h"

#ifndef WOLF_DIRECTORIES_H
#define WOLF_DIRECTORIES_H

/* Forward declarations */
class tDirectory;
class tAutoDirectory;
class tFile;
class tDirectoryManager;

/* Non platform-specific location enumeration, modded, ripped from http://bit.ly/d0wv1J */
enum tDirectoryEnum {
	/* From Apple */
	tApplicationDirectory = 1,
	tLibraryDirectory = 2,
	tUserDirectory = 3,
	tDocumentationDirectory = 4,
	tDesktopDirectory = 12,
	tCachesDirectory = 13,
	tApplicationSupportDirectory = 14,
	tMoviesDirectory = 17,
	tMusicDirectory = 18,
	tPicturesDirectory = 19,
	tAllLibrariesDirectory = 101,

	/* From me */
	tApplicationResourceDirectory = 200
};

/*!
 *	A base class for anything that relies on a path.
 */

class tPathBase {
public:
	boost::filesystem::path path();
	ios_base::openmode mode();
protected:
	ios_base::openmode _mode;
	boost::filesystem::path _path;
};

/*!
 *	A base class for tDirectories
 */

class tDirectoryBase : public tID, public tPathBase, public tLIDManager1 <tFile>, public tLIDManager2 <tDirectoryBase> {
public:
	friend class tDirectory;
	friend class tAutoDirectory;
	friend class tFile;
	bool Good();
	boost::filesystem::directory_iterator iterator();
	tDirectoryBase * directoryWithName(string name);
	tFile * fileWithName(string name);
	string name();
	virtual void openMe() = 0;
protected:
	virtual void release();
	boost::filesystem::directory_iterator _iterator;
	bool _good, _createIfNonexistent;
};

/*!
 *	A class that manages R/W access to a directory.
 */

class tDirectory : public tDirectoryBase {
public:
	tDirectory(tDirectoryEnum directory, const char * subdirectory = NULL, bool cwd = false, bool createIfNonexistent = true, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::app | ios_base::binary);
	tDirectory(tDirectoryBase * parent, const char * subdirectory = NULL, bool cwd = false, bool createIfNonexistent = true, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::app | ios_base::binary);
	void openMe();
private:
	tDirectoryBase * _parent;
};

/*!
 *	Like a tDirectory, but recursively poplates its file arrays.
 */

class tAutoDirectory : public tDirectoryBase {
public:
	tAutoDirectory(tDirectoryBase * parent, const char * subdirectory = NULL, bool createIfNonexistent = true, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::app | ios_base::binary);
	~tAutoDirectory();
	void openMe();
protected:
	void release();
private:
	tDirectoryBase * _parent;
};

/*!
 *	A class that manages R/W access to a file.
 */

class tFile : public tID, public tPathBase, public boost::filesystem::fstream {
public:
	tFile(tDirectoryBase * directory, const char * filename);
	tFile(tDirectoryBase * directory, const char * filename, ios_base::openmode mode);
	void erase();
	void openMe();
	void exit();
private:
	tDirectoryBase * _directory;
};

/*!
 *	A class that manages a bunch of tDirectories.
 */

class tDirectoryManager : public tIDManager <tDirectoryBase> {
public:
	friend class tDirectory;
	friend class tAutoDirectory;
	static void InitAll();
};

/* Typedefs */
typedef tIDList <tDirectoryBase*> tDirectoryList;
typedef tIDList <tFile*> tFileList;

/* Constants */
const char tTestFilePrefix[] = "wolf_";
const char tTestFileContents[] = "Romulus";
const char tHexArray[] = "0123456789abcdef";
const uint8_t tRandStringLen = 4;

#endif /* WOLF_DIRECTORIES_H */
