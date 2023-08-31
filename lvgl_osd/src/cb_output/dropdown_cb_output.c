/**
 * @file dropdown_cb_output
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
 * Action when a specific dropdown was selected to a certain value
 * @param txt Label of the dropdown
 * @param val Index of the value
 */
void dropdown_cb_output(const char *txt, int32_t val)
{
    if (strcmp(txt, "Camera Position") == 0)
    {
        if (val == 0)
        {
            // Auto
        }
        else if (val == 1)
        {
            // Top
        }
        else if (val == 2)
        {
            // Buttom
        }
    }
    else if (strcmp(txt, "Motion Detection") == 0)
    {
        if (val == 0)
        {
            // Motion Flash
        }
        else if (val == 1)
        {
            // On
        }
        else if (val == 2)
        {
            // Off
        }
        else if (val == 3)
        {
            // Flash
        }
        else if (val == 4)
        {
            // Motion On
        }
    }
    else if (strcmp(txt, "Logo Display Mode") == 0)
    {
        if (val == 0)
        {
            // Motion Flash
        }
        else if (val == 1)
        {
            // On
        }
        else if (val == 2)
        {
            // Off
        }
        else if (val == 3)
        {
            // Motion
        }
        else if (val == 4)
        {
            // Flash
        }
    }
    else if (strcmp(txt, "Logo Select") == 0)
    {
        if (val == 0)
        {
            // Auto
        }
        else if (val == 1)
        {
            // 1
        }
        else if (val == 2)
        {
            // 2
        }
        else if (val == 3)
        {
            // 3
        }
        else if (val == 4)
        {
            // 4
        }
        else if (val == 5)
        {
            // 5
        }
        else if (val == 6)
        {
            // 6
        }
        else if (val == 7)
        {
            // 7
        }
        else if (val == 8)
        {
            // 8
        }
        else if (val == 9)
        {
            // 9
        }
        else if (val == 10)
        {
            // 10
        }
    }
    else if (strcmp(txt, "Volume") == 0)
    {
        if (val == 0)
        {
            // Low
        }
        else if (val == 1)
        {
            // Medium
        }
        else if (val == 2)
        {
            // High
        }
    }
}