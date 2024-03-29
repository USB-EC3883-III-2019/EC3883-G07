/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cap1.h
**     Project     : Sully el SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : Capture
**     Version     : Component 02.223, Driver 01.30, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-21, 10:54, # CodeGen: 48
**     Abstract    :
**         This component "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
**     Settings    :
**             Timer capture encapsulation : Capture
**
**         Timer
**             Timer                   : TPM1
**             Counter shared          : Yes
**
**         High speed mode
**             Prescaler               : divide-by-1
**           Maximal time for capture register
**             Xtal ticks              : 200000000
**             microseconds            : 4000000
**             milliseconds            : 4000
**             seconds                 : 4
**             seconds (real)          : 4.0
**           One tick of timer is
**             microseconds            : 61.035156
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Capture                : TPM1C1V   [$0049]
**              Counter                : TPM1CNT   [$0041]
**              Mode                   : TPM1SC    [$0040]
**              Run                    : TPM1SC    [$0040]
**              Prescaler              : TPM1SC    [$0040]
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       22            |  PTB5_TPM1CH1_SS1
**             ----------------------------------------------------
**
**         Port name                   : PTB
**         Bit number (in port)        : 5
**         Bit mask of the port        : $0020
**
**         Signal edge/level           : both
**         Priority                    : 
**         Pull option                 : off
**
**     Contents    :
**         Reset           - byte Cap1_Reset(void);
**         GetCaptureValue - byte Cap1_GetCaptureValue(Cap1_TCapturedValue *Value);
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
** @file Cap1.h
** @version 01.30
** @brief
**         This component "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
*/         
/*!
**  @addtogroup Cap1_module Cap1 module documentation
**  @{
*/         

#ifndef __Cap1
#define __Cap1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE Cap1. */

#include "Cpu.h"

/* PUBLISHED CONSTANTS */
#define Cap1_PRESCALER_VALUE           0x01U /* Prescaler value of the timer in high speed mode */
#define Cap1_COUNTER_INPUT_CLOCK_HZ    0x4000LU /* Initial counter input clock frequency [Hz] */
#define Cap1_TIMER_INPUT_CLOCK         0x00E40000LU /* Deprecated, Initial timer input clock frequency [Hz] */
#define Cap1_PRESCALER_VALUE_HIGH      0x01U /* Prescaler value of the timer in high speed mode */
#define Cap1_COUNTER_INPUT_CLOCK_HZ_HIGH 0x4000LU /* Counter input clock frequency in high speed mode [Hz] */
#define Cap1_TIMER_INPUT_CLOCK_HIGH    0x00E40000LU /* Deprecated, Timer input clock frequency in high speed mode[Hz] */

#ifndef __BWUserType_Cap1_TCapturedValue
#define __BWUserType_Cap1_TCapturedValue
  #define Cap1_TCapturedValue word     /*  Captured value, unsigned integer value. Bit-width of the type depends on the width of selected timer. */
#endif

#pragma CODE_SEG Cap1_CODE

extern volatile word Cap1_CntrState;   /* Content of counter */


#define Cap1_Reset() \
  (Cap1_CntrState = TPM1CNT , (byte)ERR_OK)
/*
** ===================================================================
**     Method      :  Cap1_Reset (component Capture)
**     Description :
**         This method resets the counter register (see implementation
**         note in <General Info>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define Cap1_GetCaptureValue(Value) \
  /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */\
  (((*(Cap1_TCapturedValue*)(Value) = TPM1C1V), \
  (*(Cap1_TCapturedValue*)(Value) -= Cap1_CntrState)), \
  ERR_OK) \
  /*lint -restore Enable MISRA rule (11.4) checking. */
/*
** ===================================================================
**     Method      :  Cap1_GetCaptureValue (component Capture)
**     Description :
**         This method gets the last value captured by enabled timer.
**         Note: one tick of timer is
**               61.035156 us in high speed mode
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - A pointer to the content of the
**                           capture register
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

void Cap1_Init(void);
/*
** ===================================================================
**     Method      :  Cap1_Init (component Capture)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void Cap1_Interrupt(void);
#pragma CODE_SEG Cap1_CODE
/*
** ===================================================================
**     Method      :  Interrupt (component Capture)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT

/* END Cap1. */

#endif /* ifndef __Cap1 */
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
