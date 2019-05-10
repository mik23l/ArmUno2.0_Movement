/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    pick_move.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _PICK_MOVE_H    /* Guard against multiple inclusion */
#define _PICK_MOVE_H


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
#include "arm_queue.h"
#include "variable_define.h"
#include "package_queue.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define RIGHT0_PICK1 4500
#define RIGHT1_PICK1 4700
#define RIGHT0_PICK2 4900
#define RIGHT1_PICK2 5450
#define RIGHT0_PICK3 5300
#define RIGHT1_PICK3 5900
#define LEFT0_PICK1 2700
#define LEFT1_PICK1 3000
#define LEFT0_PICK2 3200
#define LEFT1_PICK2 3800
#define LEFT0_PICK3 3700
#define LEFT1_PICK3 4700

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
        void pick_move(int pick_part, uint16_t *dis)

      @Summary
        Brief one-line description of the function.
     */
    void pick_move(int *pick_part, uint16_t *dis);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PICK_MOVE_H */

/* *****************************************************************************
 End of File
 */
