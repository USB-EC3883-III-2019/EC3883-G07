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
#include "TI3.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
char flagusuario=0;
char flagtorre=0;
char flagser=0;
char flagmotor=0;
char flagespera = 0;

void main(void)
{
	char bloque[3],carac,caracoriginal,prueba=0b00001111, error,send,esperando=0, maestro=0, esclavo=1,encabezado, mensaje[4], recibido[3];
	char step=1, sentido = 1, posicion = 40, stepmax = 8, zona, i;
	char zonas[6] = {7, 20, 33, 46, 59, 72};
	char Q[8] = {0b00000101, 0b00000001,0b00001001, 0b00001000, 0b00001010, 0b00000010, 0b00000110, 0b00000100};
	unsigned int espera;
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	while(1){
		if(flagusuario){
			do{AS1_RecvChar(&encabezado);}
			while(!(encabezado&0b10000000));
			while(AS1_GetCharsInRxBuf()<3);
			AS1_RecvBlock(bloque, 3, &send);
			maestro = !(encabezado&0b00100000);
			esclavo = (encabezado&0b00100000);
			caracoriginal = (encabezado<<4)|(bloque[0]&0b00001111);
		}
			/*if(!AS1_GetCharsInRxBuf()){
				flag = 0;
			}
			if(AS2_GetCharsInRxBuf() && esperando){
				esperando = 0;
				AS2_RecvChar(&carac);
				AS1_SendChar(carac);
			}*/
		
		/*FC321_GetTimeUS(&espera);
		if(espera>3000){
			flagser = 0;
			do {error = AS2_SendChar(prueba);} while(error != ERR_OK);
			FC321_Reset();	
		}*/
		
//MAESTRO		
		if(maestro){
			//Armar mensaje para enviar
			mensaje[0] = encabezado&0b10001111;
			mensaje[1] = bloque[0]&0b00001111;
			mensaje[2] = bloque[1];
			mensaje[3] = bloque[2];
			
			//Obtener zona de la primera transmision
			zona = (bloque[0]&0b01110000)>>4;
			
			//Ubicar motor en la zona
			TI2_EnableEvent();
			while(posicion != zonas[zona-1]){
				if(flagmotor){
					flagmotor = 0;
					sentido = (zonas[zona-1]>posicion);
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
			TI2_DisableEvent();
			
			if(flagespera){
				flagespera = 0;
				AS2_SendBlock(mensaje, 4, &send);
			}
			
			if(flagtorre){
				do{AS2_RecvChar(&encabezado);}
				while(!(encabezado&0b10000000));
				while(AS2_GetCharsInRxBuf()<3);
				AS2_RecvBlock(recibido, 3, &send);
				
				if(!recibido[2] && !recibido[1]){
					carac = (encabezado<<4)|(recibido[0]&0b00001111);
					if(carac==caracoriginal){						
					AS1_SendChar(carac);
					maestro = 0;
					}
				}
			}			
		}
		
//ESCLAVO		
		if(esclavo){
			if(flagtorre){
				do{AS2_RecvChar(&encabezado);}
				while(!(encabezado&0b10000000));
				while(AS2_GetCharsInRxBuf()<3);
				AS2_RecvBlock(recibido, 3, &send);			
			}
			//Obtener zona
			zona = 0;
			i = 0;
			while(zona == 0){
				if(recibido[2-i]&0b00000111){
					zona = recibido[2-i]&0b00000111;
					recibido[2-i] = recibido[2-i]&0b11111000;
				}
				else{
					zona = recibido[2-i]&0b00111000;
					recibido[2-i]&0b00000000;
				}
				i++;
			}
				
			//Ubicar motor en la zona
			TI2_EnableEvent();
			while(posicion != zonas[zona-1]){
				if(flagmotor){
					flagmotor = 0;
					sentido = (zonas[zona-1]>posicion);
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
			TI2_DisableEvent();
			
			//Armar mensaje para enviar
			mensaje[0] = encabezado&0b10001111;
			mensaje[1] = recibido[0]&0b00001111;
			mensaje[2] = recibido[1];
			mensaje[3] = recibido[2];
			
			//Enviar
			AS2_SendBlock(mensaje, 4, &send);			
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
