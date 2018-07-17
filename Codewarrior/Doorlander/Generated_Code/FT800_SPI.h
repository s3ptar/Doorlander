/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : FT800_SPI.h
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Component   : GenericSPI
**     Version     : Component 01.033, Driver 01.00, CPU db: 3.00.063
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-16, 19:22, # CodeGen: 23
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         RecvChar            - byte FT800_SPI_RecvChar(void);
**         SendChar            - void FT800_SPI_SendChar(byte val);
**         ClearReceiveStatReg - void FT800_SPI_ClearReceiveStatReg(void);
**         ClearReceiveDataReg - void FT800_SPI_ClearReceiveDataReg(void);
**         WaitTransferDone    - void FT800_SPI_WaitTransferDone(void);
**         WriteDummy_Read     - byte FT800_SPI_WriteDummy_Read(void);
**         Write_ReadDummy     - void FT800_SPI_Write_ReadDummy(byte val);
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
** @file FT800_SPI.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup FT800_SPI_module FT800_SPI module documentation
**  @{
*/         

#ifndef __FT800_SPI_H
#define __FT800_SPI_H

/* MODULE FT800_SPI. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "SPI1.h"

#include "Cpu.h"
#define FT800_SPI_WaitRxFull()   while(!(SPI1S_SPRF))   /* Wait until RX buffer is full */
#define FT800_SPI_WaitTxEmpty()  while(!(SPI1S_SPTEF)) /* Wait until TX buffer is empty */
#define FT800_SPI_DummyRxRead()  ((void)SPI1D)                /* dummy read to clear the data/status register */




#define FT800_SPI_RecvChar() SPI1D
/*
** ===================================================================
**     Method      :  FT800_SPI_RecvChar (component GenericSPI)
**     Description :
**         
**     Parameters  : None
**     Returns     :
**         ---             - Character read
** ===================================================================
*/

#define FT800_SPI_SendChar(val) (SPI1D=val)
/*
** ===================================================================
**     Method      :  FT800_SPI_SendChar (component GenericSPI)
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         val             - 
**     Returns     : Nothing
** ===================================================================
*/

#define FT800_SPI_ClearReceiveStatReg() ((void)SPI1S) /* dummy read to clear the status register */
/*
** ===================================================================
**     Method      :  FT800_SPI_ClearReceiveStatReg (component GenericSPI)
**     Description :
**         Clears the status register
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define FT800_SPI_ClearReceiveDataReg() {(void)SPI1D; } /* dummy read to clear the data/status register */
/*
** ===================================================================
**     Method      :  FT800_SPI_ClearReceiveDataReg (component GenericSPI)
**     Description :
**         Clears the data register
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define FT800_SPI_WaitTransferDone()  while(!(SPI1S_SPRF)) /* until flag indicates transfer done */
/*
** ===================================================================
**     Method      :  FT800_SPI_WaitTransferDone (component GenericSPI)
**     Description :
**         Waits until the transfer is done
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

byte FT800_SPI_WriteDummy_Read(void);
/*
** ===================================================================
**     Method      :  FT800_SPI_WriteDummy_Read (component GenericSPI)
**     Description :
**         Writes a dummy value to the SPI bus and returns the value
**         read from the bus.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void FT800_SPI_Write_ReadDummy(byte val);
/*
** ===================================================================
**     Method      :  FT800_SPI_Write_ReadDummy (component GenericSPI)
**     Description :
**         Writes a value to the SPI bus and ignores the value read
**         back from the bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**         val             - The value to be shifted to the bus.
**     Returns     : Nothing
** ===================================================================
*/

/* END FT800_SPI. */

#endif
/* ifndef __FT800_SPI_H */
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
