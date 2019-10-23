/* ###################################################################
**     Filename    : main.c
**     Project     : Sully el SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-02, 12:27, # CodeGen: 0
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
#include "MBitQ.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "TI1.h"
#include "TI2.h"
#include "AS1.h"
#include "Cap1.h"
#include "AD1.h"
#include "Bit1.h"
#include "FC161.h"
#include "FC81.h"
#include "TI3.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

char flagmotor = 0;
char flaglect = 0;
char flagsonar = 0;
char flagtrigger = 0;
unsigned int lecturasonar;

void main(void)
{
  /* Write your local variable definition here */
	char step=5, sentido = 1, posicion = 32, posmax = 63, error, stepmax = 9,n=0,mediciones=2,entramado[4],bloque = 4, enviado, envio[2];
	char mensaje = 0b01010101;
	char Q[8] = {0b00000101, 0b00000001,0b00001001, 0b00001000, 0b00001010, 0b00000010, 0b00000110, 0b00000100};
	//char Q[4]= {0b00000001, 0b00001000, 0b00000010, 0b00000100};
	unsigned int timerlidar, lecturalidar[2], timersonar, valorsonar[2], sonarfilt, lidarfilt;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  while(1){
 	  if(flagmotor){
 		  TI1_Disable();
 		  TI2_Enable();
 		  flagmotor = 0;
 		  if(step == stepmax)step = 1;
 		  if(!step) step = stepmax-1;		  		  
 		  MBitQ_PutVal(Q[(step-1)]);
 		  //MBitQ_PutVal(Q[0]);
 		  if(sentido){
 			  posicion++;
 			  step++;
 		  }
 		  else {
 			  posicion--;
 			  step--;
 		  }
 		  if((posicion == posmax) || posicion==0){
 		 			  sentido = !sentido;
 		 		  }	  
 		  
 		  // Filtrado
 		  sonarfilt = (valorsonar[0]+valorsonar[1])>>1;
 		  lidarfilt = (lecturalidar[0]+lecturalidar[1])>>1;

 		  
 		  //Entramado
 		  entramado[0] = 0b00111111 & posicion;
 		  entramado[1] = 0b10000000 | ((sonarfilt & 0b111111100) >> 2);
 		  entramado[2] = 0b10000000 | ((sonarfilt & 0b000000011) << 5) | ((lidarfilt & 0b111110000000) >> 7);
 		  entramado[3] = 0b10000000 | (lidarfilt & 0b000001111111);
 		  
 		  //Envio
 		  AS1_SendBlock(entramado, bloque, &enviado);
 	  }
 	  
 	  if(flaglect){
 		  flaglect= 0 ;
 		  TI1_Enable();
 		  TI2_Disable();
 		  FC161_Enable();
 		  for(n=0;n<mediciones;n++){
 			  //Lidar
 			  
 			  FC161_GetTimeMS(&timerlidar);
 			  while(n>0 && timerlidar<60){
 				  FC161_GetTimeMS(&timerlidar);
 			  }
 			  do {error = AD1_Measure(1);} while(error != ERR_OK);
 			  do {error = AD1_GetValue(&lecturalidar[n]);} while(error != ERR_OK);
 			  FC161_Reset();
 			  
 			  //Sonar
 			  Bit1_SetVal(); //Subir trigger
 			  TI3_Enable();
 			  while(!flagtrigger); //Esperar 10 us
 			  TI3_Disable();
 			  Bit1_ClrVal(); //Bajar trigger
 			  flagtrigger = 0;
 			  while(!flagsonar);
 			  flagsonar = 0;
 			  while(!flagsonar);
 			  valorsonar[n] = lecturasonar;
 			  flagsonar = 0;
 		  }
 		  FC161_Disable();
 		 /*sonarfilt = ((valorsonar[0]+valorsonar[1])>>1);
 		 envio[0]=sonarfilt>>8;
 		 envio[1]=sonarfilt;
 		 AS1_SendBlock(envio, 2, &enviado);*/
 		  
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
