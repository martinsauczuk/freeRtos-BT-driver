#ifndef _MAIN_H_
#define _MAIN_H_

/** \addtogroup rtos_blink FreeRTOS blink example
 ** @{ */

/*==================[inclusions]=============================================*/

#include "app.h"
#include "board.h"
#include "driver.h"
#include "sapi.h"        // <= sAPI header

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"


#define 	TX_QUEUE_SIZE 		100
#define 	RX_QUEUE_SIZE 		100
#define 	LED_TX              LED1
#define 	LED_UPDATE          LED3
#define 	LED_RX		        LED2
#define		UART_CONF			UART_USB


#ifdef __cplusplus
extern "C" {
#endif


xQueueHandle xQueueTx;
xQueueHandle xQueueRx;

static void initHardware(void);
int main(void);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */
