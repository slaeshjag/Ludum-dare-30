#ifndef __STATE_H__
#define	__STATE_H__

enum state_e {
	STATE_DUMMY,
	STATE_MAINMENU,
	STATE_LEVELPACK_SELECT,
	STATE_LEVEL_SELECT,
	STATE_INGAME,
	STATE_PAUSEMENU,
	STATE_NEXTLEVEL,
};


struct state_s {
	enum state_e		cur_state;
	enum state_e		new_state;
};

void state_init();
void state_loop();
void state_new(enum state_e new);
const char *state_levelpack();

#endif
