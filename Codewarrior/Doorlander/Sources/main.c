/* ###################################################################
**     Filename    : main.c
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-08, 10:32, # CodeGen: 0
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
#include "FRTOS1.h"
#include "VL1swi.h"
#include "TickCntr1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "Led_Red.h"
#include "Led_Green.h"
#include "CreateTasks.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "Idle_Task.h"


/************************************************************************
/! \fn          void main(void)
*  \brief       main function - Programm start here
*  \param       none
*  \exception   none
*  \return      none
************************************************************************/
void main(void){
	
    /* Write your local variable definition here */

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    /* Write your code here */
    /* For example: for(;;) { } */
    /* Create the task*/
    CreateTasks_CreateTasks();
    FRTOS1_vTaskStartScheduler();
    /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}

