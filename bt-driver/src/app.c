#include "app.h"

extern xQueueHandle xQueueRx;

/**
 * APP: Este módulo está dedicado a la aplicación, utiliza las funciones
 * provistas por el drive.
 * Para transmitir utilizar vvoid vWriteStringToQueue(char* stringPointer) y vWriteCharToQueue(char data);
 */


/**
 *	Muestra menú al usuario
 */
void vShowMenu(  ) {

	vWriteStringToQueue("** App de prueba driver uart freeRtos **\r\n" );
	vWriteStringToQueue("Menú, seleccione una opción\r\n" );
	vWriteStringToQueue("1 - Función de ejemplo 1\r\n" );
	vWriteStringToQueue("2 - Función de ejemplo 2\r\n" );

}

/**
 * Si hay dato en la cola de Rx(tecla presionada), responder
 *
 */
void vResponseMenuTask( void *pvParameters ) {

	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	char valorExtraido;

	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		/* As this task unblocks immediately that data is written to the queue this
			call should always find the queue empty. */
		if( uxQueueMessagesWaiting( xQueueRx ) != 0 )
		{
			vPrintStringDebug( "Queue should have been empty!\r\n" );
		}

		xStatus = xQueueReceive( xQueueRx, &valorExtraido, xTicksToWait );

		// Hay dato en receivedChar
		if( xStatus == pdPASS )
		{
			selectOption(valorExtraido);
		}
		else
		{
			vPrintStringDebug( "Could not receive from the queue.\r\n" );
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
	vWriteStringToQueue("opcion incorrecta\r\n" );
	vShowMenu();
}


