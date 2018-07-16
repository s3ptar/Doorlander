/* ###################################################################
**     Filename    : Events.c
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-13, 17:44, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  PeriodicCounter_OnInterrupt (module Events)
**
**     Component   :  PeriodicCounter [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PeriodicCounter_OnInterrupt(void)
{
  /* Write your code here ... */

}

/*
** ===================================================================
**     Event       :  MPR08x1_OnPress (module Events)
**
**     Component   :  MPR08x1 [MPR08x]
**     Description :
**         Event for a button pressed. You can disable this event if
**         you are not interested in it in order to save code size.
**     Parameters  :
**         NAME            - DESCRIPTION
**         button          - Button number, in the range 0 to 7.
**     Returns     : Nothing
** ===================================================================
*/
void MPR08x1_OnPress(byte button)
{
  (void)button; /* only to avoid compiler warning about unused variable */
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnEnd(void)
{
  /* Write your code here ... */
}


/* END Events */

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
