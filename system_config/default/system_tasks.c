/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled state
    machines.

  Description:
    This file contains source code necessary to maintain system's polled state
    machines.  It implements the "SYS_Tasks" function that calls the individual
    "Tasks" functions for all the MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"
#include "arm.h"
#include "movement.h"
#include "find.h"
#include "send.h"
#include "receive.h"
#include "receiver.h"


// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 
static void _SYS_Tasks ( void );
 
 
static void _ARM_Tasks(void);
static void _MOVEMENT_Tasks(void);
static void _FIND_Tasks(void);
static void _SEND_Tasks(void);
static void _RECEIVE_Tasks(void);
static void _RECEIVER_Tasks(void);


// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/

void SYS_Tasks ( void )
{
    /* Create OS Thread for Sys Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
                "Sys Tasks",
                1024, NULL, 0, NULL);

 
 
    /* Create OS Thread for ARM Tasks. */
    xTaskCreate((TaskFunction_t) _ARM_Tasks,
                "ARM Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for MOVEMENT Tasks. */
    xTaskCreate((TaskFunction_t) _MOVEMENT_Tasks,
                "MOVEMENT Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for FIND Tasks. */
    xTaskCreate((TaskFunction_t) _FIND_Tasks,
                "FIND Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for SEND Tasks. */
    xTaskCreate((TaskFunction_t) _SEND_Tasks,
                "SEND Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for RECEIVE Tasks. */
    xTaskCreate((TaskFunction_t) _RECEIVE_Tasks,
                "RECEIVE Tasks",
                1024, NULL, 1, NULL);

    /* Create OS Thread for RECEIVER Tasks. */
    xTaskCreate((TaskFunction_t) _RECEIVER_Tasks,
                "RECEIVER Tasks",
                1024, NULL, 1, NULL);

    /**************
     * Start RTOS * 
     **************/
    vTaskStartScheduler(); /* This function never returns. */
}


/*******************************************************************************
  Function:
    void _SYS_Tasks ( void )

  Summary:
    Maintains state machines of system modules.
*/
static void _SYS_Tasks ( void)
{
    while(1)
    {
        /* Maintain system services */

        /* Maintain Device Drivers */
 
 

        /* Maintain Middleware */

        /* Task Delay */
    }
}

 
 

/*******************************************************************************
  Function:
    void _ARM_Tasks ( void )

  Summary:
    Maintains state machine of ARM.
*/

static void _ARM_Tasks(void)
{
    while(1)
    {
        ARM_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _MOVEMENT_Tasks ( void )

  Summary:
    Maintains state machine of MOVEMENT.
*/

static void _MOVEMENT_Tasks(void)
{
    while(1)
    {
        MOVEMENT_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _FIND_Tasks ( void )

  Summary:
    Maintains state machine of FIND.
*/

static void _FIND_Tasks(void)
{
    while(1)
    {
        FIND_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _SEND_Tasks ( void )

  Summary:
    Maintains state machine of SEND.
*/

static void _SEND_Tasks(void)
{
    while(1)
    {
        SEND_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _RECEIVE_Tasks ( void )

  Summary:
    Maintains state machine of RECEIVE.
*/

static void _RECEIVE_Tasks(void)
{
    while(1)
    {
        RECEIVE_Tasks();
    }
}


/*******************************************************************************
  Function:
    void _RECEIVER_Tasks ( void )

  Summary:
    Maintains state machine of RECEIVER.
*/

static void _RECEIVER_Tasks(void)
{
    while(1)
    {
        RECEIVER_Tasks();
    }
}


/*******************************************************************************
 End of File
 */
