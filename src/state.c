#include "camera.h"
#include "world.h"
#include "state.h"
#include "level_select.h"
#include "splash.h"
#include "object.h"

struct state_s state;
char levelpack[256];

void state_init() {
	state.cur_state = STATE_DUMMY;
	state.new_state = STATE_LEVELPACK_SELECT;

	return;
}


void state_loop() {
	if (state.cur_state != state.new_state) {
		/* TODO: Fade in/out */
		switch (state.cur_state) {	/* Run state destructors */
			case STATE_LEVEL_SELECT:
				level_select_destroy();
				break;
			case STATE_NEXTLEVEL:
				level_select_destroy();
				break;
			default:
				break;
		}

		switch (state.new_state) {	/* Run state constructors */
			case STATE_LEVELPACK_SELECT:
				d_fs_mount("res/levelpack.ldi");
				sprintf(levelpack, "levelpack.ldi");
				break;
			case STATE_LEVEL_SELECT:
				level_select_init();
				break;
			case STATE_INGAME:
				camera_reset();
				break;
			case STATE_NEXTLEVEL:
				level_select_unlock_next();
				level_select_init();
				break;
			case STATE_ENDOFPACK:
				splash_message("All levels completed!");
				break;
			default:
				break;
		}

		state.cur_state = state.new_state;
	}

	switch (state.cur_state) {
		case STATE_MAINMENU:
			state.new_state = STATE_LEVELPACK_SELECT;
			break;
		case STATE_LEVELPACK_SELECT:
			state.new_state = STATE_LEVEL_SELECT;
			break;
		case STATE_LEVEL_SELECT:
			level_select_loop();
			break;
		case STATE_INGAME:
			camera_loop(1);
			break;
		case STATE_NEXTLEVEL:
			camera_loop(0);
			splash_loop();
			if (d_keys_get().b) {
				object_nuke();
				d_keys_set(d_keys_get());
				if (!(level_select_level(camera_get_level() + 1)))
					state.new_state = STATE_ENDOFPACK;
				else
					state.new_state = STATE_INGAME;
			}
			break;
		case STATE_ENDOFPACK:
			splash_loop();
			if (d_keys_get().b) {
				d_keys_set(d_keys_get());
				state.new_state = STATE_MAINMENU;
			}
		default:
			break;
	}

	return;
}


void state_new(enum state_e new) {
	state.new_state = new;
}


const char *state_levelpack() {
	return levelpack;
}
