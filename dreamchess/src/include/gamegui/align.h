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

#ifndef GAMEGUI_ALIGN_H
#define GAMEGUI_ALIGN_H

#include <gamegui/system.h>
#include <gamegui/widget.h>

#define GG_ALIGN(W) GG_CHECK_CAST(W, gg_align_get_class_id(), gg_align_t)

#define GG_ALIGN_DATA                                                                                                  \
	GG_WIDGET_DATA                                                                                                     \
	float xalign;                                                                                                      \
	float yalign;

typedef struct gg_align {
	GG_ALIGN_DATA
} gg_align_t;

gg_class_id gg_align_get_class_id(void);

void gg_align_init(gg_align_t *align);

void gg_align_set_alignment(gg_align_t *align, float xalign, float yalign);

#endif
