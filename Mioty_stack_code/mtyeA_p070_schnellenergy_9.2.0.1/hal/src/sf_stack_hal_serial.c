
/**
  @file       sf_stack_hal_serial.c
  @copyright  STACKFORCE GmbH, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      UART implementations supporting the TI-RTOS.
*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include <stdlib.h>
#include <stddef.h>
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
/* Driver include  */
#include <ti/drivers/UART.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Example/Board Header files */
#include "Board.h"

#include "sf_stack_hal_serial.h"
#include "sf_app_hal_lp.h"

/*==============================================================================
                            CONFIGURATION
==============================================================================*/

/*! Sets the length of the Rx ringbuffer. */
#define UART_BUFFER_RX_LEN            40U
/*! Number od bytes to read before calling the rx callback  */
#define UART_RX_LEN                    1U
/*==============================================================================
                            VARIABLES
==============================================================================*/
/* Buffer for the uart-module */
volatile uint8_t gc_uart_RtosBuffer;
/*! Input ring buffer. */
volatile uint8_t gc_uart_bufferRx[UART_BUFFER_RX_LEN];
/*! Pointer to the Rx ring buffer's current write position */
volatile uint8_t *gpc_uart_bufferRxWrite;
/*! Pointer to the Rx ring buffer's current read position */
volatile uint8_t *gpc_uart_bufferRxRead;
/* Global value which indictes if rx is active ore not */
volatile bool gb_readActive;
/* Controls if the loc_uartReadCallback() should be executed or not. */
volatile bool uartAboutToClose = false;
/************************* UART Interface *************************************/
/* Handle for the uart-interface */
UART_Handle uartHandle;

/* Task and tast stack */
Task_Struct gSerialTask;
/* RAM area reserved for the pin shutdown task. */
static uint8_t gSerialTaskStack[512];
/* Semaphore used to gate for lp timer */
static Semaphore_Struct gSerialSem;

/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/
/* Uart read callback. Set by building the uart handle */
static void loc_uartReadCallback(UART_Handle handle, void *buf, size_t count);
/* Local function to handle the uart  read */
static void loc_uartRead(void);
/* Handles the serial task. */
static void loc_halSerialTask(UArg a0, UArg a1);
/*==============================================================================
                          LOCAL  FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief Function called in case of a RX interrupt. This function will trigger
 *        the related SWI to handle the receiption.
 */
/*============================================================================*/
static void loc_uartReadCallback(UART_Handle handle, void *buf, size_t count)
{
  /* Just prevent the whole callback from
   * being executed on UART_readCancel(). There might be a small
   * chance that data is lost from the time the uartAboutToClose() flag is set
   * until readCancel() has completed, but that is ok IMO, because you have
   * already decided to go into standby. */
  if (uartAboutToClose == true)
  {
    return;
  }

  gb_readActive = false;

  *gpc_uart_bufferRxWrite = *((uint8_t*)buf);
  gpc_uart_bufferRxWrite++;

  /*! Check for an overflow of the read pointer and adjust if required. */
  if(gpc_uart_bufferRxWrite >= &gc_uart_bufferRx[UART_BUFFER_RX_LEN])
  {
    gpc_uart_bufferRxWrite = gc_uart_bufferRx;
  } /* if */

  /* Ensure that received data ia read from upper layers.  */
  sf_app_hal_lp_wakeup();

  /* Ensure that the uart read is started again. */
  Semaphore_post(Semaphore_handle(&gSerialSem));

}/* loc_uartReadCallback() */

/*============================================================================*/
/*!
 * @brief Small helper function to avoid duplicated code while serial
 *        receiption.
 */
/*============================================================================*/
static void loc_uartRead(void)
{
  if((gb_readActive == false) && (uartHandle != NULL))
  {
    gb_readActive = true;
    if(UART_read(uartHandle, (void*)&gc_uart_RtosBuffer, 1) == UART_ERROR)
    {
        gb_readActive = false;
    }/* if */
  }/* if */
}/* loc_uartRead() */

/*-----------------------------------------------------------------------------
  loc_halSerialTask()
-----------------------------------------------------------------------------*/
static void loc_halSerialTask(UArg a0, UArg a1)
{
  while(1)
  {
    sf_stack_hal_serial_run();
    /* Wait till next uart isr. */
    Semaphore_pend(Semaphore_handle(&gSerialSem), BIOS_WAIT_FOREVER);
  }/* while(1) */
}/* loc_halSerialTask */

/*==============================================================================
                          API  FUNCTIONS
==============================================================================*/

void sf_stack_hal_serial_taskInit(void)
{
  /* Locals */
  Task_Params taskParams;
  Semaphore_Params semParams;

  /* Configure task. */
  Task_Params_init(&taskParams);
  taskParams.stack = gSerialTaskStack;
  taskParams.stackSize = sizeof(gSerialTaskStack);
  taskParams.priority = 2;
  /* Set priority higher than the normal task. To ensure that we are not
   * interrupted. */
  //taskParams.priority = 3;
  Task_construct(&gSerialTask, loc_halSerialTask, &taskParams, NULL);

  /* Configure shutdown semaphore. */
  Semaphore_Params_init(&semParams);
  semParams.mode = Semaphore_Mode_BINARY;
  Semaphore_construct(&gSerialSem, 0, &semParams);
} /* sf_stack_serialTaskInit () */

/*============================================================================*/
/*! sf_stack_hal_serial_close() */
/*============================================================================*/
void sf_stack_hal_serial_close(void)
{
  if (uartHandle != NULL)
  {
    uartAboutToClose = true;
    UART_close(uartHandle);
    uartHandle = NULL;
    uartAboutToClose = false;
  }
} /* sf_stack_hal_serial_close() */

/*============================================================================*/
/*! sf_stack_hal_serial_init() */
/*============================================================================*/
bool sf_stack_hal_serial_init(void)
{
  bool b_return = false;
  UART_Params uartParams;

  /*! Init the Rx-buffer variables. */
  gpc_uart_bufferRxWrite = gc_uart_bufferRx;
  gpc_uart_bufferRxRead = gc_uart_bufferRx;
  gb_readActive = false;
  uartAboutToClose = false;

  /* Create a UART with data processing off. */
  UART_Params_init(&uartParams);
  uartParams.writeDataMode = UART_DATA_BINARY;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_OFF;
  uartParams.baudRate = 115200;
  uartParams.dataLength = UART_LEN_8;
  uartParams.stopBits = UART_STOP_ONE;
  uartParams.parityType = UART_PAR_NONE;


  uartParams.readMode = UART_MODE_CALLBACK;
  uartParams.writeMode = UART_MODE_BLOCKING;
  uartParams.readCallback = loc_uartReadCallback;

  /* Ensure that the uart is not already in use */
  sf_stack_hal_serial_close();

  uartHandle = UART_open(Board_UART0, &uartParams);

  if (uartHandle != NULL)
  {
    /* Enable the rx interrupt. The callback function "loc_uartReadCallback()"
     * will be called after the first byte was received */
    loc_uartRead();
    b_return = true;
  }/* if */

  return b_return;
} /* sf_stack_hal_serial_init() */

/*============================================================================*/
/* sf_stack_hal_serial_run() */
/*============================================================================*/
void sf_stack_hal_serial_run(void)
{
  if((gb_readActive == false) && (uartHandle != NULL))
  {
    loc_uartRead();
  }/* if */
}/* sf_stack_hal_serial_run() */

/*============================================================================*/
/* sf_stack_hal_serial_write() */
/*============================================================================*/
uint16_t sf_stack_hal_serial_write(uint8_t *pc_data, uint16_t i_len)
{
  int i;
  uint16_t i_txLen = 0x00U;

  if((uartHandle != NULL) && (uartAboutToClose == false))
  {
    /* Call the RTOS uart write function. This function will block until all byte
     * are sent */
    i = UART_write(uartHandle, (void*)pc_data, i_len);

    /* Check if writing the data was successfull */
    if(i != UART_ERROR)
    {
      i_txLen = (uint16_t)i;
    }/* if */
  }/* if */
  else
  {
    /* The uart is currently deactivated. The data can not be send!
     * To don't block the device we will ignore this request */
     i_txLen = i_len;
  }

  /*! Return the number of written byte. */
  return i_txLen;
} /* sf_stack_hal_serial_write() */

/*============================================================================*/
/* sf_stack_hal_serial_read() */
/*============================================================================*/
uint16_t sf_stack_hal_serial_read(uint8_t *pc_data, uint16_t i_len)
{
  uint16_t i;

  for(i = 0U; (i < i_len) && (sf_stack_hal_serial_cntRxBytes() > 0U); i++)
  {
    /* Read the Rx buffer and decrement the received bytes */
    pc_data[i] = *gpc_uart_bufferRxRead++;

    /** Check for an overflow of the read pointer and adjust if required. */
    if(gpc_uart_bufferRxRead == &gc_uart_bufferRx[UART_BUFFER_RX_LEN])
    {
      gpc_uart_bufferRxRead = gc_uart_bufferRx;
    } /* if */
  } /* for */
  return i;
} /* sf_stack_hal_serial_read() */

/*============================================================================*/
/* sf_stack_hal_serial_cntRxBytes() */
/*============================================================================*/
uint16_t sf_stack_hal_serial_cntRxBytes(void)
{
  uint16_t i_cnt;

  if(gpc_uart_bufferRxWrite > gpc_uart_bufferRxRead)
  {
    i_cnt = gpc_uart_bufferRxWrite - gpc_uart_bufferRxRead;
  }
  else if(gpc_uart_bufferRxWrite < gpc_uart_bufferRxRead)
  {
    i_cnt = &gc_uart_bufferRx[UART_BUFFER_RX_LEN] - gpc_uart_bufferRxRead;
    i_cnt +=  gpc_uart_bufferRxWrite - gc_uart_bufferRx;
  }
  else
  {
    i_cnt = 0x00;
  }/* if() ... else if ... else */

  return i_cnt;
} /* sf_stack_hal_serial_cntRxBytes() */

/*============================================================================*/
/* sf_stack_hal_serial_isBusy() */
/*============================================================================*/
bool sf_stack_hal_serial_isBusy(void)
{
    return false;
} /* sf_stack_hal_serial_isBusy() */
