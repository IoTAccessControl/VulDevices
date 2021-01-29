/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

extern void xPortSysTickHandler( void );
static void prvInitializeHeap( void );
static void prvEchoClientTask();
static void testEthNetwork();

void SysTick_Handler(void)
{
	HAL_IncTick();

	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	{
		xPortSysTickHandler();
	}
}


void initFreeRTOS() {
	printf("initFreeRTOS\n");
	prvInitializeHeap();
	xTaskCreate( prvEchoClientTask,  "prvEchoClientTask", configMINIMAL_STACK_SIZE, 
		( void * ) NULL, NULL,  NULL );  
	vTaskStartScheduler();
}

void vApplicationDaemonTaskStartupHook( void ) {
	printf("vApplicationDaemonTaskStartupHook\n");
}


static void prvInitializeHeap( void )
{
	static uint8_t ucHeap1[ configTOTAL_HEAP_SIZE ];
	static uint8_t ucHeap2[ 27 * 1024 ] __attribute__( ( section( ".freertos_heap2" ) ) );
    HeapRegion_t xHeapRegions[] =
    {
        { ( unsigned char * ) ucHeap2, sizeof( ucHeap2 ) },
        { ( unsigned char * ) ucHeap1, sizeof( ucHeap1 ) },
        { NULL,                                        0 }
    };

    vPortDefineHeapRegions( xHeapRegions );
}

void prvEchoClientTask() {
	testEthNetwork();
	while (1) {
		//printf("prvEchoClientTask\n");
		vTaskDelay(500);
	}
}


/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle
	 * task's state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetTimerTaskMemory() to provide the memory that is
 * used by the RTOS daemon/time task. */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
	portDISABLE_INTERRUPTS();

	/* Loop forever */
	for( ; ; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
}

/**
 * @brief Warn user if pvPortMalloc fails.
 *
 * Called if a call to pvPortMalloc() fails because there is insufficient
 * free memory available in the FreeRTOS heap.  pvPortMalloc() is called
 * internally by FreeRTOS API functions that create tasks, queues, software
 * timers, and semaphores.  The size of the FreeRTOS heap is set by the
 * configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
 *
 */
void vApplicationMallocFailedHook()
{
    taskDISABLE_INTERRUPTS();
    for( ;; );
}

__attribute__(( weak )) void vPortSetupTimerInterrupt( void ) {
}

/*
Network interface
*/
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_DNS.h"
#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"
#include <stdarg.h>

void vLoggingPrintf( const char * pcFormatString, ... ) {
	va_list ap;
	va_start(ap, pcFormatString);
	vprintf(pcFormatString, ap);
	va_end(ap);
}

const char *pcApplicationHostnameHook( void ) {
	
}

UBaseType_t uxRand() {
	
}

BaseType_t xApplicationDNSQueryHook( const char *pcName ) {
	
}

void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent ) {
	
}

BaseType_t xNetworkInterfaceInitialise( void ) {

}

BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                        BaseType_t xReleaseAfterSend ) {
}
void vNetworkInterfaceAllocateRAMToBuffers( NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ] ) {

}

BaseType_t xGetPhyLinkStatus( void ) {
}

extern void prvProcessEthernetPacket( NetworkBufferDescriptor_t * const pxNetworkBuffer );

void testEthNetwork() {
	printf("testEthNetwork\n");
	prvProcessEthernetPacket(NULL);
}
