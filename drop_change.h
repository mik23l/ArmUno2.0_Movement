/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    drop_change.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DROP_CHANGE_H    /* Guard against multiple inclusion */
#define _DROP_CHANGE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "debug.h"
#include "movement_queue.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************


    // *****************************************************************************
    /**
      @Function
        bool drop_change(int *part, ACTION_TYPE *type, int *done, int *reset_action)

      @Summary
        Brief one-line description of the function.
     */
    bool drop_change(int *part, ACTION_TYPE *type, int *done, int *reset_action);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PICK_CHANGE_H */

/* *****************************************************************************
 End of File
 */
