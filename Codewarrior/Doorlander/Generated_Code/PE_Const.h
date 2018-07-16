/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : PE_Const.h
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Component   : PE_Const
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-13, 17:51, # CodeGen: 1
**     Abstract    :
**         This component "PE_Const" contains internal definitions
**         of the constants.
**     Settings    :
**     Contents    :
**         No public methods
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
** @file PE_Const.h
** @version 01.00
** @brief
**         This component "PE_Const" contains internal definitions
**         of the constants.
*/         
/*!
**  @addtogroup PE_Const_module PE_Const module documentation
**  @{
*/         

#ifndef __PE_Const_H
#define __PE_Const_H

/* Constants for detecting running mode */
#define HIGH_SPEED        0x00         /* High speed */
#define LOW_SPEED         0x01         /* Low speed */
#define SLOW_SPEED        0x02         /* Slow speed */

/* Reset cause constants */
#define RSTSRC_POR        0x80         /* Power-on reset        */
#define RSTSRC_PIN        0x40         /* External reset bit    */
#define RSTSRC_COP        0x20         /* COP reset             */
#define RSTSRC_ILOP       0x10         /* Illegal opcode reset  */
#define RSTSRC_ILAD       0x08         /* Illegal address reset */
#define RSTSRC_MODRST     0x04         /* Normal Monitor Mode Entry Reset*/
#define RSTSRC_MENRST     0x04         /* Forced Monitor Mode Entry Reset*/
#define RSTSRC_LVI        0x02         /* Low voltage inhibit reset */

#endif /* _PE_Const_H */
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
