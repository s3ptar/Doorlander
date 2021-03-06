/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : MPR08x1.h
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Component   : MPR08x
**     Version     : Component 01.205, Driver 01.00, CPU db: 3.00.063
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-15, 09:31, # CodeGen: 16
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         SetSensitivity       - byte MPR08x1_SetSensitivity(byte sensitivity);
**         SetSounder           - byte MPR08x1_SetSounder(bool enable, byte clickPeriod, byte frequency);
**         GetSensorInformation - byte MPR08x1_GetSensorInformation(byte *buf, byte bufSize);
**         ProcessTouch         - void MPR08x1_ProcessTouch(void);
**
**Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**All Rights Reserved.
**
**Redistribution and use in source and binary forms, with or without modification,
**are permitted provided that the following conditions are met:
**
**o Redistributions of source code must retain the above copyright notice, this list
**  of conditions and the following disclaimer.
**
**o Redistributions in binary form must reproduce the above copyright notice, this
**  list of conditions and the following disclaimer in the documentation and/or
**  other materials provided with the distribution.
**
**o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**  contributors may be used to endorse or promote products derived from this
**  software without specific prior written permission.
**
**THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**http: www.freescale.com
**mail: support@freescale.com
** ###################################################################*/
/*!
** @file MPR08x1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup MPR08x1_module MPR08x1 module documentation
**  @{
*/         

#ifndef __MPR08x1_H
#define __MPR08x1_H

/* MODULE MPR08x1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "Attn1.h"
#include "CI2C1.h"
#include "Irq1.h"
#include "WAIT1.h"

#include "Cpu.h"

#define MPR08x1_INTERRUPTS_ENABLED  1 /* Device generates interrupts and MPR08x1_ProcessTouch() is called automatically by the ISR. */

/* MPR084 registers */
#define FIFO_REGISTER                              0x00
#define FAULT_REGISTER                             0x01
#define PAD_STATUS_REGISTER                        0x02
#define PAD_CONFIGURATION_REGISTER                 0x03
#define SENSITIVITY_1_REGISTER                     0x04
#define SENSITIVITY_2_REGISTER                     0x05
#define SENSITIVITY_3_REGISTER                     0x06
#define SENSITIVITY_4_REGISTER                     0x07
#define SENSITIVITY_5_REGISTER                     0x08
#define SENSITIVITY_6_REGISTER                     0x09
#define SENSITIVITY_7_REGISTER                     0x0A
#define SENSITIVITY_8_REGISTER                     0x0B
#define ELECTRODE_CHANNEL_ENABLE_REGISTER          0x0C
#define MAX_NOF_TOUCH_POSITION_REGISTER            0x0D
#define MASTER_TICK_COUNTER_REGISTER               0x0E
#define TOUCH_ACQUISITION_SAMPLE_PERIOD_REGISTER   0x0F
#define SOUNDER_CONFIGURATION_REGISTER             0x10
#define LOW_POWER_CONFIGURATION_REGISTER           0x11
#define STUCK_KEY_TIMEOUT_REGISTER                 0x12
#define CONFIGURATION_REGISTER                     0x13
#define SENSOR_INFORMATION_REGISTER                0x14

/* various defines to make access to the register bits easier: */
/* --- CONFIGURATION_REGISTER --- */
#define CONFIGURATION_REG_RUNE    0x01 /* Run Mode Enable - The Run Mode Enable bit enables or disables scanning of the
                                             electrodes for touch detection. This bit is active high.
                                             0 Electrode Scanning Disabled (Stop modes)
                                             1 Electrode Scanning Enabled (Run modes) */
#define CONFIGURATION_REG_IRQEN   0x02 /* Interrupt Enable - The Interrupt Enable bit enables or disables the IRQ
                                             Functionality.
                                             0 IRQ Disabled
                                             1 IRQ Enabled */
#define CONFIGURATION_REG_DCE_NOT 0x04 /* Duty Cycle Enable - The Duty Cycle Enable bit enables or disables duty cycling on
                                             the sensor. This bit is active low.
                                             0 Duty Cycle Enabled (2 modes)
                                             1 Duty Cycle Disabled (1 modes) */
#define CONFIGURATION_REG_RST_NOT 0x10 /* Reset - Asserts a global reset of the sensor controller.
                                             0 Reset Asserted
                                             1 Reset Not Asserted */
/* --- SOUNDER_CONFIGURATION_REGISTER --- */
#define SOUNDER_FREQ_1kHZ   0  /* value for 1 kHz frequency for sounder */
#define SOUNDER_FREQ_2kHZ   1  /* value for 2 kHz frequency for sounder */
#define SOUNDER_CLICK_10ms  0  /* value for a 10 ms click period for sounder */
#define SOUNDER_CLICK_20ms  1  /* value for a 20 ms click period for sounder */

/* error code for 'OnFault' event */
#define ON_MPR08x_FAULT_NONE            0       /* Reserved for no fault */
#define ON_MPR08x_FAULT_SHORT_VSS       (1<<0)  /* Short to VSS detected (Fault register) */
#define ON_MPR08x_FAULT_SHORT_VDD       (1<<1)  /* Short to VDD detected (Fault register) */
#define ON_MPR08x_I2C_MAX_KEYS_ERROR    (1<<2)  /* MNKE: Maximum number of keys exceeded, only for MPR084 */
#define ON_MPR08x_FAULT_FIFO_OVL        5       /* FIFO Overflow (FIFO register) */
#define ON_MPR08x_I2C_SEND_ERROR        6       /* I2C Fatal error during sending */
#define ON_MPR08x_I2C_RECEIVE_ERROR     7       /* I2C Fatal error during receiving */
#define ON_MPR08x_I2C_SELECT_ERROR      8       /* I2C Fatal error during slave select */




byte MPR08x1_SetSensitivity(byte sensitivity);
/*
** ===================================================================
**     Method      :  MPR08x1_SetSensitivity (component MPR08x)
**     Description :
**         Specifies the sensor sensitivity level at runtime. Do NOT
**         call this function inside ProcessTouch().
**     Parameters  :
**         NAME            - DESCRIPTION
**         sensitivity     - sensitivity level, in the
**                           range of 1 to 64
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte MPR08x1_SetSounder(bool enable, byte clickPeriod, byte frequency);
/*
** ===================================================================
**     Method      :  MPR08x1_SetSounder (component MPR08x)
**     Description :
**         Configures the sounder/buzzer at runtime. Do NOT call this
**         function inside ProcessTouch().
**     Parameters  :
**         NAME            - DESCRIPTION
**         enable          - If sounder shall be enabled or not.
**         clickPeriod     - The click period controls
**                           the length of the sounder click. 0 gives a
**                           10 ms period, and 1 gives a 20 ms click
**                           period.
**         frequency       - Controls the frequency of the
**                           driven output. A value of 0 gives 1 kHz,
**                           and 1 gives 2 kHz
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte MPR08x1_GetSensorInformation(byte *buf, byte bufSize);
/*
** ===================================================================
**     Method      :  MPR08x1_GetSensorInformation (component MPR08x)
**     Description :
**         Reads the sensor information from the device. If the buffer
**         is not large enough to get all the information, then the
**         next call to this function will return the remaining
**         information. In any case the buffer passed will be zero
**         terminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - pointer to a buffer for the information.
**         bufSize         - size of the buffer, including zero
**                           byte. A buffer size of at least 45 bytes
**                           should be passed.
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void MPR08x1_ProcessTouch(void);
/*
** ===================================================================
**     Method      :  MPR08x1_ProcessTouch (component MPR08x)
**     Description :
**         Reads the sensor data and dispatches it to the corresponding
**         events. If the interrupts are enabled, this method is called
**         automatically in the interrupt service routine. Otherwise
**         you have to call this function from your application in
**         order to read the sensor (instantaneous mode).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Irq1_OnInterrupt(void);

void MPR08x1_Init(void);
/*
** ===================================================================
**     Method      :  MPR08x1_Init (component MPR08x)
**
**     Description :
**         Device initialization routine.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END MPR08x1. */

#endif
/* ifndef __MPR08x1_H */
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
