#include "main.h"


/**
 *
 */
static void initHardware(void) {
   /* Inicializar la placa */
   boardConfig();

   /* Inicializar Uart */
   uartConfig( UART_USB, 9600 );
}

/**
 *
 */
int main( void )
{
	initHardware();

    /* The queue is created to hold a maximum of 5 long values. */

    xQueueTx = xQueueCreate(TX_QUEUE_SIZE, sizeof( char ) );
    xQueueRx = xQueueCreate(RX_QUEUE_SIZE, sizeof( char ) );
    vShowMenu();

//	if( xQueueTx != NULL )
//	{
//		xTaskCreate( vSenderTask, "Sender1", 240, ( void * ) 100, 1, NULL );
		xTaskCreate( vResponseMenuTask, "ResponseMenu", 240, ( void * ) 200, 1, NULL );

//		xTaskCreate( vShowMenuTerminalTask, "menuPrincipal", 240, ( void * ) 100 , 1, NULL );
		/* Create the task that will read from the queue.  The task is created with
		priority 2, so above the priority of the sender tasks. */
		xTaskCreate( vDriverTxTask, "Tx", 240, ( void * ) 100, 1, NULL );
		xTaskCreate( vDriverRxTask, "Rx", 240, ( void * ) 100, 1, NULL );

		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();
//	}
//	else
//	{
		/* The queue could not be created. */
//	}


	while(1);
	return 0;
}
