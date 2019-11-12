/* ###################################################################
**     Filename    : main.c
**     Project     : PapaCaliente
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-11-04, 13:36, # CodeGen: 0
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
** @version 01.12
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
#include "AS1.h"
#include "AS2.h"
#include "PWM1.h"
#include "TI1.h"
#include "FC321.h"
#include "MBit1.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "TI2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
char flag=0;
char flagser=0;
char flagmotor=0;

void main(void)
{
	char carac,prueba=0b00001111, error;
	char step=1, sentido = 1, posicion = 40, stepmax = 8, z;
	char zonas[6] = {7, 20, 33, 46, 59, 72};
	char Q[8] = {0b00000101, 0b00000001,0b00001001, 0b00001000, 0b00001010, 0b00000010, 0b00000110, 0b00000100};
	unsigned int espera;
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  	z = 1;
	while(1){
		if(flag){
			AS1_RecvChar(&carac);
			AS1_SendChar(carac);
			if(!AS1_GetCharsInRxBuf()){
				flag = 0;
			}
		}
		FC321_GetTimeUS(&espera);
		if(espera>3000){
			flagser = 0;
			do {error = AS2_SendChar(prueba);} while(error != ERR_OK);
			FC321_Reset();
			
		}
		if(flagmotor){
			flagmotor = 0;
			if(posicion != zonas[z-1]){
				sentido = (zonas[z-1]>posicion);
				if(step == stepmax && sentido)step = 0;	//Mantener steps en rango de 1 a stepmax (4 u 8)
				if(step == 1 && !sentido) step = stepmax+1;	

				if(sentido){
					posicion++;
					step++;
				 }
				 else {
					posicion--;
					step--;
				 }
				
				MBit1_PutVal(Q[(step-1)]);	
			}
		}
	}


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
