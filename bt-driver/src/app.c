#include "app.h"

/**
 *
 */
void vShowMenu(  ) {

	vWriteStringToQueue(">Menu, seleccione la opcion\r\n" );
	vWriteStringToQueue("Opcion 1\r\n" );
	vWriteStringToQueue("Opcion 2\r\n" );
	vWriteStringToQueue(">");

}

/**
 * Si hay dato en la cola de Rx(tecla presionada), responder
 *
 */
void vResponseMenuTask( void *pvParameters ) {

	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	char receivedChar;

	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		gpioToggle(LEDG);
		/* As this task unblocks immediately that data is written to the queue this
			call should always find the queue empty. */
		if( uxQueueMessagesWaiting( xQueueRx ) != 0 )
		{
			//			vPrintString( "Queue should have been empty!\r\n" );
		}

		xStatus = xQueueReceive( xQueueRx, &receivedChar, xTicksToWait );

		if( xStatus == pdPASS )
		{
			selectOption(receivedChar);
		}
		else
		{
			/* We did not receive anything from the queue even after waiting for 100ms.
				This must be an error as the sending tasks are free running and will be
				continuously writing to the queue. */
			//			vPrintString( "Could not receive from the queue.\r\n" );
		}
		taskYIELD();
	}

}

/**
 * Opciones del manu
 */
void selectOption(char input) {
	switch (input) {
	case '1':
		opcion1();
		break;

	case '2':
		opcion2();
		break;

	default:
		opcionDefault();
		break;
	}
}

/**
 *
 */
void opcion1() {

	vWriteStringToQueue("Opcion 1 seleccionada\r\n");
}

/**
 *
 */
void opcion2() {
	vWriteStringToQueue("Opcion 2 seleccionada\r\n" );
}

/**
 *
 */
void opcionDefault() {
	vWriteStringToQueue("incorrecta\r\n" );
	vShowMenu();
}


