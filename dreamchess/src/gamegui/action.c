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

#include <gamegui/action.h>
#include <gamegui/label.h>

gg_class_id gg_action_get_class_id(void) {
	GG_CHILD(gg_bin_get_class_id())
}

/** Implements widget::render for action widgets. */
void gg_action_render(gg_widget_t *widget, int x, int y, int focus) {
	gg_widget_t *child = gg_bin_get_child(GG_BIN(widget));

	if (focus != GG_FOCUS_NONE)
		focus = GG_FOCUS_ALL;

	child->render(child, x, y, focus);
}

/** Implements widget::input for action widgets. */
int gg_action_input(gg_widget_t *widget, gg_event_t event) {
	gg_action_t *action = GG_ACTION(widget);

	if ((event.type == GG_EVENT_KEY && event.key == GG_KEY_ACTION) ||
		(event.type == GG_EVENT_MOUSE && event.mouse.type == GG_MOUSE_BUTTON_DOWN && event.mouse.button == 0)) {
		gg_widget_emit_signal(widget, widget, action->pressed, NULL);
		return 1;
	}

	return 0;
}

void gg_action_init(gg_action_t *action, gg_widget_t *widget) {
	gg_bin_init((gg_bin_t *)action, widget);

	action->render = gg_action_render;
	action->input = gg_action_input;
	action->id = gg_action_get_class_id();
	action->enabled = 1;
	action->width = widget->width;   /* FIXME */
	action->height = widget->height; /* FIXME */
	action->pressed = gg_signal_lookup(action->id, "action_pressed");
	if (action->pressed == -1)
		action->pressed = gg_signal_register(action->id, "action_pressed");
}

/** @brief Creates an action widget.
 *
 *  An action widget consists of a single label. When the widget is activated
 *  a function is executed.
 *
 *  @param string The text for the widget.
 *  @return The created action widget.
 */
gg_widget_t *gg_action_create(gg_widget_t *widget) {
	gg_action_t *action = malloc(sizeof(gg_action_t));

	gg_action_init(action, widget);

	return GG_WIDGET(action);
}

gg_widget_t *gg_action_create_with_label(char *text, float xalign, float yalign) {
	gg_widget_t *label = gg_label_create(text);
	gg_widget_t *action;

	gg_label_set_bouncy(GG_LABEL(label), 1);
	gg_align_set_alignment(GG_ALIGN(label), xalign, yalign);
	action = gg_action_create(label);
	return action;
}
