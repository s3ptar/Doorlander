/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : FT800_SPI.c
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
**     * Copyright (c) 2008-2017, Erich Styger
**      * Web:         https://mcuoneclipse.com
**      * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**      * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**      * All rights reserved.
**      *
**      * Redistribution and use in source and binary forms, with or without modification,
**      * are permitted provided that the following conditions are met:
**      *
**      * - Redistributions of source code must retain the above copyright notice, this list
**      *   of conditions and the following disclaimer.
**      *
**      * - Redistributions in binary form must reproduce the above copyright notice, this
**      *   list of conditions and the following disclaimer in the documentation and/or
**      *   other materials provided with the distribution.
**      *
**      * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**      * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**      * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**      * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**      * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**      * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**      * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**      * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**      * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**      * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file FT800_SPI.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup FT800_SPI_module FT800_SPI module documentation
**  @{
*/         

/* MODULE FT800_SPI. */

#include "FT800_SPI.h"

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
/* function is implemented as macro in the header file */

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
/* function is implemented as macro in the header file */

/*
** ===================================================================
**     Method      :  FT800_SPI_ClearReceiveStatReg (component GenericSPI)
**     Description :
**         Clears the status register
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/* function is implemented as macro in the header file */

/*
** ===================================================================
**     Method      :  FT800_SPI_ClearReceiveDataReg (component GenericSPI)
**     Description :
**         Clears the data register
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/* function is implemented as macro in the header file */

/*
** ===================================================================
**     Method      :  FT800_SPI_WaitTransferDone (component GenericSPI)
**     Description :
**         Waits until the transfer is done
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/* function is implemented as macro in the header file */

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
byte FT800_SPI_WriteDummy_Read(void)
{
  FT800_SPI_WaitTxEmpty(); /* wait until we can store new value into shift register */
  FT800_SPI_SendChar(0); /* shift in dummy value */
  FT800_SPI_WaitTxEmpty(); /* wait until value has been shifted out */
  FT800_SPI_WaitRxFull(); /* wait until we are ready to read the new value from the bus from the register */
  return FT800_SPI_RecvChar(); /* return value from bus */
}

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
void FT800_SPI_Write_ReadDummy(byte val)
{
  FT800_SPI_WaitTxEmpty(); /* wait until transmit buffer is empty */
  FT800_SPI_SendChar(val); /* send the value to the bus */
  FT800_SPI_WaitRxFull();  /* wait until the value has been shifted out */
  FT800_SPI_DummyRxRead(); /* ignore the new value from the bus */
}

/* END FT800_SPI. */

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
