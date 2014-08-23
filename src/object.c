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
	
	return objn;
}


int object_find(const char *name) {
	int i;

	for (i = 0; i < obj.objects; i++)
		if (!strcmp(obj.object[i].name, name))
			return i;
	fprintf(stderr, "Unable to find object %s\n", name);
	return -1;
}
