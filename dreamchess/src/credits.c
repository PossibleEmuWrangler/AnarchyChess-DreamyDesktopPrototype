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

#include <stdlib.h>

#include "config.h"
#include "credits.h"

static char *programming[] = {"Programming", "DreamChess Authors", "Possible_EmuWrangler", NULL};

static char *graphics[] = {"Graphics",
						   "DreamChess Authors",
						   NULL};

static char *modelling[] = {"3D Modelling", "DreamChess Authors", NULL};

static char *thanks[] = {"Special Thanks To",
						 "Garry Chess"
						 , NULL};

static char *copyright[] = {"AnarchyChess DreamyDesktopPrototype 0.8.6", "\xa9 2023", "https://www.google.com/search?channel=fs&q=En+passant - Google En Passant", NULL};

static char *music[] = {"Music", "DreamChess Authors", NULL};

static char **credits[] = {copyright, programming, music, graphics, modelling, thanks, NULL};

char ***get_credits(void) {
	return credits;
}
