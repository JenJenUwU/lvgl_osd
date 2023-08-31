#ifndef LV_OSD_INDEV_H
#define LV_OSD_INDEV_H

#include "lv_drv_conf.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void osd_keypad_init(void);
void osd_keypad_read(lv_indev_drv_t * drv, lv_indev_data_t * data);

#ifdef __cplusplus
}
#endif

#endif /* LV_OSD_INDEV_H */