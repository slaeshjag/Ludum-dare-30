#include <string.h>

#include "level_select.h"
#include "ld30.h"
#include "state.h"
#include "world.h"
#include "camera.h"

struct level_select_s l_select;


void level_select_unlock_next() {
	int level;
	DARNIT_FILE *f;
	char progress[256];

	level = camera_get_level();
	level += 2;

	sprintf(progress, "%s.progress", state_levelpack());
	f = d_file_open(progress, "w");
	d_file_write_ints(&level, 1, f);
	d_file_close(f);
	return;
}


void level_select_adjust_limit() {
	const char *levelpack = state_levelpack();
	char progress[256], *next;
	int max_level, i;
	DARNIT_FILE *f;

	sprintf(progress, "%s.progress", levelpack);
	if (!(f = d_file_open(progress, "r"))) {
		if (!f)
			fprintf(stderr, "Unable to open progress file %s\n", progress);
		max_level = 1;
	} else {
		d_file_read_ints(&max_level, 1, f);
		d_file_close(f);
	}
	
	next = l_select.level_list;
	for (i = 0; i < max_level && next; i++) {
		next = strchr(next, '\n');
		if (next)
			next++;
	}

	if (next) {
		next--;
		*next = 0;
	}

	return;
}





void level_select_init() {
	size_t len;
	DARNIT_FILE *f;

	if (!(f = d_file_open("levels/levels.index", "r"))) {
		fprintf(stderr, "No level index file\n");
		state_new(STATE_LEVELPACK_SELECT);
		l_select.menu_select = NULL;
		l_select.level_list = NULL;
		/* TODO: Play error-sound */
		return;
	}

	d_file_seek(f, 0, SEEK_END);
	len = d_file_tell(f);
	d_file_seek(f, 0, SEEK_SET);

	l_select.level_list = malloc(len + 1);
	d_file_read(l_select.level_list, len, f);
	l_select.level_list[len] = 0;
	if (l_select.level_list[len - 1] == '\n')
		l_select.level_list[len - 1] = 0;
	level_select_adjust_limit();

	l_select.menu_select = d_menu_vertical_new(l_select.level_list, 200, 100, ld30.font, 400, 10, 300);

	d_file_close(f);

	return;
}


void level_select_get_line(int pos, char *buff) {
	int i, len;
	char *next;

	next = l_select.level_list;
	for (i = 0; i < pos && next; i++) {
		next = strchr(next, '\n');
		if (next)
			next++;
	}

	if (i != pos || !next) {
		*buff = 0;
		return;
	}

	if (!strchr(next, '\n'))
		strcpy(buff, next);
	else {
		len = strchr(next, '\n') - next;
		memcpy(buff, next, len);
		buff[len] = 0;
	}

	return;
}


int level_select_level(int num) {
	char selection[256];
	
	level_select_get_line(num, selection);
	if (!(*selection))
		return 0;
	world_load(selection);
	state_new(STATE_INGAME);
	camera_set_level(num);

	return 1;
}


void level_select_loop() {
	int res;

	if (!l_select.menu_select)
		return;
	d_render_blend_enable();
	res = d_menu_loop(l_select.menu_select);
	d_render_blend_disable();

	if (res == -2) {
		/* TODO: Play back-sound */
		state_new(STATE_LEVELPACK_SELECT);
	} else if (res >= 0) {
		level_select_level(res);
	}

	return;
}


void level_select_destroy() {
	l_select.menu_select = d_menu_free(l_select.menu_select);

	return;
}
