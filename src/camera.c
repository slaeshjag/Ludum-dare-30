#include <darnit/darnit.h>
#include <math.h>

#include "camera.h"
#include "world.h"
#include "object.h"


struct camera_s camera;


void camera_init() {
	camera.arrow = d_render_tilesheet_load("res/arrow.png", 32, 32, DARNIT_PFORMAT_RGB5A1);
	return;
}


void camera_reset() {
	camera.x = camera.y = 0;
	camera.tangle_pos = 0;
	/* Arne is always the focus in a new game/level */
	camera.current_obj = object_find("Arne");
	return;
}


void camera_loop(int interactive) {
	int n, arrow_x, arrow_y;
	DARNIT_KEYS k;

	if (d_keys_get().r) {
		if ((n = object_get_connecting(camera.current_obj)) >= 0) {
			camera.tangle_stack[camera.tangle_pos++] = camera.current_obj;
			camera.current_obj = n;
			world_set_submap(object_submap(camera.current_obj));
		}
		k = d_keys_zero();
		k.r = 1;
		d_keys_set(k);
	} else if (d_keys_get().l) {
		if (camera.tangle_pos > 0) {
			camera.current_obj = camera.tangle_stack[--camera.tangle_pos];
			world_set_submap(object_submap(camera.current_obj));
		}
		k = d_keys_zero();
		k.l = 1;
		d_keys_set(k);
	} else if (d_keys_get().x || d_keys_get().y) {
		camera.current_obj = object_find_next_head(camera.current_obj, d_keys_get().y ? 1 : -1);
		camera.tangle_pos = 0;
	}

	if (interactive)
		object_logic_loop(camera.current_obj);
	world_render();
	object_render(world_current_submap());

	object_pos(camera.current_obj, &arrow_x, &arrow_y);
	arrow_y -= (32 + 8);
	arrow_y += sinf(0.01 * d_time_get()) * 8;
	d_render_blend_enable();
	d_render_tile_blit(camera.arrow, 0, arrow_x, arrow_y);
	d_render_blend_disable();
}


void camera_set_level(int level) {
	camera.current_level = level;
}


int camera_get_level() {
	return camera.current_level;
}
