#define	DECLARE_HACK
#include "object.h"
#include "world.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct object_s obj;

void object_init() {
	obj.object = NULL, obj.objects = 0;
}


void object_update_pos(int id) {
	int tile_w, tile_h;

	world_tile_dim(obj.object[id].submap, &tile_w, &tile_h);
	d_sprite_move(obj.object[id].sprite, obj.object[id].x * tile_w, obj.object[id].y * tile_h);
}


int object_spawn(int object_id, const char *name) {
	int objn;
	
	objn = obj.objects++;
	obj.object = realloc(obj.object, sizeof(*obj.object) * obj.objects);

	obj.object[objn].sprite = d_sprite_load(world_object_prop(object_id, "sprite"), 0, DARNIT_PFORMAT_RGB5A1);
	obj.object[objn].x = world.map->object[object_id].x; 
	obj.object[objn].y = world.map->object[object_id].y;
	obj.object[objn].submap = world.map->object[object_id].l;

	obj.object[objn].active = 1;
	obj.object[objn].name = strdup(name);

	obj.object[objn].connects = world_object_prop(object_id, "connects");
	object_update_pos(objn);
	
	return objn;
}


int object_find(const char *name) {
	int i;

	for (i = 0; i < obj.objects; i++)
		if (!strcmp(obj.object[i].name, name))
			return i;
	return -1;
}


int object_get_connecting(int object) {
	return object_find(obj.object[object].connects);
}


int object_find_next_head(int start, int dir) {
	int i;

	for (i = 0;; i += dir) {
		if (!strcmp(world_object_prop(i, "head"), "head"))
			return i;
		if (obj.objects == i + dir)
			i = 0;
		if (i + dir < 0)
			i = obj.objects;
	}

	/* Should never happen */
	return -1;
}


int object_move_try(int self, int dx, int dy, int tangle) {
	int id, x, y;

	x = obj.object[self].x, y = obj.object[self].y;
	if (world_check_pos(x + dx, y + dy, x, y))	/* Unable to move */
		return 0;
	obj.object[self].x += dx, obj.object[self].y += dy;
	object_update_pos(self);

	if ((id = object_get_connecting(self)) < 0)
		return 1;
	return object_move_try(id, dx, dy, 1);
}


int object_logic_loop(int id) {
	int dx, dy;
	DARNIT_KEYS k;
	dx = dy = 0;

	if (d_keys_get().left) dx = -1, k = d_keys_zero(), k.left = 1, d_keys_set(k);
	if (d_keys_get().right) dx = 1, k = d_keys_zero(), k.right = 1, d_keys_set(k);
	if (d_keys_get().up) dy = -1, k = d_keys_zero(), k.up = 1, d_keys_set(k);
	if (d_keys_get().down) dy = 1, k = d_keys_zero(), k.down = 1, d_keys_set(k);

	if (!dx && !dy)
		return -1;

	return object_move_try(id, dx, dy, 0);
}



void object_render() {
	int i, submap;

	submap = world_current_submap();
	for (i = 0; i < obj.objects; i++) {
		if (obj.object[i].submap != submap)
			continue;
		if (!obj.object[i].active)
			continue;
		d_sprite_draw(obj.object[i].sprite);
	}

	return;
}


void object_pos(int id, int *x, int *y) {
	*x = obj.object[id].x * 32;
	*y = obj.object[id].y * 32;

	return;
}


int object_submap(int id) {
	return obj.object[id].submap;
}
