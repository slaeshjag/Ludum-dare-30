#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <darnit/darnit.h>

#define	TANGLE_MAX	32


struct camera_s {
	int			x;
	int			y;
	int			current_obj;
	int			tangle_stack[TANGLE_MAX];
	int			tangle_pos;

	int			current_level;
	DARNIT_TILESHEET	*arrow;
};

void camera_init();
void camera_reset();
void camera_loop(int interactive);
void camera_set_level(int level);
int camera_get_level();

#endif
