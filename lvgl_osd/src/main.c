/**
 * @file main
 *
 **/

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

#include "demos/lv_demos.h"
#include "display/fbdev.h"
#include "lv_osd_menu_init.h"
#include "lv_osd_indev.h"

/*********************
 *      DEFINES
 *********************/
#define DISP_BUF_SIZE (128 * 1024)
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
void frame_buffer_init();
void input_device_init();
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
 *   STATIC FUNCTIONS
 **********************/
void frame_buffer_init()
{
    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = 1000;
    disp_drv.ver_res = 600;
    disp_drv.offset_x = 150;
    disp_drv.offset_y = 80;
    lv_disp_drv_register(&disp_drv);
}
void input_device_init()
{
    osd_keypad_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = osd_keypad_read;
    lv_indev_drv_register(&indev_drv);
}
/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int main(int argc, char **argv)
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    /*LVGL init*/
    lv_init();

    /*Initialie display driver*/
    frame_buffer_init();

    /*Initialie input driver*/
    input_device_init();

    /*Call the lvgl GUI*/
    lvgl_osd_menu();

    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too. */
        lv_tick_inc(5);
        lv_timer_handler();
        usleep(5 * 1000);
    }

    //lv_obj_clean(lv_scr_act())
    
    return 0;
}
