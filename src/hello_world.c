/*
 * main.c
 * Creates a Window, Layer and assigns an `update_proc` to draw
 * the 'P' in the Pebble logo.
 */

#include <pebble.h>
#define ARROW_MARGIN 15

static Window *s_main_window;
static Layer *s_canvas_layer;

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);

  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

  int s_radius = 70;

  // Draw the 'loop' of the 'P'
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, center, s_radius);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, s_radius-5);

  // Draw the 'arrow'
  int angle = 40;
  int lAngle = angle - 30;
  int rAngle = angle + 30;

    // Plot hands
  GPoint c_point = (GPoint) {
    .x = (int16_t)(sin_lookup(angle) * (int32_t)(s_radius - ARROW_MARGIN) / 360) + center.x,
    .y = (int16_t)(-cos_lookup(angle) * (int32_t)(s_radius - ARROW_MARGIN) / 360) + center.y,
  };

    GPoint l_point = (GPoint) {
    .x = (int16_t)(sin_lookup(lAngle) * (int32_t)(s_radius - ARROW_MARGIN) / 360) + center.x,
    .y = (int16_t)(-cos_lookup(lAngle) * (int32_t)(s_radius - ARROW_MARGIN) / 360) + center.y,
  };

  GPoint r_point = (GPoint) {
    .x = (int16_t)(sin_lookup(rAngle) * (int32_t)(s_radius - ARROW_MARGIN) / 360) + center.x,
    .y = (int16_t)(-cos_lookup(rAngle) * (int32_t)(s_radius - ARROW_MARGIN) / 360) + center.y,
  };



  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_draw_line(ctx, c_point, l_point);
  graphics_draw_line(ctx, c_point, r_point);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
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
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit(void) {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
