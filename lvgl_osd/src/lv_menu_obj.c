
/**
 * @file lv_menu_obj
 *
 **/

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lv_menu_obj.h"
//#include "cb_output.h"
#include "lvgl.h"
/*********************
 *      DEFINES
 *********************/
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
void btn_cb_output(const char *txt);
void dropdown_cb_output(const char *txt, int32_t val);
void slider_cb_output(const char *txt, int32_t val);
void switch_cb_output(const char *txt, bool chk);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *      FUNCTIONS
 **********************/
/**
 * Creates a text container object with a label attach to it
 *
 * @param parent pointer to an object, it will be the parent of the new text cont object
 * @param icon LV_SYMBOL of any kind that will be showed as the container's icon, NULL if no icon
 * @param txt name of the label attached to the container, NULL if no text
 * @param builder_variant LV_MENU_ITEM_BUILDER_VARIANT_1 for style 1, LV_MENU_ITEM_BUILDER_VARIANT_2
 * for style 2
 * @return pointer to the created text cont object
 */
lv_obj_t *create_text(lv_obj_t *parent, const char *icon, const char *txt,
                      lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t *obj = lv_menu_cont_create(parent);

    lv_obj_t *img = NULL;
    lv_obj_t *label = NULL;
    /*
    static lv_ft_info_t info;
    info.name = "../assets/demon_font.tff";
    info.weight = 24;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, info.font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);
    */

    if (icon)
    {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if (txt)
    {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
        //lv_obj_add_style(label, &style, 0);
    }

    if (builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt)
    {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}
/**
 * Creates a switch object with a label attach to it
 *
 * @param parent pointer to an object, it will be the parent of the new switch object
 * @param icon LV_SYMBOL of any kind that will be showed as the container's icon, NULL if no icon
 * @param txt name of the label attached to the container, NULL if no text
 * @param builder_variant LV_MENU_ITEM_BUILDER_VARIANT_1 for style 1, LV_MENU_ITEM_BUILDER_VARIANT_2
 * for style 2
 * @return pointer to the created switch obect
 */
lv_obj_t *create_switch(lv_obj_t *parent, const char *icon, const char *txt, bool chk)
{
    lv_obj_t *obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t *sw = lv_switch_create(obj);
    lv_obj_add_flag(sw, LV_OBJ_FLAG_USER_2);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    // Pass txt as user data
    lv_obj_add_event_cb(sw, switch_event_cb, LV_EVENT_VALUE_CHANGED, (void *)txt);

    return obj;
}
/**
 * Call back event used when a switch is adjusted
 * Output control of switches
 * @param e Pointer to the event descriptor
 */
void switch_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    const char *txt = (const char *)lv_event_get_user_data(e); // Get the text from user data

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *sw = lv_event_get_target(e);
        bool chk = lv_obj_has_state(sw, LV_STATE_CHECKED);

        // Use the 'txt' and 'chk' as needed
        LV_LOG_USER("Switch '%s' toggled: %s", txt, chk ? "ON" : "OFF");
        switch_cb_output(txt, chk);
    }
}
/**
 * Creates a dropdown object with a label attach to it
 *
 * @param parent pointer to an object, it will be the parent of the new dropdown object
 * @param icon LV_SYMBOL of any kind that will be showed as the container's icon, NULL if no icon
 * @param txt name of the label attached to the container, NULL if no text
 * @param builder_variant LV_MENU_ITEM_BUILDER_VARIANT_1 for style 1, LV_MENU_ITEM_BUILDER_VARIANT_2
 * for style 2
 * @return pointer to the created dropdown object
 */
lv_obj_t *create_dropdown(lv_obj_t *parent, const char *icon, const char *txt, const char *options,
                          int32_t val)
{
    lv_obj_t *obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t *dropdown = lv_dropdown_create(obj);
    lv_obj_add_flag(dropdown, LV_OBJ_FLAG_USER_2);
    lv_dropdown_set_options_static(dropdown, options);
    lv_dropdown_set_selected(dropdown, val);

    // Pass txt as user data
    lv_obj_add_event_cb(dropdown, dropdown_event_cb, LV_EVENT_VALUE_CHANGED, (void *)txt);
    return obj;
}

void dropdown_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    const char *txt = (const char *)lv_event_get_user_data(e); // Get the text from user data

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *dropdown = lv_event_get_target(e);
        int32_t val = lv_dropdown_get_selected(dropdown);

        // Use the 'txt' and 'val' as needed
        LV_LOG_USER("Dropdown '%s' value changed: %d", txt, val);
        dropdown_cb_output(txt, val);
    }
}
/**
 * Creates a button object with a label attach to it
 *
 * @param parent pointer to an object, it will be the parent of the new button object
 * @param icon LV_SYMBOL of any kind that will be showed as the container's icon, NULL if no icon
 * @param txt name of the label attached to the container, NULL if no text
 * @param builder_variant LV_MENU_ITEM_BUILDER_VARIANT_1 for style 1, LV_MENU_ITEM_BUILDER_VARIANT_2
 * for style 2
 * @return pointer to the created button object
 */
lv_obj_t *create_button(lv_obj_t *parent, const char *icon, const char *txt, const char *btn_text)
{
    lv_obj_t *obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t *btn = lv_btn_create(obj);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_USER_2);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED,
                        (void *)txt); // Pass btn_text as user data

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, btn_text);

    return obj;
}
/**
 * Call back event used when a button is adjusted
 * Output control of buttons
 * @param e Pointer to the event descriptor
 */
void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    const char *txt = (const char *)lv_event_get_user_data(e); // Cast user_data back to const char pointer

    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Button clicked: %s", txt);
        btn_cb_output(txt);
    }
}
/**
 * Creates a slider object with a label attach to it
 *
 * @param parent pointer to an object, it will be the parent of the new slider object
 * @param icon LV_SYMBOL of any kind that will be showed as the container's icon, NULL if no icon
 * @param txt name of the label attached to the container, NULL if no text
 * @param builder_variant LV_MENU_ITEM_BUILDER_VARIANT_1 for style 1, LV_MENU_ITEM_BUILDER_VARIANT_2
 * for style 2
 * @return pointer to the created slider object
 */
lv_obj_t *create_slider(lv_obj_t *parent, const char *icon, const char *txt, int32_t min,
                        int32_t max, int32_t val)
{
    lv_obj_t *obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t *slider = lv_slider_create(obj);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_USER_2);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_OFF);

    // Pass txt as user data
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, (void *)txt);

    // Create the label within the parent object (obj)
    lv_obj_t *slider_label = lv_label_create(obj);
    lv_label_set_text(slider_label, int_to_str(val));
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_obj_add_event_cb(slider, slider_event_label_cb, LV_EVENT_VALUE_CHANGED, slider_label);

    if (icon == NULL)
    {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return obj;
}
/**
 * Call back event used when a slider is adjusted
 * Output control of sliders
 * @param e Pointer to the event descriptor
 */
void slider_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    const char *txt = (const char *)lv_event_get_user_data(e); // Get the text from user data

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int32_t val = lv_slider_get_value(slider);
        // Use the 'txt' and 'val' as needed
        LV_LOG_USER("Slider '%s' value changed: %d", txt, val);
        slider_cb_output(txt, val);
    }
}
/**
 * Call back event used when slider value is adjusted
 * Adjust the label value respective to the adjust slider
 * @param e Pointer to the event descriptor
 */
void slider_event_label_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *slider_label = lv_event_get_user_data(e);

    if (slider_label)
    {
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
        lv_label_set_text(slider_label, buf);
        lv_obj_align_to(slider_label, lv_obj_get_parent(slider), LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }
}
/**
 * Integer to string convert function
 *
 * @param num Integer value to be converted to string
 * @return String the integer was converted to
 */
const char *int_to_str(int32_t num)
{
    snprintf(int_to_str_buffer, sizeof(int_to_str_buffer), "%d", num);
    return int_to_str_buffer;
}
/**
 * Callback event when an object is focused, the function interacts with the object if the object
 * has the flag LV_OBJ_FLAG_USER_1
 *
 */
void focus_event_cb()
{
    lv_obj_t *focused_item = lv_group_get_focused(lv_group_get_default());

    if (focused_item)
    {
        if (lv_obj_has_flag(focused_item, LV_OBJ_FLAG_USER_1))
        {
            lv_event_send(focused_item, LV_EVENT_CLICKED, NULL);
        }
    }
}
