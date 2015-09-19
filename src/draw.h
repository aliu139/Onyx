/*
 * draw.h
 * In charge of drawing
 */
#pragma once
#include <pebble.h>

void draw_arrow(GContext *ctx, int32_t angle, int32_t radius, GPoint center);

void canvas_update_proc(Layer *this_layer, GContext *ctx);
