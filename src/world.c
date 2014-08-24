#include <string.h>
#include "world.h"
#include "object.h"
#include "camera.h"

struct world_s world;

int world_init() {
	world.map = NULL;
	return 1;
}


int world_unload() {
	if (!world.map)
		return 1;
	world.map = d_map_unload(world.map);
	return 1;
}


int world_load(const char *fname) {
	int i;
	const char *hint;
	if (world.map)
		world_unload();
	if (!(world.map = d_map_load(fname)))
		return 0;
	world.submap = 0;

	for (i = 0; i < world.map->objects; i++) {
		object_spawn(i, world_object_prop(i, "NAME"));
	}

	if (d_platform_get().platform & DARNIT_PLATFORM_PANDORA)
		hint = d_map_prop(world.map->prop, "hint_pandora");
	else
		hint = d_map_prop(world.map->prop, "hint");
	if (!strcmp(hint, "NO SUCH KEY"))
		hint = "";
	camera_set_hint(hint);

	return 1;
}


void world_render() {
	d_tilemap_draw(world.map->layer[world.submap].tilemap);

	return;
}


int world_check_pos(int x, int y, int old_x, int old_y) {
	int index;
	/* TODO: Do directional collision checking */

	if (x < 0 || y < 0) return 1;
	if (x > world.map->layer[world.submap].tilemap->w) return 1;
	if (y > world.map->layer[world.submap].tilemap->h) return 1;

	index = x + y * world.map->layer[world.submap].tilemap->w;
	if (world.map->layer[world.submap].tilemap->data[index] & 0xF0000)
		return 1;
	return 0;
}


unsigned int world_get_tile(int x, int y, int submap) {
	int index;

	if (x < 0 || y < 0) return 0;
	if (x > world.map->layer[submap].tilemap->w) return 0;
	if (y > world.map->layer[submap].tilemap->h) return 0;
	index = x + y * world.map->layer[world.submap].tilemap->w;
	return world.map->layer[submap].tilemap->data[index];
}


const char *world_object_prop(int object, const char *prop) {
	return d_map_prop(world.map->object[object].ref, prop);
}


void world_tile_dim(int submap, int *w, int *h) {
	*w = world.map->layer[submap].tile_w;
	*h = world.map->layer[submap].tile_h;

	return;
}


int world_current_submap() {
	return world.submap;
}


void world_set_submap(int submap) {
	world.submap = submap;
	return;
}
