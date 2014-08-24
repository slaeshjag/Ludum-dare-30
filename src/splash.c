#include "splash.h"
#include "ld30.h"

struct splash_s splash;

void splash_init() {
	int y_pos;

	y_pos = d_font_glyph_h(ld30.font) / 2;
	y_pos *= -1;
	y_pos += d_platform_get().screen_h / 2;
	splash.splash_bg = d_map_load("res/splash.ldmz");
	splash.message = d_text_surface_new(ld30.font, 256, 760, 20, y_pos);
}


void splash_message(const char *message) {
	d_text_surface_reset(splash.message);
	d_text_surface_string_append(splash.message, message);
	return;
}


void splash_loop() {
	d_tilemap_draw(splash.splash_bg->layer->tilemap);
	d_render_blend_enable();
	d_text_surface_draw(splash.message);
	d_render_blend_disable();
}
