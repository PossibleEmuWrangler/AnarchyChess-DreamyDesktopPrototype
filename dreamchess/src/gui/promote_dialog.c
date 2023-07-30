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

#include "ui_sdlgl.h"

static int dialog_promote_cb(gg_widget_t *widget, gg_widget_t *emitter, void *data, void *extra_data) {
	set_dialog_promote_piece(*(int *)extra_data);
	gg_dialog_close();
	return 1;
}

gg_dialog_t *dialog_promote_create(int colour) {
	static int cb_pieces[5];

	texture_t *pieces;
	gg_widget_t *dialog;
	gg_widget_t *action;
	gg_widget_t *vbox = gg_vbox_create(0);
	gg_widget_t *hbox = gg_hbox_create(0);
	gg_widget_t *gg_image;
	gg_widget_t *text = gg_label_create("Promotion! Choose new piece! Rightmost is Knook");

	set_dialog_promote_piece(NONE);
	cb_pieces[0] = QUEEN + colour;
	cb_pieces[1] = ROOK + colour;
	cb_pieces[2] = BISHOP + colour;
	cb_pieces[3] = KNIGHT + colour;
	cb_pieces[4] = KNOOK + colour;

	gg_container_append(GG_CONTAINER(vbox), text);

	if (IS_WHITE(colour))
		pieces = get_white_pieces();
	else
		pieces = get_black_pieces();

	gg_image = gg_image_create(&pieces[GUI_PIECE_QUEEN]);
	action = gg_action_create(gg_image);
	gg_widget_subscribe_signal_name(action, action->id, "action_pressed", dialog_promote_cb, &cb_pieces[0]);
	gg_container_append(GG_CONTAINER(hbox), action);

	gg_image = gg_image_create(&pieces[GUI_PIECE_ROOK]);
	action = gg_action_create(gg_image);
	gg_widget_subscribe_signal_name(action, action->id, "action_pressed", dialog_promote_cb, &cb_pieces[1]);
	gg_container_append(GG_CONTAINER(hbox), action);

	gg_image = gg_image_create(&pieces[GUI_PIECE_BISHOP]);
	action = gg_action_create(gg_image);
	gg_widget_subscribe_signal_name(action, action->id, "action_pressed", dialog_promote_cb, &cb_pieces[2]);
	gg_container_append(GG_CONTAINER(hbox), action);

	gg_image = gg_image_create(&pieces[GUI_PIECE_KNIGHT]);
	action = gg_action_create(gg_image);
	gg_widget_subscribe_signal_name(action, action->id, "action_pressed", dialog_promote_cb, &cb_pieces[3]);
	gg_container_append(GG_CONTAINER(hbox), action);

    
    /* ACTODO: This is for the knook, but use knight image for now */
	gg_image = gg_image_create(&pieces[GUI_PIECE_KNIGHT]);
	action = gg_action_create(gg_image);
	gg_widget_subscribe_signal_name(action, action->id, "action_pressed", dialog_promote_cb, &cb_pieces[4]);
	gg_container_append(GG_CONTAINER(hbox), action);
    
    gg_container_append(GG_CONTAINER(vbox), hbox);

	dialog = gg_dialog_create(vbox, NULL, NULL, 0);
	gg_dialog_set_modal(GG_DIALOG(dialog), 1);
	gg_dialog_set_style(GG_DIALOG(dialog), get_ingame_style());
	return GG_DIALOG(dialog);
}
