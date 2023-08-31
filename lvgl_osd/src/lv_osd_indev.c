/**
 * @file lv_osd_indev
 *
 **/

/*********************
 *      INCLUDES
 *********************/
#include "lv_osd_indev.h"
#include "key.h"
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
/*********************
 *      DEFINES
 *********************/
#define OSD_INPUT_PATH "/dev/input/event0"
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
bool osd_keypad_set_file(char* dev_name);
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *      VARIABLES
 **********************/
int input_fd = -1;
int osd_key_val;
int osd_button;
bool menu_activate = true;
/**********************
 *      FUNCTIONS
 **********************/
void osd_keypad_init(void)
{
    if (!osd_keypad_set_file(OSD_INPUT_PATH))
    {
        return;
    }
}

bool osd_keypad_set_file(char *dev_name)
{
    if (input_fd != -1)
    {
        close(input_fd);
    }
    input_fd = open(OSD_INPUT_PATH, O_RDONLY);

    if (input_fd == -1)
    {
        printf(
            "Fail to open device:%s.\n"
            "Please confirm the path or you have permission to do this.\n",
            OSD_INPUT_PATH);
        return false;
    }

    osd_key_val = 0;
    return true;
}

void osd_keypad_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    lv_obj_t *focused_item = NULL;
    struct input_event event;
    int key_event = 0;

    while (read(input_fd, &event, sizeof(event)) > 0)
    {
        if (event.type == EV_KEY)
        {   
            
            if (!menu_activate)
            {   
                if (event.code == KEY_MENU)
                {
                    if (event.value == 1)
                    {
                        // Key press event
                        menu_activate = !menu_activate;
                        if (menu_activate)
                        {
                            lv_obj_set_style_opa(lv_scr_act(), LV_OPA_COVER, LV_STATE_DEFAULT);
                        }
                        else
                        {
                            lv_obj_set_style_opa(lv_scr_act(), LV_OPA_TRANSP, LV_STATE_DEFAULT);
                        }
                        key_event = 1; // Mark as key press
                    }
                    else if (event.value == 0)
                    {
                        // Key release event
                        key_event = -1; // Mark as key release
                    }
                    data->key = 0 ;
                    break;
                }
                data->key = 0; // No input processing while menu is paused
                data->state = LV_INDEV_STATE_REL;
                return;
            }
            else
            {
                /*Define functions for different keys*/
                switch (event.code)
                {
                case KEY_HOME:
                    data->key = 0;
                    break;
                case KEY_MENU:
                    if (event.value == 1)
                    {
                        // Key press event
                        menu_activate = !menu_activate;
                        if (menu_activate)
                        {
                            lv_obj_set_style_opa(lv_scr_act(), LV_OPA_COVER, LV_STATE_DEFAULT);
                        }
                        else
                        {
                            lv_obj_set_style_opa(lv_scr_act(), LV_OPA_TRANSP, LV_STATE_DEFAULT);
                        }
                        key_event = 1; // Mark as key press
                    }
                    else if (event.value == 0)
                    {
                        // Key release event
                        key_event = -1; // Mark as key release
                    }
                    data->key = 0;
                    break;
                case KEY_UP:
                    data->key = LV_KEY_PREV;
                    break;
                case KEY_DOWN:
                    data->key = LV_KEY_NEXT;
                    break;
                case KEY_LEFT:
                    data->key = LV_KEY_LEFT;
                    break;
                case KEY_RIGHT:
                    data->key = LV_KEY_RIGHT;
                    break;
                case KEY_OK:
                    focused_item = lv_group_get_focused(lv_group_get_default());
                    if (focused_item)
                    {
                        if (lv_obj_has_flag(focused_item, LV_OBJ_FLAG_USER_1))
                        {
                            lv_group_focus_obj(lv_obj_get_child(lv_obj_get_user_data(focused_item), 1));
                            data->key = 0;
                        }
                        else
                        {
                            data->key = LV_KEY_ENTER;
                        }
                    }
                    break;
                case KEY_BACK:
                    data->key = LV_KEY_BACKSPACE;
                    break;
                case KEY_EXIT:
                    data->key = 0;
                    break;
                default:
                    data->key = 0;
                    break;
                }
            }
            if (data->key != 0)
            {
                /* Only record button state when actual output is produced to prevent widgets from
                 * refreshing */
                data->state = (event.value) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
            }
            osd_key_val = data->key;
            osd_button = data->state;
            return;
        }
    }
    if (drv->type == LV_INDEV_TYPE_KEYPAD)
    {
        /* No data retrieved */
        data->key = osd_key_val;
        data->state = osd_button;
        return;
    }
    if (key_event == 1)
    {
        // Key press event
        data->key = osd_key_val;
        data->state = LV_INDEV_STATE_PR;
    }
    else if (key_event == -1)
    {
        // Key release event
        data->key = 0;
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        // No key event
        data->key = 0;
        data->state = LV_INDEV_STATE_REL;
    }
}