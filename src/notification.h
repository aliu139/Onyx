/*
 * message.h
 */
#pragma once
#include <pebble.h>

//Reset a notification, also sends long pulse notification
void reset_notification();

//Check if we should notify with a vibrate
void check_notification(int distance);
