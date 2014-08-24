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
	DARNIT_TEXT_SURFACE	*hint_text;
	DARNIT_TEXT_SURFACE	*entangle_text;
};

void camera_init();
void camera_reset();
void camera_loop(int interactive);
void camera_set_level(int level);
int camera_get_level();
void camera_set_hint(const char *str);


#endif
