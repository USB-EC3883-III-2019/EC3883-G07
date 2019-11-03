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
#include "BotonFilt.h"
#include "TI4.h"
#include "LedFilt.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

char flagmotor = 0; 	//Flag que inicia movimiento del motor
char flaglect = 0; 		//Flag que inicia lectura de sensores
char flagsonar = 0; 	//Flag de recepción del Echo del Sonar
char flagtrigger = 0;	//Flag de duración de 10 us para trigger del sonar
char filt = 1;			//Estado del filtro On/Off (1/0)
unsigned int lecturasonar;	//Variable en la que se asigna la lectura del Capture

void main(void)
{
  /* Write your local variable definition here */
	char step=1, sentido = 1, posicion = 16, posmax = 31, error, stepmax = 5; 	//Variables para control de movimiento de motor
	char n=0,mediciones=4,entramado[4],bloque = 4, enviado, envio[2];			//Variables para control de lectura y comunicacion serial
	//char Q[8] = {0b00000101, 0b00000001,0b00001001, 0b00001000, 0b00001010, 0b00000010, 0b00000110, 0b00000100}; //Vector de estados para Q en 1/2 steps
	char Q[4]= {0b00000001, 0b00001000, 0b00000010, 0b00000100}; //Vector de estados para Q en steps
	unsigned int timerlidar, lecturalidar[4], timersonar, valorsonar[4], sonarfilt, lidarfilt;  //Control de filtrado y de datos

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  MBitQ_PutVal(Q[(step-1)]); //Inicializar en posicion 1 del motor
  AS1_Enable(); //Habilitar comunicación serial
  while(1){
//Control de motor, filtrado, entramado y envío por puerto serial
 	  if(flagmotor){ 					//Cuando corresponda mover el motor
 		  TI1_Disable(); 				//Desactivar timer del motor y activar timer de lectura
 		  TI2_Enable();
 		  flagmotor = 0;				//Resetear flag de motor
 		  if(step == stepmax)step = 1;	//Mantener steps en rango de 1 a stepmax (4 u 8)
 		  if(!step) step = stepmax-1;		  		  
 		  MBitQ_PutVal(Q[(step-1)]);	//Coloca las salidas digitales en el estado de Q1, Q2, Q3 y Q4 correspondiente
 		  
 		  // Filtrado
 		  if(filt){ 					//Filtrar en caso de que esté activo el filtro
 			  sonarfilt = (valorsonar[0]+valorsonar[1]+valorsonar[2]+valorsonar[3])>>2;			//Filtrar como un promedio de las medidas
 			  lidarfilt = (lecturalidar[0]+lecturalidar[1]+lecturalidar[2]+lecturalidar[3])>>2;
 			  entramado[0] = (0b00111111 & posicion)|0b01000000;								//Indicar filtro activo en entramado	
 		  }
 		  else{
 			  sonarfilt = valorsonar[0];						//Si no se filtra sólo asignar valor de primera medida
 			  lidarfilt = lecturalidar[0];
 			  entramado[0] = 0b00111111 & posicion;				
 		  }
 		  
 		  //Entramado
 		  entramado[1] = 0b10000000 | ((sonarfilt & 0b111111100) >> 2);   
 		  entramado[2] = 0b10000000 | ((sonarfilt & 0b000000011) << 5) | ((lidarfilt & 0b111110000000) >> 7);
 		  entramado[3] = 0b10000000 | (lidarfilt & 0b000001111111);
 		  
 		  //Envio
 		  AS1_SendBlock(entramado, bloque, &enviado);   //Envio por puerto serial
 		  
 		  //Siguiente posicion
 		 if(sentido){
 		  	posicion++;
 		  	step++;
 		 }
 		 else {
 		  	posicion--;
 		  	step--;
 		 }
 		 //Cambio de sentido en caso de posición borde
 		 if((posicion == posmax) || posicion==1){
 		  	sentido = !sentido;
 		 }	  
 	  }
 	  
 //Control de lectura de sensores
 	  if(flaglect){
 		  flaglect= 0 ;  					//Resetear flag de lectura
 		  TI1_Enable();						//Activar timer de motor y desactivar timer de lectura
 		  TI2_Disable();
 		  FC161_Enable();					//Activar contador de espera para dato nuevo de infrarrojo
 		  
 		  for(n=0;n<mediciones;n++){			//Realizar tantas mediciones como lo indique mediciones
 			  //Lidar  
 			  FC161_GetTimeMS(&timerlidar);		//Obtener tiempo de contador de lidar
 			  while(n>0 && timerlidar<50){		//Si no es la primera lectura y aún no hay un nuevo valor de lidar entonces volver a leer contador
 				  FC161_GetTimeMS(&timerlidar);
 			  }
 			  do {error = AD1_Measure(1);} while(error != ERR_OK);   //Medir con ADC
 			  do {error = AD1_GetValue(&lecturalidar[n]);} while(error != ERR_OK);   //Obtener valor de ADC
 			  FC161_Reset();		//Resetear contador
 			  
 			  //Sonar
 			  Bit1_SetVal(); 			//Subir trigger
 			  TI3_Enable(); 			//Habilitar timer trigger
 			  while(!flagtrigger); 		//Esperar 10 us
 			  TI3_Disable();			//Deshabilitar timer trigger
 			  Bit1_ClrVal(); 			//Bajar trigger
 			  flagtrigger = 0;			//Resetear flag del trigger
 			  while(!flagsonar);		//Esperar a recibir flanco de subida de Echo
 			  flagsonar = 0;
 			  while(!flagsonar);		//Esperar a recibir flanco de bajada de Echo
 			  valorsonar[n] = lecturasonar;	//Guardar valor del sonar
 			  flagsonar = 0;
 		  }
 		  FC161_Disable();				//Desactivar contador de Lidar		  
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
