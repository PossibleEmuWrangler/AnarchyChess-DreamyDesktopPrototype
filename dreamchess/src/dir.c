/*  DreamChess
**
**  DreamChess is the legal property of its developers, whose names are too
**  numerous to list here. Please refer to the AUTHORS.txt file distributed
**  with this source distribution.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "dir.h"

#ifdef _WIN32

#define USERDIR "DreamChess"

#include "shlobj.h"
#include "shlwapi.h"
#include <io.h>
#include <windows.h>

int ch_datadir(void) {
	char filename[MAX_PATH + 6];

	GetModuleFileName(NULL, filename, MAX_PATH);
	filename[MAX_PATH] = '\0';
	PathRemoveFileSpec(filename);
	strcat(filename, "/data");
	return chdir(filename);
}

int ch_userdir(void) {
	char appdir[MAX_PATH];

	if (SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdir))
		return -1;

	if (chdir(appdir))
		return -1;

	if (chdir(USERDIR)) {
		if (mkdir(USERDIR))
			return -1;

		return chdir(USERDIR);
	}

	return 0;
}

#elif defined __APPLE__

#include "CoreFoundation/CoreFoundation.h"
#include <sys/stat.h>
#include <unistd.h>

#define USERDIR "Library/Application Support/DreamChess"

int ch_datadir(void) {
	char temp1[200];
	char temp2[200];
	char temp3[200];
	CFBundleRef mainBundle = CFBundleGetMainBundle();

	CFURLRef bundledir = CFBundleCopyResourcesDirectoryURL(mainBundle);
	CFURLRef resdir = CFBundleCopyBundleURL(mainBundle);

	CFStringRef stringref = CFURLCopyFileSystemPath(bundledir, kCFURLPOSIXPathStyle);
	CFStringGetCString(stringref, temp1, 200, kCFStringEncodingMacRoman);

	stringref = CFURLCopyFileSystemPath(resdir, kCFURLPOSIXPathStyle);
	CFStringGetCString(stringref, temp2, 200, kCFStringEncodingMacRoman);

	snprintf(temp3, sizeof(temp3), "%s/%s", temp2, temp1);

	return chdir(temp3);
}

int ch_userdir(void) {
	char *home = getenv("HOME");

	if (!home)
		return -1;

	if (chdir(home))
		return -1;

	if (chdir(USERDIR)) {
		if (mkdir(USERDIR, 0755))
			return -1;

		return chdir(USERDIR);
	}

	return 0;
}

#else /* !_WIN32 */

#define USERDIR ".dreamchess"

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int ch_datadir(void) {
	return chdir(DATADIR);
}

int ch_userdir(void) {
	char *home = getenv("HOME");

	if (!home)
		return -1;

	if (chdir(home))
		return -1;

	if (chdir(USERDIR)) {
		if (mkdir(USERDIR, 0755))
			return -1;

		return chdir(USERDIR);
	}

	return 0;
}

#endif
