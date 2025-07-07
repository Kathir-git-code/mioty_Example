/*
 *  ======== TMP1075.h ========
 *  TMP1075 Interface
 */
#ifndef ti_sensors_TMP1075__include
#define ti_sensors_TMP1075__include 1

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif

#define TMP1075_TEMP 0x00U
#define TMP1075_CONFIG 0x01U
#define TMP1075_CONFIG_OS_ENABLE 0x8000U
#define TMP1075_CONFIG_OS_DISABLE 0x0000U
#define TMP1075_CONFIG_CR_37HZ 0x0000U
#define TMP1075_CONFIG_CR_18HZ 0x2000U
#define TMP1075_CONFIG_CR_9HZ 0x4000U
#define TMP1075_CONFIG_CR_4HZ 0x6000U
#define TMP1075_CONFIG_FQ_1FAULT 0x0000U
#define TMP1075_CONFIG_FQ_2FAULT 0x0800U
#define TMP1075_CONFIG_FQ_4FAULT 0x1000U
#define TMP1075_CONFIG_FQ_6FAULT 0x1800U
#define TMP1075_CONFIG_POL_LOW 0x0000U
#define TMP1075_CONFIG_POL_HIGH 0x0400U
#define TMP1075_CONFIG_TM_COMP 0x0000U
#define TMP1075_CONFIG_TM_TSTAT 0x0200U
#define TMP1075_CONFIG_SD_CC 0x0000U
#define TMP1075_CONFIG_SD_SD 0x0100U
#define TMP1075_TLOW 0x02U
#define TMP1075_THIGH 0x03U
#define TMP1075_DEV_ID 0x0FU


/*
 *  ======== TMP1075_State ========
 *  Initial configuration state for a TMP1075 sensor
 */
typedef struct TMP1075_State {
    uint16_t config;
    uint16_t tlow;
    uint16_t thigh;

    uint8_t busId;   /* I2C bus id */
    uint8_t devAddr; /* Sensor's I2C address on the bus */

    uint16_t osWait; /* One shot conversion time (in ms)  */
} TMP1075_State;

/*
 *  ======== TMP1075_Handle ========
 *  First argument to all TMP1075 methods
 */
typedef TMP1075_State *TMP1075_Handle;

/*
 *  ======== TMP1075_config ========
 *  Configure device with current settings
 */
extern void TMP1075_config(TMP1075_Handle sensor);

/*
 *  ======== TMP1075_read ========
 *  Read raw temperature register value
 *
 *  The returned value, when shifted right by 4 bits, represents the
 *  temperature in units of 0.0625 degrees Celsius.  For example, 
 *  a return value of 16 represents 0.0625 degrees Celsius.
 *
 *  Conversion functions are provided to convert the raw value returned by this
 *  function to a value in "natural" units.
 *
 *  For example, TMP1075_toMilliCelsius(value) converts a raw temperature
 *  value into an integral temperature value in units of milli-degrees Celsius.
 *  
 *  @param sensor  handle to a TMP1075 state object
 *  @returns       a 32-bit signed result in units of 0.0625 degrees C (when
 *                 shifted right by an appropriate amount)
 *
 *  @see TMP1075_toIntCelsius TMP1075_toFloatCelsius
 *       TMP1075_toMilliCelsius
 */
extern int32_t TMP1075_read(TMP1075_Handle sensor);

/*
 *  ======== TMP1075_toIntCelsius ========
 *  Convert raw temperature register value to whole degrees Celsius
 *
 *  This function rounds values to the nearest integer.
 *
 *  @param raw    32-bit sign extended temperature value read from the
 *                sensor's read function: TMP1075_read()
 *  @returns      signed 32-bit integer representation of temperature in 
 *                degrees Celsius, rounded to the nearest whole number
 *  @see          TMP1075_read
 */
extern int32_t TMP1075_toIntCelsius(int32_t raw);

/*
 *  ======== TMP1075_toMilliCelsius ========
 *  Convert raw field temperature to whole milli-degrees Celsius
 *
 *  This function truncates rather than rounds values.
 *
 *  @param raw    32-bit sign extended temperature value read from the
 *                sensor's read function: TMP1075_read()
 *  @returns      signed 32-bit integer representation of temperature in 
 *                milli-degrees Celsius
 *  @see          TMP1075_read
 */
extern int32_t TMP1075_toMilliCelsius(int32_t raw);

/*
 *  ======== TMP1075_toFloatCelsius ========
 *  Convert raw temperature value to fractional degrees Celsius
 *
 *  @param raw    32-bit sign extended temperature value read from the
 *                sensor's read function: TMP1075_read()
 *  @returns      floating point representation of temperature in degrees
 *                Celsius
 *  @see          TMP1075_read
 */
extern float TMP1075_toFloatCelsius(int32_t raw);

extern  uint8_t writeReg(TMP1075_Handle sensor, uint8_t regAddr, uint16_t value);

extern void TMP1075_configureAlert();


/* support C++ sources */
#ifdef __cplusplus
}
#endif

#endif

