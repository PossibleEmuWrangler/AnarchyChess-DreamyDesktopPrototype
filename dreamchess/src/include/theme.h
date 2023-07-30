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

#ifndef DREAMCHESS_THEME_H
#define DREAMCHESS_THEME_H

#include "gamegui/queue.h"
#include "options.h"

/* Define our booleans */
#define TRUE 1
#define FALSE 0

typedef struct theme_selector {
	float colour[4];
	float spinspeed;
	float size;
	float bouncespeed;
} theme_selector_t;

typedef struct theme_struct {
	char *name;
	char *style;
	char *pieces;
	char *board;
	char *white_name;
	char *black_name;
	char lighting;
	theme_selector_t selector;
} theme;

typedef TAILQ_HEAD(, music_pack) music_packs_t;

typedef struct {
	char *name;

} theme_style_t;

typedef struct {
	char *name;

} theme_pieces_t;

typedef struct {
	char *name;

} theme_board_t;

typedef struct music_pack {
	char *dir;
	TAILQ_ENTRY(music_pack) entries;
} music_pack_t;

void theme_find_themes(option_t *option);
void theme_find_music_packs(void);
music_packs_t *theme_get_music_packs(void);

#endif
