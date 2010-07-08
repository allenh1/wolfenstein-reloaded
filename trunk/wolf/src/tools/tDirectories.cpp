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

#include "tDirectories.h"

/*!
 *	Returns the Boost FS path to the directory.
 */

boost::filesystem::path tPathBase::path() {
	return _path;
}

/*!
 *	Returns the open mode of this path object as a bitmask
 */

ios_base::openmode tPathBase::mode() {
	return _mode;
}

/*!
 *	Returns true if this directory is good to use
 */

bool tDirectoryBase::Good() {
	return _good;
}

/*!
 *	Returns the Boost FS iterator to this directory.
 */

boost::filesystem::directory_iterator tDirectoryBase::iterator() {
	return _iterator;
}

/*!
 *	Returns a pointer to the directory object with the specified name.
 */

tDirectoryBase * tDirectoryBase::directoryWithName(string name) {
	tDirectoryBase * ret = NULL;
	for( tDirectoryList::iterator child = List2()->begin(); child != List2()->end(); child++ ) {
		if( name == (*child)->path().leaf() ) {
			ret = *child;
			break;
		}
	}
	return ret;
}

/*!
 *	Returns a pointer to the file object with the specified name.
 */

tFile * tDirectoryBase::fileWithName(string name) {
	tFile * ret = NULL;
	for( tFileList::iterator child = List1()->begin(); child != List1()->end(); child++ ) {
		if( name == (*child)->path().leaf() ) {
			ret = *child;
			break;
		}
	}
	return ret;
}

/*!
 *	Returns the name of this directory. Example: /usr/bin would return "bin."
 */

string tDirectoryBase::name() {
	return _path.leaf();
}

/*!
 *	Useless: it's virtual.
 */

void tDirectoryBase::release() {
}

/*!
 *	Makes a subdirectory object within the OS-specific directory enum.
 */

tDirectory::tDirectory(tDirectoryEnum directory, const char * subdirectory, bool cwd, bool createIfNonexistent, ios_base::openmode mode) {
	string subdir;
	if( subdirectory != NULL )
		subdir.assign( subdirectory );

	if( directory != tApplicationResourceDirectory ) {
#if defined(MACOSX) /* PORTABILITY_NEEDED */
		_path = boost::filesystem::path( boost::filesystem::path( [ [ NSSearchPathForDirectoriesInDomains( (NSSearchPathDirectory)directory, NSUserDomainMask, YES ) objectAtIndex:0 ] cStringUsingEncoding:NSASCIIStringEncoding ] ) / subdir );
#elif defined(LINUX)
#elif defined(WINDOWS)
        /* Which directory should we use? */
        uint32_t directory_type;
		if( directory == tApplicationDirectory )
            directory_type = CSIDL_PROGRAM_FILES;
		else if( directory == tUserDirectory )
            directory_type = CSIDL_PROFILE;
		else if( directory == tDesktopDirectory )
            directory_type = CSIDL_DESKTOPDIRECTORY;
		else if( directory == tCachesDirectory )
            directory_type = 0xffffffff;
		else if( directory == tApplicationSupportDirectory )
            directory_type = CSIDL_APPDATA;
		else if( directory == tMoviesDirectory )
            directory_type = CSIDL_MYVIDEO;
		else if( directory == tMusicDirectory )
            directory_type = CSIDL_MYMUSIC;
		else if( directory == tPicturesDirectory )
            directory_type = CSIDL_MYPICTURES;
        else
            directory_type = 0x00000000;

        /* Check */
        if( directory_type == 0x00000000 )
            return;

        if( directory_type != 0xffffffff ) {
            /* Path array */
            char name[PATH_MAX + 1];

            /* Set the memory */
            memset( name, PATH_MAX + 1, 0x00 );

            /* Get the path */
            if( SHGetFolderPath( NULL, directory_type, NULL, 0, name ) != S_OK ) /* NEEDS_LOCALIZATION */ {
                cerr << "Error getting folder path!" << endl;
                return;
            }

            /* Set the path */
            _path = boost::filesystem::path( name ) / subdir;
        }
        else {
            /* Path array */
            char name[PATH_MAX + 1];

            /* Set the memory */
            memset( name, PATH_MAX + 1, 0x00 );

            /* Get the path */
            if( GetTempPath( PATH_MAX, name ) == 0 ) /* NEEDS_LOCALIZATION */ {
                cerr << "Error getting temp folder path!" << endl;
                return;
            }
        }
#endif
		_mode = mode;
		_createIfNonexistent = createIfNonexistent;
	}
	else {
#if defined(MACOSX) /* PORTABILITY_NEEDED */
		_path = boost::filesystem::path( [ [ [ NSBundle mainBundle ] resourcePath ] cStringUsingEncoding:NSASCIIStringEncoding ] );
#elif defined(LINUX)
#elif defined(WINDOWS)
        /* Some vars. */
        char filename[PATH_MAX + 1];
        string str;
        size_t size = 0;

        /* Set the memory */
        memset( filename, PATH_MAX + 1, 0x00 );

        /* Windows API call */
        size = GetModuleFileName( NULL, filename, PATH_MAX );

        /* Check it */
        if( size == 0 ) /* NEEDS_LOCALIZATION */ {
            cerr << "Error getting executable path!" << endl;
            return;
        }

        /* Clean it up a bit */
        str.assign( filename );
        str.assign( str.substr( 0, str.find_last_of( "/\\") ) );

        _path = boost::filesystem::path( str.c_str() );
#endif
		_mode = ios_base::in | ios_base::binary;
		_createIfNonexistent = false;
	}

	if( cwd ) {
		if( chdir( _path.string().c_str() ) != 0 ) {
            cerr << "Error changing working directory!" << endl; // NEEDS_LOCALIZATION
            return;
		}

		boost::filesystem::initial_path();
	}

	tDirectoryManager::pushID( this );
}

/*!
 *	Defines a subdirectory.
 */

tDirectory::tDirectory(tDirectoryBase * parent, const char * subdirectory, bool cwd, bool createIfNonexistent, ios_base::openmode mode) {
	string subdir;
	if( subdirectory != NULL )
		subdir.assign( subdirectory );

	_path = boost::filesystem::path( parent->_path / subdir );
	_mode = mode;
	_createIfNonexistent = createIfNonexistent;
	_parent = parent;

	if( cwd ) {
		if( chdir( _path.string().c_str() ) != 0 )
            cerr << "Error changing working directory!" << endl; // NEEDS_LOCALIZATION
		boost::filesystem::initial_path();
	}

	_parent->pushID2( this );
}

/*!
 *	Opens this tDirectory and checks for access problems.
 */

void tDirectory::openMe()
{
	/* Make the directory if not there */
	_good = exists( _path ) && is_directory( _path );
	if( !_good && _createIfNonexistent ) {
		create_directory( _path );
		_good = exists( _path ) && is_directory( _path ) && is_empty( _path );
		tASSERT( _good );
	}

	/* Test R/W access and set up the iterator */
	if( _good ) {
		/* Set up the iterator */
		_iterator = boost::filesystem::directory_iterator( _path );

		/* Run the write test if necessary */
		if( _mode & ios_base::out ) {
			/* Vars */
			tRandomizer & rand = tRandomizer::getInstance();
			tFile testFile( this, ( tTestFilePrefix + rand.randomString( tRandStringLen, tHexArray ) ).c_str() );
			string str1( tTestFileContents ), str2;
			testFile.openMe();

			/* Stream in stuff */
			testFile << str1;
			testFile.seekg( 0 );
			testFile >> str2;

			/* Assertion */
			tASSERT( str1 == str2 );

			/* Delete the file */
			testFile.erase();
		}

		/* Check all subdirectories and files */
		for( tFileList::iterator child1 = List1()->begin(); child1 != List1()->end(); child1++ )
			(*child1)->openMe();
		for( tDirectoryList::iterator child2 = List2()->begin(); child2 != List2()->end(); child2++ )
			(*child2)->openMe();
	}
}

/*!
 *	Creates an automatic, recursive directory within another.
 */

tAutoDirectory::tAutoDirectory(tDirectoryBase * parent, const char * subdirectory, bool createIfNonexistent, ios_base::openmode mode) {
	string subdir;
	if( subdirectory != NULL )
		subdir.assign( subdirectory );

	_path = boost::filesystem::path( parent->_path / subdir );
	_mode = mode;
	_createIfNonexistent = createIfNonexistent;
	_parent = parent;
	_parent->pushID2( this );
}

/*!
 *	Destroys this tAutoDirectory in memory.
 */

tAutoDirectory::~tAutoDirectory() {
	release();
}

/*!
 *	Opens a handle to this tAutoDirectory.
 */

void tAutoDirectory::openMe() {
	/* Make the directory if not there */
	_good = exists( _path ) && is_directory( _path );
	if( !_good && _createIfNonexistent ) {
		create_directory( _path );
		_good = exists( _path ) && is_directory( _path ) && is_empty( _path );
		tASSERT( _good );
	}

	/* Test R/W access and set up the iterator */
	if( _good ) {
		/* Run the write test if necessary */
		if( _mode & ios_base::out ) {
			/* Vars */
			tRandomizer & rand = tRandomizer::getInstance();
			tFile testFile( this, ( tTestFilePrefix + rand.randomString( tRandStringLen, tHexArray ) ).c_str() );
			string str1( tTestFileContents ), str2;
			testFile.openMe();

			/* Stream in stuff */
			testFile << str1;
			testFile.seekg( 0 );
			testFile >> str2;

			/* Assertion */
			tASSERT( str1 == str2 );

			/* Delete the file */
			testFile.erase();
		}

		/* Load all specified files and directories */
		for( tFileList::iterator child1 = List1()->begin(); child1 != List1()->end(); child1++ )
			(*child1)->openMe();
		for( tDirectoryList::iterator child2 = List2()->begin(); child2 != List2()->end(); child2++ )
			(*child2)->openMe();

		/* Load all OTHER files and subdirectories automatically */
		for( _iterator = boost::filesystem::directory_iterator( _path ); _iterator != boost::filesystem::directory_iterator(); _iterator++ ) {
			if( is_directory( *_iterator ) ) {
				bool found = false;
				for( tDirectoryList::iterator child = List2()->begin(); child != List2()->end(); child++ ) {
					if( (*child)->path().leaf() == _iterator->leaf() ) {
						found = true;
						break;
					}
				}
				if( !found ) {
					tAutoDirectory * subdir = new tAutoDirectory( this, _iterator->leaf().c_str(), _createIfNonexistent, _mode );
					subdir->openMe();
				}
			}
			else if( is_regular_file( *_iterator ) ) {
				bool found = false;
				for( tFileList::iterator child = List1()->begin(); child != List1()->end(); child++ ) {
					if( (*child)->path().leaf() == _iterator->leaf() ) {
						found = true;
						break;
					}
				}
				if( !found ) {
					tFile * subfile = new tFile( this, _iterator->leaf().c_str(), _mode );
					subfile->openMe();
				}
			}
		}
	}
}

/*!
 *	Recursively closes out this tAutoDirectory.
 */

void tAutoDirectory::release()
{
	/* Close all files and open directories */
	for( tFileList::iterator child1 = List1()->begin(); child1 != List1()->end(); child1++ ) {
		/* Close the file */
		(*child1)->exit();

		/* Free and call destructor */
		if( *child1 )
			delete *child1;
	}
	for( tDirectoryList::iterator child2 = List2()->begin(); child2 != List2()->end(); child2++ ) {
		/* Free and call the destructor again */
		if( *child2 )
		{
			(*child2)->release();
			delete *child2;
		}
	}
}

/*!
 *	Creates a tFile and inherits mode from its parent
 */

tFile::tFile(tDirectoryBase * directory, const char * filename) {
	_path = boost::filesystem::path( directory->path() / filename );
	_mode = directory->mode();
	_directory = directory;
	_directory->pushID1( this );
}

/*!
 *	Creates a tFile with a different openmode than its parent
 */

tFile::tFile(tDirectoryBase * directory, const char * filename, ios_base::openmode mode) {
	_path = boost::filesystem::path( directory->_path / filename );
	_mode = mode;
	_directory = directory;
	_directory->pushID1( this );
}

/*!
 *	Deletes this tFile from the storage media
 */

void tFile::erase() {
	/* Protection */
	if( !( _mode & ios_base::out ) )
		return;

    exit();

#ifndef WINDOWS
    if( exists( _path ) )
		remove( _path );
#else
    /* Windows workaround */
	if( exists( _path ) )
	{
	    if( remove( _path.native_file_string().c_str() ) != 0 )
            cerr << "Error deleting file: " << strerror( errno ) << endl;
	}
#endif
	if( !exists( _path ) )
		_directory->deleteID1( this );

    /* Assertion */
	tASSERT( !exists( _path ) );
}

/*!
 *	Opens this tFile
 */

void tFile::openMe() {
	/* Open the file */
	open( _path, _mode );

	/* Assertion */
	tASSERT( exists( _path ) && is_open() && good() );
}

/*!
 *	Closes this tFile
 */

void tFile::exit() {
	if( is_open() )
		close();
}

/*!
 *	Returns a tPointer to all the data
 */

char * tFile::data(size_t &size) {
    char * ret = NULL;
    if( !exists( _path ) || !is_open() || !good() )
        return NULL;

    seekg( 0, ios::end );
    size = tellg();
    ret = new char[size];
    read( ret, size );

    return ret;
}

/*!
 *	Recursively opens all directories registered statically.
 */

void tDirectoryManager::InitAll() {
	/* Go through ALL directories. */
	for( tDirectoryList::iterator parent = list()->begin(); parent != list()->end(); parent++ )
		(*parent)->openMe();
}
