/*
 * Idle_Task.c
 *
 *  Created on: Jul 8, 2018
 *      Author: Besitzer
 */
/************************************************************************/
/*                      Includes                                        */
/************************************************************************/
#include "Idle_Task.h"
#include "tools.h"
#include "FRTOS1.h"
/************************************************************************/
/*                      Definition                                      */
/************************************************************************/

/************************************************************************/
/*                      Global Variables                                */
/************************************************************************/

static

/************************************************************************
/! \fn          void vTaskIdle( void * pvParameters )
*  \brief       idle Function - print Error codes und Status to the Led
*  \param       none
*  \exception   none
*  \return      none
************************************************************************/
void vTaskIdle( void * pvParameters ){
	
	
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. */
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    for( ;; )
    {
        /* Task code goes here. */
    }
	/* The parameter value is expected to be 1 as 1 is passed in the
	pvParameters value in the call to xTaskCreate() below. */
    //configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
	
	//for(;;){
	    //Wait for 100ms
	//    FRTOS1_vTaskDelay(calculate_msTicks(100));
	//}
	//vTaskDelete( NULL );
}

/* Task to be created. */
void vTaskCode( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. */
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    for( ;; )
    {
        /* Task code goes here. */
    }
}
