#ifndef __SF_DRV_CLOCK_H__
#define __SF_DRV_CLOCK_H__

/**
  @file       sf_drv_clock.h
  @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
  @author     STACKFORCE
  @brief      Hardware Abstraction Layer Application Programming Interface
              for clock implementations.
*/


/*==============================================================================
                         INCLUDES
==============================================================================*/

/* Standard libraries */
#include <stdbool.h>
#include <stdint.h>

#include <ti/sysbios/knl/Clock.h>

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initializes the clock.
  @return Returns pointer to the clock handle.
*/
Clock_Handle sf_drv_clock_init(void);

/**
  @brief  Starts the clock with a defined timeout.
  @param  pClockHandle   Pointer to the clock handle which should be
                         started.
  @param  i_timeout      Time in microseconds.
  @param  fp_rtc         Pointer to the callback function.
  @return Returns @c true if starting the timer was successful.
*/
bool sf_drv_clock_start(Clock_Handle pClockHandle, uint32_t i_timeout,
                        Clock_FuncPtr fp_clockCb);

/**
  @brief  Stops the RTC for the timer event.

  @param  pClockHandle   Pointer to the clock handle which should be
                         stoped.

  @return Returns @c true if stop the timer was successful.
*/
bool sf_drv_clock_stop(Clock_Handle pClockHandle);


#endif /* __sf_drv_clock_H__ */
