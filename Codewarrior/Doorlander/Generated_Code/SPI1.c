/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SPI1.c
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Component   : Init_SPI
**     Version     : Component 01.114, Driver 01.21, CPU db: 3.00.063
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-16, 19:22, # CodeGen: 23
**     Abstract    :
**          This file implements the SPI (SPI1) module initialization
**          according to the Peripheral Initialization Component settings, and defines
**          interrupt service routines prototypes.
**          The SPI module is the serial peripheral interface module,which allows 
**          full-duplex, synchronous, serial communications with peripheral devices.


**     Settings    :
**          Component name                                 : SPI1
**          Device                                         : SPI1
**          Settings
**            Clock settings
**              Value of Preselection                      : 1
**              Value of Selection                         : 2
**              Frequency                                  : 2097.152 kHz
**            Mode Select                                  : Master
**            Clock Polarity                               : active-high
**            Clock Phase                                  : First edge
**            Data shift order                             : MSB first
**            Bidirectional mode                           : Disabled
**            Output enable in Bidirect.                   : no
**            Stop in Wait Mode                            : Disabled
**            Data length                                  : 8 bits
**            Match value                                  : 0
**            Input filter on SPI pins                     : Enabled
**          Pins
**            SCK pin                                      : PTE6_SPSCK1
**            SCK pin signal                               : 
**            MISO pin allocation                          : Enabled
**            MISO pin                                     : PTE4_MISO1
**            MISO pin signal                              : 
**            MOSI pin allocation                          : Enabled
**            MOSI pin                                     : PTE5_MOSI1
**            MOSI pin signal                              : 
**            SS pin allocation                            : Disabled
**          Interrupts
**            Interrupt                                    : Vspi1
**            Interrupt priority                           : default
**            Receive and fault interrupt                  : Disabled
**            Transmit Interrupt                           : Disabled
**            Match interrupt                              : Disabled
**            ISR name                                     : 
**          Initialization
**            Call Init in CPU init. code                  : yes
**            Enable SPI system                            : yes
**     Contents    :
**         Init - void SPI1_Init(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file SPI1.c
** @version 01.21
** @brief
**          This file implements the SPI (SPI1) module initialization
**          according to the Peripheral Initialization Component settings, and defines
**          interrupt service routines prototypes.
**          The SPI module is the serial peripheral interface module,which allows 
**          full-duplex, synchronous, serial communications with peripheral devices.


*/         
/*!
**  @addtogroup SPI1_module SPI1 module documentation
**  @{
*/         

/* MODULE SPI1. */

#include "SPI1.h"

/*
** ===================================================================
**     Method      :  SPI1_Init (component Init_SPI)
**     Description :
**         This method initializes registers of the SPI module
**         according to this Peripheral Initialization Component settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the component for more details. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SPI1_Init(void)
{
  /* SPI1C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  setReg8(SPI1C1, 0x00U);              /* All interrupt flags in SPIxS register are reset when the SPI1 module is disabled. */ 
  /* SPI1C2: SPMIE=0,SPIMODE=0,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
  setReg8(SPI1C2, 0x00U);               
  /* SPI1BR: ??=0,SPPR2=0,SPPR1=0,SPPR0=0,??=0,SPR2=0,SPR1=0,SPR0=0 */
  setReg8(SPI1BR, 0x00U);               
  /* SPI1M: Bit15=0,Bit14=0,Bit13=0,Bit12=0,Bit11=0,Bit10=0,Bit9=0,Bit8=0,Bit7=0,Bit6=0,Bit5=0,Bit4=0,Bit3=0,Bit2=0,Bit1=0,Bit0=0 */
  setReg16(SPI1M, 0x00U);               
  /* SPI1C1: SPIE=0,SPE=1,SPTIE=0,MSTR=1,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  setReg8(SPI1C1, 0x50U);               
}

/* END SPI1. */

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
