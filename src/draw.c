/*
 * draw.c
 */

#include "draw.h"

#define ARROW_MARGIN 15
#define ARROW_IN 10

void draw_arrow(GContext *ctx, int32_t angle, int32_t radius, GPoint center) {
	int32_t lAngle = angle - 40;
	int32_t rAngle = angle + 40;

	// Plot hands
	GPoint c_point = (GPoint ) {
		.x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * angle/360) * (int32_t)(radius - ARROW_MARGIN) / TRIG_MAX_ANGLE) + center.x,
		.y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * angle/360) * (int32_t)(radius - ARROW_MARGIN) / TRIG_MAX_ANGLE) + center.y,
	};

	GPoint l_point = (GPoint ) {
		.x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * lAngle/360) * (int32_t)(radius - ARROW_MARGIN - ARROW_IN) / TRIG_MAX_ANGLE) + center.x,
		.y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * lAngle/360) * (int32_t)(radius - ARROW_MARGIN - ARROW_IN) / TRIG_MAX_ANGLE) + center.y,
	};

	GPoint r_point = (GPoint ) {
		.x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * rAngle/360) * (int32_t)(radius - ARROW_MARGIN - ARROW_IN) / TRIG_MAX_ANGLE) + center.x,
		.y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * rAngle/360) * (int32_t)(radius - ARROW_MARGIN - ARROW_IN) / TRIG_MAX_ANGLE) + center.y,
	};

	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_draw_line(ctx, c_point, l_point);
	graphics_draw_line(ctx, c_point, r_point);
}

void canvas_update_proc(Layer *this_layer, GContext *ctx) {
	GRect bounds = layer_get_bounds(this_layer);

	// Get the center of the screen (non full-screen)
	GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

	int32_t s_radius = 70;

	// Draw a circle
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_circle(ctx, center, s_radius);
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_circle(ctx, center, s_radius - 5);

	// TODO: Find angle for arrow
	int32_t angle = 0;

	draw_arrow(ctx, angle, s_radius, center);
}
