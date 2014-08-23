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

#endif
