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

#ifndef GAMEGUI_OPTION_H
#define GAMEGUI_OPTION_H

#include <gamegui/select.h>
#include <gamegui/system.h>

#define GG_OPTION(W) GG_CHECK_CAST(W, gg_option_get_class_id(), gg_option_t)

#define GG_OPTION_DATA                                                                                                 \
	GG_SELECT_DATA                                                                                                     \
	gg_signal_t changed;

typedef struct gg_option {
	GG_OPTION_DATA
} gg_option_t;

void gg_option_render(gg_widget_t *widget, int x, int y, int focus);

int gg_option_input(gg_widget_t *widget, gg_event_t event);

void gg_option_set_size(gg_widget_t *widget, int width, int height);

void gg_option_init(gg_option_t *option);

gg_widget_t *gg_option_create(void);

void gg_option_append(gg_option_t *option, gg_widget_t *child);

void gg_option_append_label(gg_option_t *option, char *text, float xalign, float yalign);

int gg_option_get_selected(gg_option_t *option);
void gg_option_set_selected(gg_option_t *option, int index);

gg_class_id gg_option_get_class_id(void);

#endif
