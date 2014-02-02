#include <pebble.h>
#include <pebble_fonts.h>

static Window *window;
static TextLayer *text_layer_title;
static TextLayer *text_layer_commands;
static ScrollLayer *layer_list;
static const char *llista = "Unes peres\r\n" \
	"Un suc\r\n" \
	"Unes taronges\r\n" \
	"Un suc dos\r\n" \
	"Un suc\r\n" \
	"Unes taronges\r\n" \
	"Un suc dos\r\n" \
	"Un suc\r\n" \
	"Unes taronges\r\n" \
	"Un suc dos\r\n" \
	"Un suc\r\n" \
	"Unes taronges\r\n" \
	"Un suc dos\r\n" \
	"";

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer_commands, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer_commands, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer_commands, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  // ctx = app_get_current_graphics_context();

// Set layer for «title»
  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  text_layer_title = text_layer_create((GRect) { .origin = { 0, 0 }, .size = bounds.size });
  text_layer_set_font(text_layer_title,fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(text_layer_title, "Task List");
  text_layer_set_text_alignment(text_layer_title, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer_title));

// Set layer for «commands»
  GSize title_size = text_layer_get_content_size(text_layer_title);
	
  layer_list = scroll_layer_create((GRect) { .origin = {0,title_size.h + 10}, .size = { .h = bounds.size.h - title_size.h - 10, .w = bounds.size.w }});
  layer_add_child(window_layer, scroll_layer_get_layer(layer_list));

  text_layer_commands = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { 100, 400 } });
  text_layer_set_font(text_layer_commands, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(text_layer_commands, llista);
  text_layer_set_text_alignment(text_layer_commands,GTextAlignmentLeft);
  text_layer_set_overflow_mode(text_layer_commands,GTextOverflowModeFill);
  scroll_layer_add_child(layer_list, text_layer_get_layer(text_layer_commands));
  scroll_layer_set_content_size(layer_list, text_layer_get_content_size(text_layer_commands));
  scroll_layer_set_click_config_onto_window(layer_list, window);
}

static void window_unload(Window *window) {
  scroll_layer_destroy(layer_list);
  text_layer_destroy(text_layer_commands);
  text_layer_destroy(text_layer_title);
}

static void init(void) {
  window = window_create();
//  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

/////////////////////////////////////

int main(void) {
  init();
  app_event_loop();
  deinit();
}

