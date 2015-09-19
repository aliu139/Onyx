/*
 * main.c
 * Creates a Window, Layer, calls for drawing
 */

#include <pebble.h>
#include "draw.h"
#include "compass.h"

#define ARROW_MARGIN 15
#define ARROW_IN 10

static Window *s_main_window;
static Layer *s_canvas_layer;

static void main_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect window_bounds = layer_get_bounds(window_layer);

	// Create Layer
	s_canvas_layer = layer_create(
			GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
	layer_add_child(window_layer, s_canvas_layer);

	// Set the update_proc
	layer_set_update_proc(s_canvas_layer, canvas_update_proc);
}

static void main_window_unload(Window *window) {
	// Destroy Layer
	layer_destroy(s_canvas_layer);
}

static void init(void) {
	// Create main Window
	s_main_window = window_create();
	window_set_window_handlers(s_main_window, (WindowHandlers ) {
		.load = main_window_load,
		.unload = main_window_unload,
	});
	window_stack_push(s_main_window, true);
	init_compass();
    init_message();
}

// Destroy main Window
static void deinit(void) {
	deinit_compass();
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
