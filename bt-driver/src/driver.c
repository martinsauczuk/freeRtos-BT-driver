#include "driver.h"

/**
 *	Transmite a la UART el contenido de la cola, si tiene contenido
 */
void vDriverTxTask( void *pvParameters ) {

	char lReceivedValue;
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		/* As this task unblocks immediately that data is written to the queue this
		call should always find the queue empty. */
		if( uxQueueMessagesWaiting( xQueueTx ) != 0 )
		{
//			vPrintString( "Queue should have been empty!\r\n" );
		}

		xStatus = xQueueReceive( xQueueTx, &lReceivedValue, xTicksToWait );

		if( xStatus == pdPASS )
		{
			/* Data was successfully received from the queue, print out the received
			value. */
			//			vPrintStringAndNumber( "Received = ", lReceivedValue );
			uartWriteByte( UART_CONF, lReceivedValue);
		}
		else
		{
			/* We did not receive anything from the queue even after waiting for 100ms.
			This must be an error as the sending tasks are free running and will be
			continuously writing to the queue. */
//			vPrintString( "Could not receive from the queue.\r\n" );
		}
	}
}

/**
 *
 */
void vDriverRxTask( void *pvParameters ) {

	portBASE_TYPE xStatus;
	char data;

	for( ;; )
	{

		if( uartReadByte(UART_CONF, &data) ) {

			gpioWrite(LED_RX, TRUE);

//			vWriteCharToQueue(data);	// echo
			xStatus = xQueueSendToBack( xQueueRx, &data, 0 );

			if( xStatus != pdPASS )
			{
				/* We could not write to the queue because it was full – this must
								be an error as the queue should never contain more than one item! */
				vPrintString( "Could not send to the queue.\r\n" );
			}


		} else { // No hay dato
//			gpioWrite(LED_RX, FALSE);
//			rxFlag = FALSE;
		}
		taskYIELD();
	}
}

/**
 * Envia string completo a la cola
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
 *	Envia solamente un char a la cola
 */
void vWriteCharToQueue(char data) {

	portBASE_TYPE xStatus;
	xStatus = xQueueSendToBack( xQueueTx, &data, 0 );

	if( xStatus != pdPASS )
	{
		/* We could not write to the queue because it was full – this must
							be an error as the queue should never contain more than one item! */
		vPrintString( "Could not send to the queue.\r\n" );
	}
}

/**
 *	Imprime directamente una cadena
 */
void vPrintString( char * string) {
   uartWriteString( UART_CONF, string );
}
