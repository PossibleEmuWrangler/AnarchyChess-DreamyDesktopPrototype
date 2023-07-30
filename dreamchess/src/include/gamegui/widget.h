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

/** @file
 *  @brief Widget class interface.
 */

#ifndef GAMEGUI_WIDGET_H
#define GAMEGUI_WIDGET_H

#include <gamegui/queue.h>
#include <gamegui/signal.h>
#include <gamegui/system.h>

struct gg_dialog;

enum { GG_EVENT_NONE, GG_EVENT_KEY, GG_EVENT_CHAR, GG_EVENT_MOUSE };

enum { GG_MOUSE_BUTTON_DOWN, GG_MOUSE_BUTTON_UP, GG_MOUSE_MOVE };

typedef struct gg_event_mouse {
	int type;
	int button;
	int x, y;
} gg_event_mouse_t;

enum gg_event_key {
	GG_KEY_BACKSPACE = 0x08,
	GG_KEY_ESCAPE = 0x1B,
	GG_KEY_SPACE = 0x20,
	GG_KEY_DELETE = 0x7F,
	GG_KEY_ACTION = 0x100,
	GG_KEY_EXTRA1,
	GG_KEY_EXTRA2,
	GG_KEY_EXTRA3,
	GG_KEY_UP,
	GG_KEY_RIGHT,
	GG_KEY_DOWN,
	GG_KEY_LEFT,
	GG_KEY_HOME,
	GG_KEY_END,
	GG_KEY_ENTER
};

typedef struct gg_event {
	int type;
	int key;
	gg_event_mouse_t mouse;
} gg_event_t;

typedef TAILQ_HEAD(gg_widget_cb_head, gg_widget_cb_list) gg_widget_cb_head_t;

/** Typecast to widget. */
#define GG_WIDGET(W) GG_CHECK_CAST(W, gg_widget_get_class_id(), gg_widget_t)

/** Widget methods and properties. */
#define GG_WIDGET_DATA                                                                                                 \
	/** @brief Renders a widget.                                                                                       \
	 *                                                                                                                 \
	 *  @param widget The widget to render.                                                                            \
	 *  @param x Leftmost x coordinate where widget should be rendered.                                                \
	 *  @param y Lowermost y coordinate where widget should be rendered.                                               \
	 *  @param focus Current focus of widget.                                                                          \
	 */                                                                                                                \
	void (*render)(struct gg_widget * widget, int x, int y, int focus);                                                \
                                                                                                                       \
	/** @brief Processes a widget input event.                                                                         \
	 *                                                                                                                 \
	 *  @param widget The widget that is to receive the event.                                                         \
	 *  @param event The event to process.                                                                             \
	 *  @return 1 = event was handled. 0 = event was not handled.                                                      \
	 */                                                                                                                \
	int (*input)(struct gg_widget * widget, gg_event_t event);                                                         \
                                                                                                                       \
	/** @brief Sets a widget's requested size.                                                                         \
	 *                                                                                                                 \
	 *  @param widget The widget.                                                                                      \
	 *  @param width The width (in pixels) that the widget should request.                                             \
	 *               Ignored if smaller than minimum widget width.                                                     \
	 *  @param height The height (in pixels) that the widget should request.                                           \
	 *                Ignored if smaller than minimum widget height.                                                   \
	 */                                                                                                                \
	void (*set_size)(struct gg_widget * widget, int width, int height);                                                \
                                                                                                                       \
	/** @brief Gets a widget's requested size.                                                                         \
	 *                                                                                                                 \
	 *  @param widget The widget.                                                                                      \
	 *  @param width Returns the width (in pixels) that the widget requests.                                           \
	 *               Pointer can be NULL to ignore this dimension.                                                     \
	 *  @param height Returns the height (in pixels) that the widget                                                   \
	 *                requests. Pointer can be NULL to ignore this                                                     \
	 *                dimension.                                                                                       \
	 */                                                                                                                \
	void (*get_requested_size)(struct gg_widget * widget, int *width, int *height);                                    \
                                                                                                                       \
	/** @brief Gets a widget's focus position.                                                                         \
	 *                                                                                                                 \
	 *  @param widget The widget.                                                                                      \
	 *  @return Returns the rectangle defining the current focus position,                                             \
	 *          relative to the widget's position.                                                                     \
	 */                                                                                                                \
	gg_rect_t (*get_focus_pos)(struct gg_widget * widget);                                                             \
                                                                                                                       \
	/** @brief Sets a widget's focus position.                                                                         \
	 *                                                                                                                 \
	 *  @param widget The widget.                                                                                      \
	 *  @param x The x-coordinate (in pixels, relative to widget position)                                             \
	 *           of the new focus position.                                                                            \
	 *  @param y The y-coordinate (in pixels, relative to widget position)                                             \
	 *           of the new focus position.                                                                            \
	 *  @return 1 = focus set. 0 = focus not set.                                                                      \
	 */                                                                                                                \
	int (*set_focus_pos)(struct gg_widget * widget, int x, int y);                                                     \
                                                                                                                       \
	/** @brief Destroys a widget and frees all its allocated resources.                                                \
	 *                                                                                                                 \
	 *  @param widget The widget.                                                                                      \
	 */                                                                                                                \
	void (*destroy)(struct gg_widget * widget);                                                                        \
                                                                                                                       \
	/** Unique class ID */                                                                                             \
	gg_class_id id;                                                                                                    \
                                                                                                                       \
	/** Widget that contains this widget, if any, NULL otherwise. */                                                   \
	struct gg_widget *parent;                                                                                          \
                                                                                                                       \
	/** Enabled flag. 1 = widget enabled, 0 = widget disabled. */                                                      \
	int enabled;                                                                                                       \
                                                                                                                       \
	/** Minimum required width in pixels. */                                                                           \
	int width;                                                                                                         \
                                                                                                                       \
	/** Minimum required height in pixels. */                                                                          \
	int height;                                                                                                        \
                                                                                                                       \
	/** Forced required width. See gg_widget::set_size. */                                                             \
	int width_f;                                                                                                       \
                                                                                                                       \
	/** Forced required height. See gg_widget::set_size. */                                                            \
	int height_f;                                                                                                      \
                                                                                                                       \
	/** Allocated width in pixels. */                                                                                  \
	int width_a;                                                                                                       \
                                                                                                                       \
	/** Allocated height in pixels. */                                                                                 \
	int height_a;                                                                                                      \
                                                                                                                       \
	/** Callback list. */                                                                                              \
	gg_widget_cb_head_t callbacks;

/** Widget class. */
typedef struct gg_widget {
	GG_WIDGET_DATA
} gg_widget_t;

/** Implements gg_widget::destroy. */
void gg_widget_destroy(gg_widget_t *widget);

/** Implements gg_widget::set_size. */
void gg_set_requested_size(gg_widget_t *widget, int width, int height);

/** Implements gg_widget::get_requested_size. */
void gg_widget_get_requested_size(gg_widget_t *widget, int *width, int *height);

/** Implements gg_widget::get_focus_pos. */
gg_rect_t gg_get_focus_pos(gg_widget_t *widget);

/** Implements gg_widget::set_focus_pos. */
int gg_set_focus_pos(gg_widget_t *widget, int x, int y);

/** @brief Returns the unique class ID of the widget class.
 *
 *  @return Unique class ID.
 */
gg_class_id gg_widget_get_class_id(void);

/** @brief Sets the allocated size of a widget.
 *
 *  @param widget The widget.
 *  @param width The allocated width in pixels.
 *  @param height The allocated height in pixels.
 */
void gg_set_size(gg_widget_t *widget, int width, int height);

/** @brief Initialises a widget. Must be done before calling any class
 *         methods. This function is generally called by a widget creation
 *         function.
 *
 *  @param widget The widget.
 */
void gg_widget_init(gg_widget_t *widget);

struct gg_dialog *gg_widget_find_dialog(gg_widget_t *widget);

/* Signal handling */

typedef int (*gg_widget_cb_t)(gg_widget_t *widget, gg_widget_t *emitter, void *data, void *extra_data);

typedef struct gg_widget_cb_list {
	TAILQ_ENTRY(gg_widget_cb_list) entries;
	gg_signal_t signal;
	void *extra_data;
	gg_widget_cb_t callback;
} gg_widget_cb_list_t;

int gg_widget_subscribe_signal_name(gg_widget_t *widget, gg_class_id id, char *name, gg_widget_cb_t callback,
									void *extra_data);
void gg_widget_subscribe_signal(gg_widget_t *widget, gg_signal_t signal, gg_widget_cb_t callback, void *extra_data);
void gg_widget_emit_signal(gg_widget_t *widget, gg_widget_t *emitter, gg_signal_t signal, void *data);

#endif
