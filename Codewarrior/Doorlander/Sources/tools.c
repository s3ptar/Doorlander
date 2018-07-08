/*
 * tools.c
 *
 *  Created on: Jul 8, 2018
 *      Author: Besitzer
 */


/************************************************************************/
/*                      Includes                                        */
/************************************************************************/
#include "FreeRTOSConfig.h"
#include "tools.h"
/************************************************************************/
/*                      Definition                                      */
/************************************************************************/
#define defaultSecondCount 1000
/************************************************************************/
/*                      Global Variables                                */
/************************************************************************/


/************************************************************************
/! \fn          uint16_t calculate_Ticks(uint16_t wait_ms)
*  \brief       calculate the ticks to wait
*  \param       uint16_t wait_ms - Wait Time in ms
*  \exception   none
*  \return      ticks to wait
************************************************************************/
uint16_t calculate_msTicks(uint16_t wait_ms){
	
	return(wait_ms/(defaultSecondCount/configTICK_RATE_HZ));
	
}
