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
#include "TI4.h"
#include "TI5.h"
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
char enviando = 0;
char flagmove = 0;

void main(void)
{
	char carac,caracoriginal,prueba=0b00001111, error, encabezado=0, mensaje[4], recibido[4]={0,0,0,0}, recibiendo;
	char bloque[4] = {0,0,0,0};
	char step=1, sentido = 1, posicion = 40, stepmax = 9, zona, i;
	char zonas[6] = {7, 20, 33, 46, 59, 72};
	char maestro=0, esclavo=1, orden = 0;
	char Q[8] = {0b00000101, 0b00000001,0b00001001, 0b00001000, 0b00001010, 0b00000010, 0b00000110, 0b00000100};
	char *send;
	unsigned int espera;
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	while(1){
		if(flagusuario){
			if(AS1_GetCharsInRxBuf()>=4){
				carac = AS1_GetCharsInRxBuf();
				AS1_RecvBlock(bloque, 4, send);
				maestro = !(bloque[0]&0b00100000);
				esclavo = (bloque[0]&0b00100000)>>5;
				caracoriginal = (bloque[0]<<4)|(bloque[1]&0b00001111);
				flagusuario = 0;
			}	
		}
			
		
//MAESTRO		
		if(maestro){
			//Armar mensaje para enviar
			mensaje[0] = bloque[0]&0b10001111;
			mensaje[1] = bloque[1]&0b00001111;
			mensaje[2] = bloque[2];
			mensaje[3] = bloque[3];
			
			//Obtener zona de la primera transmision
			zona = (bloque[1]&0b01110000)>>4;
			
			//Ubicar motor en la zona
			TI2_EnableEvent();
			while(posicion != zonas[zona-1]){
				if(flagmotor){
					flagmotor = 0;
					sentido = (zonas[zona-1]>posicion);
					if(step == stepmax)step = 1;	//Mantener steps en rango de 1 a stepmax (4 u 8)
					if(step == 0) step = stepmax-1;	
					
					MBit1_PutVal(Q[(step-1)]);
					
					if(sentido){
						posicion++;
						step++;
					}
					else {
						posicion--;
						step--;
					}										
				}				
			}
			TI2_DisableEvent();
			
			if(flagespera){
				flagespera = 0;
				AS2_SendBlock(mensaje, 4, send);
			}
			if(flagtorre){
				if(AS2_GetCharsInRxBuf()>=4){
					AS2_RecvBlock(recibido, 4, send);
					flagtorre = 0;
						if(recibido[0]>127 && recibido[1]<128 && !recibido[2] && !recibido[3]){
							carac = ((recibido[0]&0b00001111)<<4)|(recibido[1]&0b00001111);
							if(carac==caracoriginal){
								AS1_SendBlock(recibido, 4, send);
								maestro = 0;
							}
						}
						else AS2_RecvChar(&error);	
				}
			}			
		}
		
//ESCLAVO		
		if(esclavo){
			if(flagtorre){
				if(AS2_GetCharsInRxBuf()>=5){
					AS2_RecvBlock(recibido, 4, send);
					flagtorre = 0;
					if(!enviando){
						if(recibido[0]>127 && recibido[1]<128 && recibido[2]<128 && recibido[3]<128){
							if((recibido[0] != mensaje[0]) || (recibido[1] != mensaje[1])||(recibido[2] != mensaje[2]) || (recibido[3] != mensaje[3])){
								recibiendo = 1;
								enviando = 1;
							}
						}
						else AS2_RecvChar(&error);	
					}
				}
			}
				
			if(recibiendo){
				recibiendo = 0;
				//Obtener zona y chequear orden
					if(recibido[2]&0b00111000){
						zona = (recibido[2]&0b00111000)>>3;
						recibido[2] = recibido[2]&0b00000111;
					}
					else if(recibido[2]&0b00000111){
						zona = (recibido[2]&0b00000111);
						recibido[2] = recibido[2]&0b00000000;
					}
					else if(recibido[3]&0b00111000){
						zona = (recibido[3]&0b00111000)>>3;
						recibido[3] = recibido[3]&0b00000111;
					}
					else if(recibido[3]&0b00000111){
						zona = (recibido[3]&0b00000111);
						recibido[3] = recibido[3]&0b00000000;
					}
				
				//Ubicar motor en la zona
				TI2_EnableEvent();
				while((posicion != zonas[zona-1])&& zona>0 && zona<7){
					if(flagmotor){
						flagmotor = 0;
						sentido = (zonas[zona-1]>posicion);
						if(step == stepmax)step = 1;	//Mantener steps en rango de 1 a stepmax (4 u 8)
						if(step == 0) step = stepmax-1;	
					
						MBit1_PutVal(Q[(step-1)]);	
					
						if(sentido){
							posicion++;
							step++;
						}
						else {
							posicion--;
							step--;
						}
					}				
				}
				TI2_DisableEvent();
							
				//Armar mensaje para enviar
				mensaje[0] = recibido[0]&0b10001111;
				mensaje[1] = recibido[1]&0b00001111;
				mensaje[2] = recibido[2];
				mensaje[3] = recibido[3];
				
			}
			if(enviando && flagespera){
				//Enviar
				flagespera = 0;
				AS2_SendBlock(mensaje, 4, send);
				AS1_SendBlock(mensaje, 4, send);
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
