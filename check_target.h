/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    check_target.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _CHECK_TARGET_H    /* Guard against multiple inclusion */
#define _CHECK_TARGET_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "arm_queue.h"
#include "debug.h"


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
        void check_target(uint32_t *right, uint32_t *left, uint32_t *grip, ARM_UPDATE *right_, ARM_UPDATE *left_, ARM_UPDATE *grip_, ARM_UPDATE *new_target)

      @Summary
        Brief one-line description of the function.
     */
    bool check_target(uint32_t *right, uint32_t *left, uint32_t *grip, ARM_UPDATE *right_, ARM_UPDATE *left_, ARM_UPDATE *grip_, ARM_UPDATE *new_target);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
