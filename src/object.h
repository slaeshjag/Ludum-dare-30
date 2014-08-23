#ifndef __OBJECT_H__
#define	__OBJECT_H__

#include <darnit/darnit.h>

enum object_type_e {
	OBJECT_TYPE_MOVABLE,
};


struct object_entry_s {
	int			x;
	int			y;
	int			submap;
	
	DARNIT_SPRITE		*sprite;
	
	enum object_type_e	type;
	/* I'll clean up memory later... */
	int			active;

	char			*name;
	const char		*connects;
};


struct object_s {
	struct object_entry_s	*object;
	int			objects;
};

extern struct object_s obj;

void object_init();
int object_spawn(int object_id, const char *name);
int object_logic_loop(int id);
void object_render();
int object_find(const char *name);
int object_get_connecting(int object);
int object_find_next_head(int start, int dir);
int object_submap(int id);
void object_pos(int id, int *x, int *y);
int object_submap(int id);

#endif
