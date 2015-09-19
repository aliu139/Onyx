/*
 * notification.c
 */
#include "notification.h"

#define NOTIFY_DISTANCE 20
#define RESET_DISTANCE 40

int notified = 0; //if user has been notified

void reset_notification(){
	notified = 0;
	vibes_long_pulse();
	light_enable_interaction();
}

void check_notification(int distance){
	if(notified == 0 && distance < NOTIFY_DISTANCE){
		notified = 1;
		vibes_double_pulse();
		light_enable_interaction();
	} else if (notified == 1 && distance > RESET_DISTANCE){
		reset_notification();
	}
}
