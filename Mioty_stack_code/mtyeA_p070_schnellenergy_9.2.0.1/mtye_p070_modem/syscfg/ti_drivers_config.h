/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the CC1352R1_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_CC1352R1_LAUNCHXL
#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== CCFG ========
 */


/*
 *  ======== ADC ========
 */

/* DIO23 */
extern const uint_least8_t              CONFIG_BAT_SENSE_CONST;
#define CONFIG_BAT_SENSE                0
#define CONFIG_TI_DRIVERS_ADC_COUNT     1


/*
 *  ======== AESECB ========
 */

extern const uint_least8_t                  CONFIG_AESECB_0_CONST;
#define CONFIG_AESECB_0                     0
#define CONFIG_TI_DRIVERS_AESECB_COUNT      1


/*
 *  ======== GPIO ========
 */
/* Owned by CONFIG_BAT_SENSE as  */
extern const uint_least8_t CONFIG_GPIO_BAT_SENSE_AIN_CONST;
#define CONFIG_GPIO_BAT_SENSE_AIN 23

extern const uint_least8_t CONFIG_GPIO_REVERSEPULSE_DIO28_CONST;
#define CONFIG_GPIO_REVERSEPULSE_DIO28 28

extern const uint_least8_t CONFIG_VIBRATION_SENS_DIO18_CONST;
#define CONFIG_VIBRATION_SENS_DIO18 18

extern const uint_least8_t CONFIG_CC1190_PA_EN_DIO3_CONST;
#define CONFIG_CC1190_PA_EN_DIO3 3

extern const uint_least8_t CONFIG_CC1190_LNA_EN_DIO4_CONST;
#define CONFIG_CC1190_LNA_EN_DIO4 4

extern const uint_least8_t CONFIG_CC1190_HGM_DIO5_CONST;
#define CONFIG_CC1190_HGM_DIO5 5

extern const uint_least8_t CONFIG_GPIO_BOTTOMLED_DIO_11_CONST;
#define CONFIG_GPIO_BOTTOMLED_DIO_11 11

extern const uint_least8_t CONFIG_GPIO_MODE_SELECT_DIO26_CONST;
#define CONFIG_GPIO_MODE_SELECT_DIO26 26

extern const uint_least8_t CONFIG_GPIO_REED_SWITCH_DIO27_CONST;
#define CONFIG_GPIO_REED_SWITCH_DIO27 27

extern const uint_least8_t CONFIG_GPIO_TOP_LED2_DIO30_CONST;
#define CONFIG_GPIO_TOP_LED2_DIO30 30

extern const uint_least8_t CONFIG_GPIO_FORWARDPULSE_DIO6_CONST;
#define CONFIG_GPIO_FORWARDPULSE_DIO6 6

extern const uint_least8_t CONFIG_GPIO_WATCHDOGTIMER_DONE_DIO10_CONST;
#define CONFIG_GPIO_WATCHDOGTIMER_DONE_DIO10 10

extern const uint_least8_t CONFIG_GPIO_WDT_WAKEUP_DIO9_CONST;
#define CONFIG_GPIO_WDT_WAKEUP_DIO9 9

extern const uint_least8_t CONFIG_BAT_VOLTAGE_CRTL_DIO14_CONST;
#define CONFIG_BAT_VOLTAGE_CRTL_DIO14 14

extern const uint_least8_t CONFIG_EN2_DIO29_CONST;
#define CONFIG_EN2_DIO29 24

/* Owned by CONFIG_I2C_0 as  */
extern const uint_least8_t CONFIG_GPIO_I2C_0_SDA_CONST;
#define CONFIG_GPIO_I2C_0_SDA 12

/* Owned by CONFIG_I2C_0 as  */
extern const uint_least8_t CONFIG_GPIO_I2C_0_SCL_CONST;
#define CONFIG_GPIO_I2C_0_SCL 13

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_SCLK_CONST;
#define CONFIG_GPIO_SPI_0_SCLK 20

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_MISO_CONST;
#define CONFIG_GPIO_SPI_0_MISO 21

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_MOSI_CONST;
#define CONFIG_GPIO_SPI_0_MOSI 19

/* Owned by CONFIG_UART0 as  */
extern const uint_least8_t CONFIG_PIN_2_CONST;
#define CONFIG_PIN_2 15

/* Owned by CONFIG_UART0 as  */
extern const uint_least8_t CONFIG_PIN_3_CONST;
#define CONFIG_PIN_3 7

/* Owned by CONFIG_UART2_0 as  */
extern const uint_least8_t CONFIG_GPIO_UART2_0_TX_CONST;
#define CONFIG_GPIO_UART2_0_TX 17

/* Owned by CONFIG_UART2_0 as  */
extern const uint_least8_t CONFIG_GPIO_UART2_0_RX_CONST;
#define CONFIG_GPIO_UART2_0_RX 16

/* Owned by CONFIG_NVS_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_0_CONST;
#define CONFIG_GPIO_0 22

/* The range of pins available on this device */
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== I2C ========
 */

/*
 *  SCL: DIO13
 *  SDA: DIO12
 */
extern const uint_least8_t              CONFIG_I2C_0_CONST;
#define CONFIG_I2C_0                    0
#define CONFIG_TI_DRIVERS_I2C_COUNT     1

/* ======== I2C Addresses and Speeds ======== */
#include <ti/drivers/I2C.h>

/* ---- CONFIG_I2C_0 I2C bus components ---- */

/* no components connected to CONFIG_I2C_0 */

/* max speed unspecified, defaulting to 100 Kbps */
#define CONFIG_I2C_0_MAXSPEED   (100U) /* Kbps */
#define CONFIG_I2C_0_MAXBITRATE ((I2C_BitRate)I2C_100kHz)


/*
 *  ======== NVS ========
 */

/*
 *  MOSI: DIO19
 *  MISO: DIO21
 *  SCLK: DIO20
 *  SS: undefined
 */
extern const uint_least8_t              CONFIG_NVSEXTERNAL_CONST;
#define CONFIG_NVSEXTERNAL              0
#define CONFIG_TI_DRIVERS_NVS_COUNT     1




/*
 *  ======== SPI ========
 */

/*
 *  MOSI: DIO19
 *  MISO: DIO21
 *  SCLK: DIO20
 */
extern const uint_least8_t              CONFIG_SPI_0_CONST;
#define CONFIG_SPI_0                    0
#define CONFIG_TI_DRIVERS_SPI_COUNT     1


/*
 *  ======== UART ========
 */

/*
 *  TX: DIO15
 *  RX: DIO7
 */
extern const uint_least8_t              CONFIG_UART0_CONST;
#define CONFIG_UART0                    0
#define CONFIG_TI_DRIVERS_UART_COUNT    1


/*
 *  ======== UART2 ========
 */

/*
 *  TX: DIO17
 *  RX: DIO16
 */
extern const uint_least8_t                  CONFIG_UART2_0_CONST;
#define CONFIG_UART2_0                      0
#define CONFIG_TI_DRIVERS_UART2_COUNT       1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
