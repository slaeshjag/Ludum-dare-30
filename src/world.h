#ifndef __WORLD_H__
#define __WORLD_H__

#include <darnit/darnit.h>

struct world_s {
	DARNIT_MAP			*map;
	int				submap;
};

int world_init();
int world_load(const char *fname);
int world_unload();
void world_render();
int world_check_pos(int x, int y, int old_x, int old_y);
const char *world_object_prop(int object, const char *prop);
void world_tile_dim(int submap, int *w, int *h);
int world_current_submap();
void world_set_submap(int submap);
unsigned int world_get_tile(int x, int y, int submap);


extern struct world_s world;

#endif
