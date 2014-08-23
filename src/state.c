#include "camera.h"
#include "world.h"
#include "state.h"
#include "level_select.h"

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
			default:
				break;
		}

		state.cur_state = state.new_state;
	}

	switch (state.cur_state) {
		case STATE_LEVELPACK_SELECT:
			state.new_state = STATE_LEVEL_SELECT;
			break;
		case STATE_LEVEL_SELECT:
			level_select_loop();
			//state.new_state = STATE_INGAME;
			break;
		case STATE_INGAME:
			camera_loop(1);
			break;
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
