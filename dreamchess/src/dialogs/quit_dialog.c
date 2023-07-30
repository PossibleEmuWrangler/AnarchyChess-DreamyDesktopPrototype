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

#include "dialogs.h"

/** @brief Quits the current game.
 *
 *  Closes the dialog and causes the game to go back to the title menu.
 */
static int dialog_quit_ok(gg_widget_t *widget, gg_widget_t *emitter, void *data, void *extra_data) {
	gg_dialog_close();
	gg_dialog_close();
	DBG_LOG("Entering title menu");
	set_quit_to_menu(1);
	return 1;
}

static int dialog_close_cb(gg_widget_t *widget, gg_widget_t *emitter, void *data, void *extra_data) {
	gg_dialog_close();
	return 1;
}

/** The quit dialog. Asks the user to confirm that he wants to quit the game.
 */

/** @brief Creates the quit confirmation dialog.
 *
 *  @return The created dialog.
 */
gg_dialog_t *dialog_quit_create(gg_dialog_t *parent) {
	gg_widget_t *dialog;
	gg_widget_t *vbox = gg_vbox_create(0);

	gg_widget_t *widget = gg_label_create("Quit to Title?");
	gg_container_append(GG_CONTAINER(vbox), widget);

	widget = gg_label_create("");
	gg_container_append(GG_CONTAINER(vbox), widget);

	widget = gg_action_create_with_label("OK", 0.5f, 0.0f);
	gg_widget_subscribe_signal_name(widget, widget->id, "action_pressed", dialog_quit_ok, NULL);
	gg_container_append(GG_CONTAINER(vbox), widget);

	widget = gg_action_create_with_label("Cancel", 0.5f, 0.0f);
	gg_widget_subscribe_signal_name(widget, widget->id, "action_pressed", dialog_close_cb, NULL);
	gg_container_append(GG_CONTAINER(vbox), widget);
	gg_vbox_set_selected(vbox, 3);

	dialog = gg_dialog_create(vbox, NULL, parent, GG_DIALOG_AUTOHIDE_PARENT);
	gg_dialog_set_style(GG_DIALOG(dialog), get_ingame_style());
	return GG_DIALOG(dialog);
}
