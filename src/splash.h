#ifndef __SPLASH_H__
#define	__SPLASH_H__

#include <darnit/darnit.h>

struct splash_s {
	DARNIT_MAP		*splash_bg;
	DARNIT_TEXT_SURFACE	*message;
};


void splash_init();
void splash_message(const char *message);
void splash_loop();

#endif
