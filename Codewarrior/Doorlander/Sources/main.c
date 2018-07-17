/* ###################################################################
**     Filename    : main.c
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-13, 17:44, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED_Red.h"
#include "LED_Green.h"
#include "MCUC1.h"
#include "CS1.h"
#include "PeriodicCounter.h"
#include "ACCEL1.h"
#include "G11.h"
#include "G21.h"
#include "Sleep1.h"
#include "AD1.h"
#include "WAIT1.h"
#include "MPR08x1.h"
#include "Attn1.h"
#include "Irq1.h"
#include "CI2C1.h"
#include "FT800_SPI.h"
#include "SPI1.h"
#include "FT800_nPowerDown.h"
#include "FT800_nCS.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Battery.h"

#define wait_for_result 1


void main(void){
	
    /* Write your local variable definition here */
	

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/
    Cpu_EnableInt();
    /* Write your code here */
   /* For example: for(;;) { } */
    while(1){   
    	//Task LED On
        LED_Green_ClrVal();
        AD1_Measure(wait_for_result);
        //Run Tasks here
        ACCEL1_MeasureGetRawX();
        ACCEL1_MeasureGetRawY();
        ACCEL1_MeasureGetRawZ();
        GetBatteryVoltage();
        LED_Green_SetVal();
        Cpu_SetWaitMode();
    }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
