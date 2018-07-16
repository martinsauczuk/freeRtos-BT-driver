#include "driver.h"

extern xQueueHandle xQueueTx;
extern xQueueHandle xQueueRx;

/**
 *	Transmite a la UART el contenido de la cola, si tiene contenido-
 *	Tare consumidora de la cola de Tx
 */
void vDriverTxTask( void *pvParameters ) {

	char valorParaTransmitir;
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	for( ;; )
	{
		/* As this task unblocks immediately that data is written to the queue this
		call should always find the queue empty. */
		if( uxQueueMessagesWaiting( xQueueTx ) != 0 )
		{
			vPrintStringDebug( "Queue should have been empty!\r\n" );
		}

		xStatus = xQueueReceive( xQueueTx, &valorParaTransmitir, xTicksToWait );

		//dato a transmitir obtenido Ok desde la cola
		if( xStatus == pdPASS )
		{
			// led indicador en ON
			gpioWrite(LED_TX, TRUE);

			// Transmision a la UART, siempre es por byte
			uartWriteByte( UART_CONF, valorParaTransmitir);
		}
		else
		{
			// led indicador en ON
			gpioWrite(LED_TX, FALSE);
			vPrintStringDebug( "No se obtuvo ningun dato de la cola Tx\r\n" );
		}
	}
}

/**
 *	Verifica si hay un dato en la UART y lo carga en la cola de Rx
 *	Productora de la cola de Rx
 */
void vDriverRxTask( void *pvParameters ) {

	// Status de la cola
	portBASE_TYPE xStatus;

	char data;

	for( ;; )
	{

		if( uartReadByte(UART_CONF, &data) ) {

			// led indicador en ON
			gpioWrite(LED_RX, TRUE);

			xStatus = xQueueSendToBack( xQueueRx, &data, 0 );

			// Pregunto por el estado
			if( xStatus != pdPASS )
			{
				vPrintStringDebug( "Error al enviar a la cola.\r\n" );
			}

		} else {
			// led indicador en off
			gpioWrite(LED_RX, FALSE);
		}
		taskYIELD();
	}
}

/**
 * Envia string completo a la cola de Tx, utilizando vWriteCharToQueue
 * Esta es la función a utilizar por la app
 */
void vWriteStringToQueue(char* stringPointer) {
	char i = 0;
	while ( stringPointer[i] != '\0')
	{
		vWriteCharToQueue( stringPointer[i] );
		i++;
	}
}

/**
 *	Envia solamente un char a la cola de Tx.
 *	Función productora de la cola de Tx
 */
void vWriteCharToQueue(char data) {

	portBASE_TYPE xStatus;
	xStatus = xQueueSendToBack( xQueueTx, &data, 0 );

	if( xStatus != pdPASS )
	{
		/* We could not write to the queue because it was full – this must
							be an error as the queue should never contain more than one item! */
		vPrintStringDebug( "Error al enviar a la cola Tx.\r\n" );
	}
}

/**
 *	Imprime directamente una cadena, sin utilizar la cola
 *	Función a utilizar solamente para debug.
 */
void vPrintStringDebug( char * string) {
   uartWriteString( UART_DEBUG, string );
}
