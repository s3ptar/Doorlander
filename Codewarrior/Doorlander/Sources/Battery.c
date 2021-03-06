/*
 * Battery.c
 *
 *  Created on: Jul 15, 2018
 *      Author: Besitzer
 */


/************************************************************************/
/*                		Includes                                		*/
/************************************************************************/

/************************************************************************/
/*                		Definitions                               		*/
/************************************************************************/	
#include 	"Battery.h"
/************************************************************************/
/*                		Constants                               		*/
/************************************************************************/

/************************************************************************/
/*                		Variables	                              		*/
/************************************************************************/

/************************************************************************/
/*                		Global Variables                           		*/
/************************************************************************/

/************************************************************************/
/*                		Local Functions                           		*/
/************************************************************************/

/************************************************************************
/! \fn			uint16_t GetBatteryVoltage( void )
*  \brief		calculate the Voltage
*  \param		none
*  \exception	none3
*  \return		return the voltage
************************************************************************/
uint16_t GetBatteryVoltage( void ){
	
	uint16_t Mes_Battery_mV;
	AD1_GetChanValue(Battery_ADC, &Mes_Battery_mV);
	Mes_Battery_mV = (Mes_Battery_mV<<1) * LSB;
	return Mes_Battery_mV;
}
