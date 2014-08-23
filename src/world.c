#include "world.h"

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
	if (world.map)
		world_unload();
	if (!(world.map = d_map_load(fname)))
		return 0;
	world.submap = 0;
	return 1;
}


void world_render() {
	d_tilemap_draw(world.map->layer[world.submap].tilemap);

	return;
}


int world_check_pos(int x, int y, int old_x, int old_y) {
	int index;
	/* TODO: Do directional collision checking */

	index = x + y * world.map->layer[world.submap].tilemap->w;
	if (world.map->layer[world.submap].tilemap->data[index] & 0xF0000)
		return 1;
	return 0;
}


const char *world_object_prop(int object, const char *prop) {
	return d_map_prop(world.map->object[object].ref, prop);
}
