#ifdef __cplusplus
extern "C" {
#endif

/**
 @code
  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 embedded.connectivity.solutions.==============
 @endcode

 @file
 @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 @author     STACKFORCE
 @brief      This header contains information for using the mioty timer hal
             module.
*/

#ifndef __SF_STACK_HAL_MIOTY_TIMER_H__
#define __SF_STACK_HAL_MIOTY_TIMER_H__

/**
 *  @addtogroup SF_STACK_HAL
 *
 *  @details
 *
 *  - <b>mioty Timer API</b>\n
 *    | API Function                                        | Description                                             |
 *    |-----------------------------------------------------|---------------------------------------------------------|
 *    | @ref sf_stack_hal_mioty_timer_init()                | @copybrief sf_stack_hal_mioty_timer_init                |
 *    | @ref sf_stack_hal_mioty_timer_deInit()              | @copybrief sf_stack_hal_mioty_timer_deInit              |
 *    | @ref sf_stack_hal_mioty_timer_delayTill()           | @copybrief sf_stack_hal_mioty_timer_delayTill           |
 *    | @ref sf_stack_hal_mioty_timer_isDeepSleepPossible() | @copybrief sf_stack_hal_mioty_timer_isDeepSleepPossible |
 *  @{
 */

#include <stdint.h>
#include <stdbool.h>

/*! States of the mioty hal. */
typedef enum
{
  /*! The stack is transmitting the first sub. */
  E_STACK_HAL_MIOTY_TIMER_STATE_TX_FIRST_SUB,
  /*! The stack is preparing a sub. */
  E_STACK_HAL_MIOTY_TIMER_STATE_TX_PREPARE,
  /*! The stack is transmitting a sub. */
  E_STACK_HAL_MIOTY_TIMER_STATE_TX_SUB,
  /*! The stack will transmit the last sub. */
  E_STACK_HAL_MIOTY_TIMER_STATE_TX_LAST_SUB,
  /*! The stack is preparing tr receive sub. */
  E_STACK_HAL_MIOTY_TIMER_STATE_RX_PREPARE,
  /*! The stack is receiving a sub. */
  E_STACK_HAL_MIOTY_TIMER_STATE_RX_SUB,
}stackHalMiotyState_t;

/*!
 * @brief Callback function to inform ll module about an occurred time out.
 */
typedef void ( sf_stack_hal_mioty_timer_callbackFunc_t ) ( void );

/*============================================================================*/
/**
 * \brief Getting the precise timer ready. The call of the function
          @ref sf_stack_hal_mioty_timer_delayTill() with the value 0x00 will start the
          timer.
 */
/*============================================================================*/
void sf_stack_hal_mioty_timer_init( void );

/*============================================================================*/
/**
 * \brief Deinitialize the timer. Do what ever you need to save energy.
 */
/*============================================================================*/
void sf_stack_hal_mioty_timer_deInit( void );

/*============================================================================*/
/**
 * \brief Delay the next operation till specified timeout occurred.
 *        In the meantime it is a good idea to enter a sleep mode (with RAM
 *        retention.)
 *
 * \param pTotalPointOfTime Pointer to absolute time value.
 *                          Point of time (based on the transmission of
 *                          first mioty sub packet) when the device should
 *                          perform the next operation.
 *                          A value of 0x00 will activate the timer and will
 *                          not lead to any delay.
 * \param state             Represents the current state of the mioty stack.
 * \param fp_callback       Function pointer which will be called when the delay
 *                          is expired.
 * \return false if the requested pointOfTime is already in the past.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_timer_delayTill( uint64_t* pTotalPointOfTime, stackHalMiotyState_t state,
                            sf_stack_hal_mioty_timer_callbackFunc_t fp_callback );

/*============================================================================*/
/**
 * \brief Function used to request if deep sleep is possible or not.
 *
 * \return true in case deep sleep is possible, false otherwise.
 */
/*============================================================================*/
bool sf_stack_hal_mioty_timer_isDeepSleepPossible(void);

/*! @} */

#endif /* __SF_STACK_HAL_MIOTY_TIMER_H__ */

#ifdef __cplusplus
}
#endif
