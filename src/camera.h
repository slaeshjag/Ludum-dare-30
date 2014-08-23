#ifndef __CAMERA_H__
#define __CAMERA_H__

#define	TANGLE_MAX	32

struct camera_s {
	int		x;
	int		y;
	int		current_obj;
	int		tangle_stack[TANGLE_MAX];
	int		tangle_pos;
};

void camera_init();
void camera_loop();

#endif
