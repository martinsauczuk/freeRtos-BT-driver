/*
 * driver.h
 *
 *  Created on: Jul 12, 2018
 *      Author: martin
 */

#ifndef BT_DRIVER_INC_DRIVER_H_
#define BT_DRIVER_INC_DRIVER_H_

#include "main.h"


void vDriverTxTask( void *pvParameters );
void vDriverRxTask( void *pvParameters );

void vWriteStringToQueue(char* stringPointer);
void vWriteCharToQueue(char data);
void vPrintStringDebug( char * string);

void selectOption(char input);
void opcion1(void);
void opcion2(void);


#endif
