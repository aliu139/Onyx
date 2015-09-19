/*#include "pebble.h"
static Window *s_main_window;
static TextLayer *s_heading_layer, *s_text_layer_calib_state;
*/
static int compassHeading;

static void compass_heading_handler(CompassHeadingData heading_data){
	compassHeading = TRIGANGLE_TO_DEG(heading_data.magnetic_heading);
	/*static char str[15];
	snprintf(str, sizeof(str), "%d", compassHeading);
	text_layer_set_text(s_heading_layer, str);
	
	GRect bounds = layer_get_frame(window_get_root_layer(s_main_window));
	GRect alert_bounds;
	if(heading_data.compass_status == CompassStatusDataInvalid) {
    // Tell user to move their arm
    alert_bounds = GRect(0, 0, bounds.size.w, bounds.size.h);
    text_layer_set_background_color(s_text_layer_calib_state, GColorBlack);
    text_layer_set_text_color(s_text_layer_calib_state, GColorWhite);
    text_layer_set_font(s_text_layer_calib_state, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_text_layer_calib_state, GTextAlignmentCenter);
	} else {
    // Show status at the top
    alert_bounds = GRect(0, -3, bounds.size.w, bounds.size.h / 7);
    text_layer_set_background_color(s_text_layer_calib_state, GColorClear);
    text_layer_set_text_color(s_text_layer_calib_state, GColorBlack);
    text_layer_set_font(s_text_layer_calib_state, fonts_get_system_font(FONT_KEY_GOTHIC_18));
    text_layer_set_text_alignment(s_text_layer_calib_state, GTextAlignmentLeft);
	}
	layer_set_frame(text_layer_get_layer(s_text_layer_calib_state), alert_bounds);

	if(heading_data.compass_status == CompassStatusDataInvalid) {
    // Tell user to move their arm
    alert_bounds = GRect(0, 0, bounds.size.w, bounds.size.h);
    text_layer_set_background_color(s_text_layer_calib_state, GColorBlack);
    text_layer_set_text_color(s_text_layer_calib_state, GColorWhite);
    text_layer_set_font(s_text_layer_calib_state, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_text_layer_calib_state, GTextAlignmentCenter);
	} else {
    // Show status at the top
    alert_bounds = GRect(0, -3, bounds.size.w, bounds.size.h / 7);
    text_layer_set_background_color(s_text_layer_calib_state, GColorClear);
    text_layer_set_text_color(s_text_layer_calib_state, GColorBlack);
    text_layer_set_font(s_text_layer_calib_state, fonts_get_system_font(FONT_KEY_GOTHIC_18));
    text_layer_set_text_alignment(s_text_layer_calib_state, GTextAlignmentLeft);
	}
	layer_set_frame(text_layer_get_layer(s_text_layer_calib_state), alert_bounds);
*/	
}

/*static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Place text layers onto screen: one for the heading and one for calibration status
  s_heading_layer = text_layer_create(GRect(12, bounds.size.h * 3 / 4, bounds.size.w / 4, bounds.size.h / 5));
  text_layer_set_text(s_heading_layer, "No Data");
  layer_add_child(window_layer, text_layer_get_layer(s_heading_layer));

  s_text_layer_calib_state = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h / 7));
  text_layer_set_text_alignment(s_text_layer_calib_state, GTextAlignmentLeft);
  text_layer_set_background_color(s_text_layer_calib_state, GColorClear);

  layer_add_child(window_layer, text_layer_get_layer(s_text_layer_calib_state));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_heading_layer);
  text_layer_destroy(s_text_layer_calib_state);
}
*/
static void initCompass(){
	compass_service_set_heading_filter(2* (TRIG_MAX_ANGLE / 360));
	compass_service_subscribe(&compass_heading_handler);
	
	/*s_main_window = window_create();
	window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
	});
	window_stack_push(s_main_window, true);*/
}

static void deinitCompass(){
	compass_service_unsubscribe();
	window_destroy(s_main_window);
}

int main(){
	initCompass();
	app_event_loop();
	deinitCompass();
}
