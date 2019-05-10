/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    drop_move.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DROP_MOVE_H    /* Guard against multiple inclusion */
#define _DROP_MOVE_H


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
/*
#define RIGHT_DROP1 5780
#define LEFT_DROP1 4700 
 */
    
#define RIGHT_DROP1 5800
#define LEFT_DROP1 4700
#define RIGHT_DROP2 5000
#define LEFT_DROP2 3700
#define RIGHT_DROP3 4800
#define LEFT_DROP3 3200


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
        void drop_move()

      @Summary
        Brief one-line description of the function.
     */
    void drop_move();
    
    // *****************************************************************************
    /**
      @Function
        void finish_move(int *drop_part)

      @Summary
        Brief one-line description of the function.
     */
    void finish_move(int *drop_part);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DROP_MOVE_H */

/* *****************************************************************************
 End of File
 */
