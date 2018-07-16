#include "main.h"

// Cola de transmisión
xQueueHandle xQueueTx;

// Cola de recepción
xQueueHandle xQueueRx;

/**
 *	Configura la placa
 */
static void initHardware(void) {
   /* Inicializar la placa */
   boardConfig();

   /* Inicializar Uart driver*/
   uartConfig( UART_CONF, 9600 );

   /* Inicializar Uart debug */
   uartConfig( UART_DEBUG, 115200 );
}

/**
 *	Bucle principal
 */
int main( void )
{

	initHardware();

	// Creación de las colas
    xQueueTx = xQueueCreate(TX_QUEUE_SIZE, sizeof( char ) );
    xQueueRx = xQueueCreate(RX_QUEUE_SIZE, sizeof( char ) );

    // Mostrar menú por primera vez
    vShowMenu();

    // Si por algún motivo las colas son nulas, terminar el programa
	if( (xQueueTx != NULL ) && ( xQueueRx != NULL ) )
	{
		// Tareas relacionadas a la appp
		xTaskCreate( vResponseMenuTask, "ResponseMenu", 240, ( void * ) 200, 1, NULL );

		// Tareas del driver
		xTaskCreate( vDriverTxTask, "Tx", 240, ( void * ) 100, 1, NULL );
		xTaskCreate( vDriverRxTask, "Rx", 240, ( void * ) 100, 1, NULL );

		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();
	}
	else
	{
		/* No pueden ser creadas las colas, no puede iniciar */
	}


	while(1);
	return 0;
}
