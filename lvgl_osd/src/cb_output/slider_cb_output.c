/**
 * @file slider_cb_output
 *
 **/

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include <stdint.h>
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
 * Action when a specific slider was selected to a certain value
 * @param txt Label of the slider
 * @param val Current value of the slider
 */
void slider_cb_output(const char *txt, int32_t val)
{
    if (strcmp(txt, "OSD Timeout") == 0)
    {
    }
    else if (strcmp(txt, "Motion Duration") == 0)
    {
    }
    else if (strcmp(txt, "Warning Message") == 0)
    {
    }
    else if (strcmp(txt, "Audio Alert") == 0)
    {
    }
}