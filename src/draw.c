/*
 * draw.c
 */

#include "draw.h"
#include "compass.h"

#define ARROW_MARGIN 20
#define ARROW_IN 10

static void mark_dirty(void* layer) {
	layer_mark_dirty(layer);
}

// Draw line with width
// (Based on code found here http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C)
static void graphics_draw_line2(GContext *ctx, GPoint p0, GPoint p1,
		int8_t width) {
	// Order points so that lower x is first
	int16_t x0, x1, y0, y1;
	if (p0.x <= p1.x) {
		x0 = p0.x;
		x1 = p1.x;
		y0 = p0.y;
		y1 = p1.y;
	} else {
		x0 = p1.x;
		x1 = p0.x;
		y0 = p1.y;
		y1 = p0.y;
	}

	// Init loop variables
	int16_t dx = x1 - x0;
	int16_t dy = abs(y1 - y0);
	int16_t sy = y0 < y1 ? 1 : -1;
	int16_t err = (dx > dy ? dx : -dy) / 2;
	int16_t e2;

	// Calculate whether line thickness will be added vertically or horizontally based on line angle
	int8_t xdiff, ydiff;

	if (dx > dy) {
		xdiff = 0;
		ydiff = width / 2;
	} else {
		xdiff = width / 2;
		ydiff = 0;
	}

	// Use Bresenham's integer algorithm, with slight modification for line width, to draw line at any angle
	while (true) {
		// Draw line thickness at each point by drawing another line
		// (horizontally when > +/-45 degrees, vertically when <= +/-45 degrees)
		graphics_draw_line(ctx, GPoint(x0 - xdiff, y0 - ydiff),
				GPoint(x0 + xdiff, y0 + ydiff));

		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x0++;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}

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
	graphics_draw_line2(ctx, c_point, l_point, 5);
	graphics_draw_line2(ctx, c_point, r_point, 5);
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
	int32_t angle = get_heading();
	draw_arrow(ctx, angle, s_radius, center);
  
  // Draw Text
  char str[10];
  snprintf(str, sizeof(str), "%d", get_heading());
  graphics_context_set_text_color(ctx, GColorBlack);
  graphics_draw_text(ctx, str, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK)
                     , bounds, GTextOverflowModeTrailingEllipsis
                     , GTextAlignmentCenter, NULL);

	redraw_timer = app_timer_register(50, mark_dirty, this_layer);
}
