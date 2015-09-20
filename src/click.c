#include "click.h"

static void send_int(int key, int value) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_int(iter, key, &value, sizeof(int), true);
  app_message_outbox_send();
}
  
// Deal with single down click
static void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(12, 1);
}

// Deal with single up click
static void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(11, 1);   
}


void click_config(Window *window) {
  // single click
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
}