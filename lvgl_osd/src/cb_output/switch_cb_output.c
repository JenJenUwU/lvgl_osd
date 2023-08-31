/**
 * @file switch_cb_output
 *
 **/

/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include <stdbool.h>
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
 * Action when a specific switch was selected to a certain value
 * @param txt Label of the switch
 * @param chk Whether the switch is checked or not
 */
void switch_cb_output(const char *txt, bool chk)
{
    if (strcmp(txt, "Blue LED") == 0)
    {
        if (chk)
        {
        }
        else
        {
        }
    }
    else if (strcmp(txt, "White LED") == 0)
    {
        if (chk)
        {
        }
        else
        {
        }
    }
    else if (strcmp(txt, "Tamper Detection") == 0)
    {
        if (chk)
        {
        }
        else
        {
        }
    }
    else if (strcmp(txt, "Digital Output") == 0)
    {
        if (chk)
        {
        }
        else
        {
        }
    }
    else if (strcmp(txt, "Digital Input") == 0)
    {
        if (chk)
        {
        }
        else
        {
        }
    }
    else if (strcmp(txt, "Display Message") == 0)
    {
        if (chk)
        {
        }
        else
        {
        }
    }
}