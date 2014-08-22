#include "ld30.h"

#include <darnit/darnit.h>

int main(int argc, char **argv) {
	d_init("LD30", "ld30", NULL);

	for (;;) {
		d_render_begin();
		d_render_end();
		d_loop();
	}

	d_quit();
}
