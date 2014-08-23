#include <darnit/darnit.h>

#include "camera.h"
#include "world.h"
#include "object.h"


struct camera_s camera;


void camera_init() {
	camera.x = camera.y = 0;
	camera.tangle_pos = 0;
	/* Arne is always the focus in a new game/level */
	camera.current_obj = object_find("Arne");
	return;
}


void camera_loop() {
	int n;
	DARNIT_KEYS k;

	if (d_keys_get().r) {
		if ((n = object_get_connecting(camera.current_obj)) >= 0) {
			camera.tangle_stack[camera.tangle_pos++] = camera.current_obj;
			camera.current_obj = n;
		}
		k = d_keys_zero();
		k.r = 1;
		d_keys_set(k);
	} else if (d_keys_get().l) {
		if (camera.tangle_pos > 0) {
			camera.current_obj = camera.tangle_stack[--camera.tangle_pos];
		}
		k = d_keys_zero();
		k.l = 1;
		d_keys_set(k);
	} else if (d_keys_get().x || d_keys_get().y) {
		camera.current_obj = object_find_next_head(camera.current_obj, d_keys_get().y ? 1 : -1);
		camera.tangle_pos = 0;
	}

	object_logic_loop(camera.current_obj);
	world_render();
	object_render(world_current_submap());
}
