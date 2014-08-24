#include "ld30.h"
#include "object.h"
#include "world.h"
#include "camera.h"
#include "state.h"
#include "splash.h"

#include <darnit/darnit.h>
/* Connected worlds, eh? Will take a couple minutes for me to figure that one
	out ... */
/* I think I might have an idea.. */

struct ld30_s ld30;

int init() {
	DARNIT_INPUT_MAP map;
	d_fs_mount_self();
	ld30.font = d_font_load("res/font.ttf", 28, 128, 128);
	object_init();
	world_init();
	camera_init();
	state_init();
	splash_init();
	
	if (!(d_platform_get().platform & DARNIT_PLATFORM_PANDORA)) {
		map = d_keymapping_get();
		map.b = TPW_KEY_RETURN;
		map.a = TPW_KEY_ESCAPE;
		d_keymapping_set(map);
	}

	return 1;
}


int main(int argc, char **argv) {
	d_init("Unrequited Entanglement", "unreq_entangle", NULL);
	init();
	
	for (;;) {
		d_render_begin();
		state_loop();
		d_render_end();
		d_loop();
	}

	d_quit();
}
