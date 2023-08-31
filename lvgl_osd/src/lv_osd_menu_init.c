/**
 * @file lv_osd_menu_init
 *
 **/

/*********************
 *      INCLUDES
 *********************/
#include "lv_osd_menu_init.h"
#include "lv_menu_obj.h"
#include "lvgl.h"

#include <stdio.h>
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t *g;
/**********************
 *      MACROS
 **********************/

/**********************
 *      VARIABLES
 **********************/
lv_obj_t *root_page;
/**********************
 *      FUNCTIONS
 **********************/
void lvgl_osd_menu(void)
{
    /*====================
     *     Init group
     *====================*/
    g = lv_group_create();
    lv_group_set_default(g);
    lv_indev_t *indev = NULL;
    for (;;)
    {
        indev = lv_indev_get_next(indev);
        if (!indev)
        {
            break;
        }

        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if (indev_type == LV_INDEV_TYPE_KEYPAD)
        {
            lv_indev_set_group(indev, g);
        }
    }
    /*====================
     *  Styling of Main Menu
     *====================*/

    lv_obj_t *menu = lv_menu_create(lv_scr_act());

    lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
    if (lv_color_brightness(bg_color) > 127)
    {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 10), 0);
    }
    else
    {
        lv_obj_set_style_bg_color(menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
    }

    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_DISABLED);
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    /*====================
     *  Create sub pages
     *====================*/

    // Mounting Orientation
    lv_obj_t *sub_mounting_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_mounting_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_mounting_page);
    lv_obj_t *mounting_section = lv_menu_section_create(sub_mounting_page);
    lv_obj_t *mounting_child_cont = create_dropdown(mounting_section, NULL, "Camera Position", "Auto\nTop\nBottom", 0);

    // Setup Menu
    lv_obj_t *sub_setup_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_setup_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_setup_page);
    lv_obj_t *setup_section = lv_menu_section_create(sub_setup_page);
    // create_dropdown(section, NULL, "OSD Timeout", "Off\n15s\n30s\n45s\n60s");
    lv_obj_t *setup_child_cont = create_slider(setup_section, NULL, "OSD Timeout", 0, 60, 30);
    create_switch(setup_section, NULL, "Blue LED", true);
    create_switch(setup_section, NULL, "White LED", true);
    create_dropdown(setup_section, NULL, "Motion Detection",
                    "Motion Flash\nOn\nOff\nFlash\nMotion On", 0);
    create_slider(setup_section, NULL, "Motion Duration", 10, 60, 15);
    create_switch(setup_section, NULL, "Tamper Detection", false);
    create_switch(setup_section, NULL, "Digital Output", false);
    create_switch(setup_section, NULL, "Digital Input", false);

    // PVM Function
    lv_obj_t *sub_pvm_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_pvm_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_pvm_page);
    lv_obj_t *pvm_section = lv_menu_section_create(sub_pvm_page);
    lv_obj_t *pvm_child_cont = create_slider(pvm_section, NULL, "Warning Message", 1, 3, 1);
    create_dropdown(pvm_section, NULL, "Logo Display Mode", "Motion Flash\nOn\nOff\nMotion\nFlash",
                    0);
    create_switch(pvm_section, NULL, "Display Message", true);
    create_slider(pvm_section, NULL, "Audio Alert", 0, 3, 0);
    create_dropdown(pvm_section, NULL, "Logo Select", "Auto\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10", 0);

    // Restore Defaults
    lv_obj_t *sub_restore_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_restore_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_restore_page);
    lv_obj_t *restore_section = lv_menu_section_create(sub_restore_page);
    lv_obj_t *restore_child_cont = create_button(restore_section, NULL, "All", "Confirm");

    // Audio Control
    lv_obj_t *sub_audio_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_audio_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_audio_page);
    lv_obj_t *audio_section = lv_menu_section_create(sub_audio_page);
    lv_obj_t *audio_child_cont = create_dropdown(audio_section, NULL, "Volume", "Low\nMedium\nHigh", 1);

    // SD Card Function
    lv_obj_t *sub_sd_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_sd_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_sd_page);
    lv_obj_t *sd_section = lv_menu_section_create(sub_sd_page);
    lv_obj_t *sd_child_cont = create_button(sd_section, NULL, "Firmware Update", "Confirm");
    create_button(sd_section, NULL, "Import Config", "Confirm");
    create_button(sd_section, NULL, "Export Config", "Confirm");

    lv_obj_t *sub_software_info_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_software_info_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_software_info_page);
    lv_obj_t *software_info_section = lv_menu_section_create(sub_software_info_page);
    lv_obj_t *software_info_child_cont = create_text(
        software_info_section, NULL, "Firmware Version: 0.0.2.13", LV_MENU_ITEM_BUILDER_VARIANT_1);
    create_text(software_info_section, NULL, "Hardware Version: 1.0",
                LV_MENU_ITEM_BUILDER_VARIANT_1);
    create_text(software_info_section, NULL, "SKU: US", LV_MENU_ITEM_BUILDER_VARIANT_1);

    /*
    lv_obj_t *sub_menu_mode_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_menu_mode_page,
                             lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_menu_mode_page);
    lv_obj_t *menu_mode_section = lv_menu_section_create(sub_menu_mode_page);
    lv_obj_t *menu_mode_child_cont
        = create_switch(menu_mode_section, LV_SYMBOL_AUDIO, "Sidebar enable", true);
    lv_obj_add_event_cb(lv_obj_get_child(menu_mode_child_cont, 2), switch_handler,
    */

    // LV_EVENT_VALUE_CHANGED, menu);

    /*====================
     *  Root page styles
     *====================*/
    root_page = lv_menu_page_create(menu, "Settings");
    lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0),
                             0);
    lv_obj_t *root_section = lv_menu_section_create(root_page);

    lv_obj_t *mounting_cont = create_text(root_section, LV_SYMBOL_UPLOAD, "Mounting Orientation",
                                          LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(mounting_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, mounting_cont, sub_mounting_page);
    lv_group_add_obj(g, mounting_cont);
    lv_obj_set_user_data(mounting_cont, mounting_child_cont);

    lv_obj_t *setup_cont = create_text(root_section, LV_SYMBOL_HOME, "Setup Menu", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(setup_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, setup_cont, sub_setup_page);
    lv_group_add_obj(g, setup_cont);
    lv_obj_set_user_data(setup_cont, setup_child_cont);

    lv_obj_t *pvm_cont = create_text(root_section, LV_SYMBOL_LIST, "PVM Function", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(pvm_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, pvm_cont, sub_pvm_page);
    lv_group_add_obj(g, pvm_cont);
    lv_obj_set_user_data(pvm_cont, pvm_child_cont);

    lv_obj_t *restore_cont = create_text(root_section, LV_SYMBOL_WARNING, "Restore Defaults",
                                         LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(restore_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, restore_cont, sub_restore_page);
    lv_group_add_obj(g, restore_cont);
    lv_obj_set_user_data(restore_cont, restore_child_cont);

    lv_obj_t *audio_cont = create_text(root_section, LV_SYMBOL_VOLUME_MID, "Audio Control",
                                       LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(audio_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, audio_cont, sub_audio_page);
    lv_group_add_obj(g, audio_cont);
    lv_obj_set_user_data(audio_cont, audio_child_cont);

    lv_obj_t *sd_cont = create_text(root_section, LV_SYMBOL_SD_CARD, "SD Card Function",
                                    LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(sd_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, sd_cont, sub_sd_page);
    lv_group_add_obj(g, sd_cont);
    lv_obj_set_user_data(sd_cont, sd_child_cont);

    create_text(root_page, NULL, "Others", LV_MENU_ITEM_BUILDER_VARIANT_1);
    root_section = lv_menu_section_create(root_page);

    lv_obj_t *about_cont = create_text(root_section, LV_SYMBOL_FILE, "About", LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(about_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, about_cont, sub_software_info_page);
    lv_group_add_obj(g, about_cont);
    lv_obj_set_user_data(about_cont, software_info_child_cont);

    /*
    lv_obj_t *menu_mode_cont = create_text(root_section, NULL, "Menu mode",
                                           LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_obj_add_flag(menu_mode_cont, LV_OBJ_FLAG_USER_1);
    lv_menu_set_load_page_event(menu, menu_mode_cont, sub_menu_mode_page);
    lv_group_add_obj(g, menu_mode_cont);
    lv_obj_set_user_data(menu_mode_cont, menu_mode_child_cont);
    */

    lv_menu_set_sidebar_page(menu, root_page);

    lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0),
                  LV_EVENT_CLICKED, NULL);
    lv_group_set_focus_cb(g, focus_event_cb);
}