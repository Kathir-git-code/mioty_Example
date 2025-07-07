#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     STACKFORCE
 * @brief      Stack application extensions
 *
 */

#ifndef __SF_APP_EX_H__
#define __SF_APP_EX_H__

/**
 *  @defgroup SF_APP_EX Stackforce Stack application extension interface
 *
 *  @details
 *
 *  - Application Programming Interface (API) of the <b>Stack application extensions</b>\n
 *    | API Function                                    | Description                                         |
 *    |-------------------------------------------------|-----------------------------------------------------|
 *    | @ref sf_app_ex_init()                     | @copybrief sf_app_ex_init                     |
 *  @{
 */

#include <stdbool.h>
#include "sf_stack_types.h"

/**
  @brief   Initialization of the application extensions.

  @return Returns the status @ref stackReturn_t .
*/
stackReturn_t sf_app_ex_init(void);

/**@} end of SF_APP_EX */
/******************************************************************************/

#endif // __SF_APP_EX_H__

#ifdef __cplusplus
}
#endif
