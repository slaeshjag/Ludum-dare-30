#include "ld30.h"
#include "object.h"
#include "world.h"

#include <darnit/darnit.h>
/* Connected worlds, eh? Will take a couple minutes for me to figure that one
	out ... */
/* I think I might have an idea.. */

int init() {
	object_init();
	world_init();

	return 1;
}


int main(int argc, char **argv) {
	d_init("LD30", "ld30", NULL);
	init();

	world_load("res/testmap.ldmz");

	for (;;) {
		d_render_begin();
		world_render();
		d_render_end();
		d_loop();
	}

	d_quit();
}
