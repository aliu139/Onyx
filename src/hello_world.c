#include <pebble.h>

Window *window;
TextLayer *text_layer;

static GBitmap *s_example_bitmap;
static BitmapLayer *s_bitmap_layer;

void handle_init(void) {
  //GBitmap for the Arrow
  s_example_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ARROW_TRANSPARENT_BLACK);
  s_bitmap_layer = bitmap_layer_create(GRect(2, 7, 137, 142));
  
  bitmap_layer_set_bitmap(s_bitmap_layer, s_example_bitmap);
  
  
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 160, 160));
	
	// Set the text, font, and text alignment
	//text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
	//text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	//text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	text_layer_set_background_color(text_layer, GColorBlack);
  
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

  // Add arrow image
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));

  
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
  // Destroy image
  gbitmap_destroy(s_example_bitmap);
  bitmap_layer_destroy(s_bitmap_layer);

  // Destroy the text layer
	text_layer_destroy(text_layer);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
