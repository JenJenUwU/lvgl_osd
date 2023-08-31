#ifndef LV_MENU_OBJ_H
#define LV_MENU_OBJ_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif
enum { LV_MENU_ITEM_BUILDER_VARIANT_1, LV_MENU_ITEM_BUILDER_VARIANT_2 };
typedef uint8_t lv_menu_builder_variant_t;
lv_obj_t *slider_label;
lv_obj_t *dropdown_label;
char int_to_str_buffer[16];
const char *int_to_str(int32_t num);
void btn_event_cb(lv_event_t *e);
void dropdown_event_cb(lv_event_t *e);
void slider_event_cb(lv_event_t *e);
void switch_event_cb(lv_event_t *e);
void slider_event_label_cb(lv_event_t *e);
// void back_event_handler(lv_event_t *e);
// void switch_handler(lv_event_t *e);
void focus_event_cb();
lv_obj_t *create_text(lv_obj_t *parent, const char *icon, const char *txt,
                             lv_menu_builder_variant_t builder_variant);
lv_obj_t *create_slider(lv_obj_t *parent, const char *icon, const char *txt, int32_t min,
                               int32_t max, int32_t val);
lv_obj_t *create_switch(lv_obj_t *parent, const char *icon, const char *txt, bool chk);
lv_obj_t *create_dropdown(lv_obj_t *parent, const char *icon, const char *txt,
                                 const char *options, int32_t val);
lv_obj_t *create_button(lv_obj_t *parent, const char *icon, const char *txt,
                               const char *btn_text);

#ifdef __cplusplus
}
#endif

#endif /* LV_MENU_OBJ_H */