/*
 * compass.c
 */
#include "compass.h"
static int compass_heading;

static void compass_heading_handler(CompassHeadingData heading_data) {
	compass_heading = TRIGANGLE_TO_DEG(heading_data.magnetic_heading);
}

int get_heading() {
	return compass_heading;
}

void init_compass() {
	compass_service_set_heading_filter(2 * (TRIG_MAX_ANGLE / 360));
	compass_service_subscribe(&compass_heading_handler);
}

void deinit_compass() {
	compass_service_unsubscribe();
}
