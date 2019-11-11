/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : MBit1.h
**     Project     : PapaCaliente
**     Processor   : MC9S08QE128CLK
**     Component   : MultiBitIO
**     Version     : Component 01.000, Driver 01.01, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-11-11, 12:50, # CodeGen: 29
**     Abstract    :
**         This bean "MultiBitIO" implements a multi-bit input/output.
**         It assembles alone pins into 1-8bit software port
**     Settings    :
**         Used pin                    :
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    56   |   PTD4_KBI2P4
**                    1      |    28   |   PTD5_KBI2P5
**                    2      |    27   |   PTD6_KBI2P6
**                    3      |    26   |   PTD7_KBI2P7
**             ----------------------------------------------------
**
**         Number of bits/pins         : 4
**         Values range                : 0 to 15
**
**         Initial direction           : Output (direction can be changed)
**         Initial output value        : 0 = 000H
**
**     Contents    :
**         GetDir    - bool MBit1_GetDir(void);
**         SetDir    - void MBit1_SetDir(bool Dir);
**         SetInput  - void MBit1_SetInput(void);
**         SetOutput - void MBit1_SetOutput(void);
**         GetVal    - byte MBit1_GetVal(void);
**         PutVal    - void MBit1_PutVal(byte Val);
**         GetBit    - bool MBit1_GetBit(byte Bit);
**         PutBit    - void MBit1_PutBit(byte Bit, bool Val);
**         SetBit    - void MBit1_SetBit(byte Bit);
**         ClrBit    - void MBit1_ClrBit(byte Bit);
**         NegBit    - void MBit1_NegBit(byte Bit);
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
** @file MBit1.h
** @version 01.01
** @brief
**         This bean "MultiBitIO" implements a multi-bit input/output.
**         It assembles alone pins into 1-8bit software port
*/         
/*!
**  @addtogroup MBit1_module MBit1 module documentation
**  @{
*/         

#ifndef __MBit1_H
#define __MBit1_H

/* MODULE MBit1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
/* Include inherited components */
#include "Inhr1.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"

#include "Cpu.h"




#define MBit1_GetDir() Inhr1_GetDir()
/*
** ===================================================================
**     Method      :  MBit1_GetDir (component MultiBitIO)
**     Description :
**         Returns selected direction.
**     Parameters  : None
**     Returns     :
**         ---             - Possible values:
**                           FALSE - Input
**                           TRUE - Output
** ===================================================================
*/

void MBit1_SetDir(bool Dir);
/*
** ===================================================================
**     Method      :  MBit1_SetDir (component MultiBitIO)
**     Description :
**         Sets a direction for the pins (available only if Direction =
**         _[input/output]_).
**     Parameters  :
**         NAME            - DESCRIPTION
**         Dir             - Direction to set. Possible values:
**                           FALSE - Input
**                           TRUE - Output
**     Returns     : Nothing
** ===================================================================
*/

  #define MBit1_SetInput() ( \
  (((( /* compliance with MISRA rule 12.1 */ \
  Inhr1_SetInput()),\
  Inhr2_SetInput()),\
  Inhr3_SetInput()),\
  Inhr4_SetInput()) \
  )
/*
** ===================================================================
**     Method      :  MBit1_SetInput (component MultiBitIO)
**     Description :
**         Sets a direction to input for the pins (available only if
**         Direction = _[input/output]_).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define MBit1_SetOutput() ( \
  (((( /* compliance with MISRA rule 12.1 */ \
  Inhr1_SetOutput()),\
  Inhr2_SetOutput()),\
  Inhr3_SetOutput()),\
  Inhr4_SetOutput()) \
  )
/*
** ===================================================================
**     Method      :  MBit1_SetOutput (component MultiBitIO)
**     Description :
**         Sets a direction to output for the pins (available only if
**         Direction = _[input/output]_).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

byte MBit1_GetVal(void);
/*
** ===================================================================
**     Method      :  MBit1_GetVal (component MultiBitIO)
**     Description :
**         Returns the value of the Input/Output bean. Bean calls
**         ancestor's [GetVal] for each bit and composes value
**         according its order. That is [direction] independent, for
**         details look into ancestor documentation.
**     Parameters  : None
**     Returns     :
**         ---             - Input value
** ===================================================================
*/

void MBit1_PutVal(byte Val);
/*
** ===================================================================
**     Method      :  MBit1_PutVal (component MultiBitIO)
**     Description :
**         Specified value is passed to the Input/Output bean. Bean
**         calls ancestor's [PutVal] for each bit with corresponded
**         value. That is [direction] independent, for details look
**         into ancestor documentation. (Method is available only if
**         the Direction = _[output]_ or _[input/output]_).
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Output value
**     Returns     : Nothing
** ===================================================================
*/

bool MBit1_GetBit(byte Bit);
/*
** ===================================================================
**     Method      :  MBit1_GetBit (component MultiBitIO)
**     Description :
**         Returns the value of the specified bit/pin of the
**         Input/Output bean. For specified bit is called ancestor's
**         [GetVal] method. That is [direction] independent, for
**         details look into ancestor documentation. Pins are addressed
**         form zero, where 0 is equaled to LSB.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Bit             - Bit/pin number to read (0 equal LSB)
**     Returns     :
**         ---             - Bit value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
** ===================================================================
*/

void MBit1_PutBit(byte Bit, bool Val);
/*
** ===================================================================
**     Method      :  MBit1_PutBit (component MultiBitIO)
**     Description :
**         Specified value is passed to the specified bit/pin of the
**         Input/Output bean. For specified bit is called ancestor's
**         [PutVal] method. That is [direction] independent, for
**         details look into ancestor documentation. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_). Pins are addressed form zero, where 0 is
**         equaled to LSB.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Bit             - Bit/pin number (0 equal LSB)
**         Val             - A new bit value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/

void MBit1_SetBit(byte Bit);
/*
** ===================================================================
**     Method      :  MBit1_SetBit (component MultiBitIO)
**     Description :
**         Sets (to one) the specified bit of the Input/Output bean. It
**         is the same as [PutBit(Bit, TRUE)]. (Method is available
**         only if the Direction = _[output]_ or _[input/output]_).
**         Pins are addressed form zero, where 0 is equaled to LSB.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Bit             - Bit/pin number to set (0 equal LSB)
**     Returns     : Nothing
** ===================================================================
*/

void MBit1_ClrBit(byte Bit);
/*
** ===================================================================
**     Method      :  MBit1_ClrBit (component MultiBitIO)
**     Description :
**         Clears (sets to zero) the specified bit of the Input/Output
**         bean. It is the same as [PutBit(Bit, FALSE)]. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_). Pins are addressed form zero, where 0 is
**         equaled to LSB.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Bit             - Bit/pin number to clear (0 equal LSB)
**     Returns     : Nothing
** ===================================================================
*/

void MBit1_NegBit(byte Bit);
/*
** ===================================================================
**     Method      :  MBit1_NegBit (component MultiBitIO)
**     Description :
**         Negates (inverts) the specified bit of the Input/Output bean.
**         It is the same as [PutBit(Bit,!GetBit(Bit))]. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_). Pins are addressed form zero, where 0 is
**         equaled to LSB.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Bit             - Bit/pin number to invert (0 equal LSB)
**     Returns     : Nothing
** ===================================================================
*/

/* END MBit1. */

#endif /* #ifndef __MBit1_H_ */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
