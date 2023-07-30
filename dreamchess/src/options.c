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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "dir.h"
#include "options.h"
#include "xml.h"

static char *remove_spaces(const char *str) {
	char *sc = strdup(str);
	char *s = sc;

	while (*s) {
		if (*s == ' ')
			*s = '_';
		s++;
	}

	return sc;
}

option_group_t *option_group_create(const char *name) {
	option_group_t *group = malloc(sizeof(option_group_t));

	group->name = remove_spaces(name);
	TAILQ_INIT(&group->options);
	return group;
}

option_t *option_group_add_option(option_group_t *group, const char *name) {
	option_t *option = malloc(sizeof(option_t));

	option->type = OPTION_TYPE_OPTION;
	option->name = remove_spaces(name);
	option->selected = NULL;
	option->size = 0;
	TAILQ_INIT(&option->values);
	TAILQ_INSERT_TAIL(&group->options, option, entries);
	return option;
}

option_t *option_group_add_int(option_group_t *group, const char *name) {
	option_t *option = malloc(sizeof(option_t));

	option->type = OPTION_TYPE_INT;
	option->name = remove_spaces(name);
	TAILQ_INSERT_TAIL(&group->options, option, entries);
	return option;
}

option_t *option_group_add_string(option_group_t *group, const char *name) {
	option_t *option = malloc(sizeof(option_t));

	option->type = OPTION_TYPE_STRING;
	option->name = remove_spaces(name);
	option->string = NULL;
	TAILQ_INSERT_TAIL(&group->options, option, entries);
	return option;
}

static void option_group_save(option_group_t *group, FILE *f) {
	option_t *option;

	fputs("<?xml version=\"1.0\"?>\n<options>\n", f);

	TAILQ_FOREACH(option, &group->options, entries) {
		fprintf(f, "<%s>", option->name);

		if (option->type == OPTION_TYPE_OPTION)
			fputs(option->selected->name, f);
		else if (option->type == OPTION_TYPE_INT)
			fprintf(f, "%d", option->value);
		else
			fputs(option->string, f);

		fprintf(f, "</%s>\n", option->name);
	}

	fputs("</options>\n", f);
}

int option_group_save_xml(option_group_t *group) {
	FILE *f;
	char *filename;
	int error = 0;

	filename = malloc(strlen(group->name) + 4 + 1);
	strcpy(filename, group->name);
	strcat(filename, ".xml");

	ch_userdir();
	f = fopen(filename, "w");

	if (!f) {
		DBG_ERROR("Failed to open '%s'", filename);
		free(filename);
		return -1;
	}

	option_group_save(group, f);

	if (ferror(f)) {
		DBG_ERROR("Failed to write '%s'", filename);
		error = -1;
	}

	free(filename);
	fclose(f);

	return error;
}

static void option_cb(void *user_data, const char *element, char *const *attrs, const char *text) {
	option_t *option;
	option_group_t *group = (option_group_t *)user_data;

	option = option_group_find_option(group, element);
	if (!option) {
		printf("Option '%s' does not exist", element);
		return;
	}

	if (option->type == OPTION_TYPE_OPTION) {
		if (option_select_value_by_name(option, text) == -1)
			printf("Option '%s' has no value '%s'", element, text);
		DBG_LOG("Setting option '%s' to '%s'", element, text);
	} else if (option->type == OPTION_TYPE_INT) {
		int val;

		errno = 0;
		val = strtol(text, NULL, 10);
		if (errno) {
			printf("Value '%s' for option '%s' is not an integer", text, element);
		} else {
			option->value = val;
		}
	} else
		option->string = strdup(text);
}

int option_group_load_xml(option_group_t *group) {
	char *filename;
	int retval = 0;

	filename = malloc(strlen(group->name) + 4 + 1);
	strcpy(filename, group->name);
	strcat(filename, ".xml");

	if (xml_parse(filename, "options", option_cb, NULL, NULL, group)) {
		DBG_ERROR("Failed to parse '%s'", filename);
		retval = -1;
	}

	free(filename);
	return retval;
}

void option_add_value(option_t *option, const char *name, void *data) {
	option_value_t *value = malloc(sizeof(option_value_t));

	value->name = strdup(name);
	value->data = data;
	value->index = option->size++;
	TAILQ_INSERT_TAIL(&option->values, value, entries);
	if (option->size == 1)
		option->selected = value;
}

int option_select_value_by_name(option_t *option, const char *name) {
	option_value_t *value;

	TAILQ_FOREACH(value, &option->values, entries) {
		if (!strcmp(value->name, name))
			break;
	}

	if (value) {
		option->selected = value;
		return 0;
	}

	return -1;
}

int option_select_value_by_index(option_t *option, int index) {
	option_value_t *value;

	TAILQ_FOREACH(value, &option->values, entries) {
		if (index-- == 0)
			break;
	}

	if (value) {
		option->selected = value;
		return 0;
	}

	return -1;
}

int option_select_next_value(option_t *option) {
	if (!option->selected)
		return -1;

	if (!TAILQ_NEXT(option->selected, entries))
		return -1;

	option->selected = TAILQ_NEXT(option->selected, entries);
	return 0;
}

int option_select_prev_value(option_t *option) {
	if (!option->selected)
		return -1;

	if (!TAILQ_PREV(option->selected, values_head, entries))
		return -1;

	option->selected = TAILQ_PREV(option->selected, values_head, entries);
	return 0;
}

option_t *option_group_find_option(option_group_t *group, const char *name) {
	char *namews = remove_spaces(name);
	option_t *option;

	TAILQ_FOREACH(option, &group->options, entries) {
		if (!strcmp(option->name, namews))
			break;
	}

	free(namews);
	return option;
}

void option_string_set_text(option_t *option, const char *text) {
	if (option->string)
		free(option->string);

	option->string = strdup(text);
}
