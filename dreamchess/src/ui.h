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

#ifndef DREAMCHESS_UI_H
#define DREAMCHESS_UI_H

#include "board.h"
#include "dreamchess.h"

typedef struct ui_driver {
	char *name;
	void (*init)(void);
	int (*create_window)(int height, int width, int fullscreen, int ms);
	int (*resize)(int height, int width, int fullscreen, int ms);
	int (*exit)(void);
	config_t *(*config)(int *pgn_slot);
	void (*update)(board_t *board, move_t *move);
	void (*poll)(void);
	void (*show_message)(char *msg);
	void (*show_result)(result_t *result);
} ui_driver_t;

extern ui_driver_t ui_sdlgl;

typedef enum ui_event {
	UI_EVENT_NONE = 0x00,
	UI_EVENT_BACKSPACE = 0x08,
	UI_EVENT_ESCAPE = 0x1B,
	UI_EVENT_SPACE = 0x20,
	UI_EVENT_DELETE = 0x7F,
	UI_EVENT_ACTION = 0x100,
	UI_EVENT_EXTRA1,
	UI_EVENT_EXTRA2,
	UI_EVENT_EXTRA3,
	UI_EVENT_UP,
	UI_EVENT_RIGHT,
	UI_EVENT_DOWN,
	UI_EVENT_LEFT,
	UI_EVENT_HOME,
	UI_EVENT_END
} ui_event_t;

#endif
