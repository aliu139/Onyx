/*
 * compass.h
 */
#pragma once
#include <pebble.h>

int get_heading();

CompassHeadingData get_compass_data();

void init_compass();

void deinit_compass();
