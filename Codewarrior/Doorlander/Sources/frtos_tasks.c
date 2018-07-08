
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

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "CreateTasks.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "Led_Green.h"

static portTASK_FUNCTION(vTaskIdleTask, pvParameters) {

    /* Write your task initialization code here ... */

    for(;;) {
        /* Write your task code here ... */

        /* You can use a task delay like
         vTaskDelay(1000/portTICK_RATE_MS);
        */

	
  }
  /* Destroy the task */
  vTaskDelete(vTaskIdleTask);
}

void CreateTasks(void) {
  if (FRTOS1_xTaskCreate(
     vTaskIdleTask,  /* pointer to the task */
      "vTaskIdle", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 0,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}

