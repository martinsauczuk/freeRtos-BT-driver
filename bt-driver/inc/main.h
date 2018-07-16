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


#define 	TX_QUEUE_SIZE 		500
#define 	RX_QUEUE_SIZE 		500
#define 	LED_TX              LED1
#define 	LED_UPDATE          LED3
#define 	LED_RX		        LED2
#define		UART_CONF			UART_232
#define		UART_DEBUG			UART_USB


#ifdef __cplusplus
extern "C" {
#endif


int main(void);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */
