#ifndef __LEVEL_SELECT_H__
#define	__LEVEL_SELECT_H__

#include <darnit/darnit.h>

struct level_select_s {
	DARNIT_MENU		*menu_select;
	char			*level_list;
};

void level_select_init();
void level_select_destroy();
void level_select_loop();
int level_select_level(int num);
void level_select_unlock_next();


#endif
