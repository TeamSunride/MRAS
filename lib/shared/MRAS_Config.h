//
// Created by Tom Danvers on 05/01/2023.
//

#ifndef MRAS_MRAS_CONFIG_H
#define MRAS_MRAS_CONFIG_H

/**
 * ================================
 * SENSORS
 * ================================
 */
#ifdef BUILD_ENV_rocket

#define MRAS_LSM6DSO32_CHIP_SELECT          40
#define MRAS_LSM6DSO32_SPI_BUS              SPI
#define MRAS_LSM6DSO32_SPI_FREQUENCY        5e6

#define MRAS_LIS3MDL_CHIP_SELECT            37
#define MRAS_LIS3MDL_SPI_BUS                MRAS_LSM6DSO32_SPI_BUS
#define MRAS_LIS3MDL_SPI_FREQUENCY          MRAS_LSM6DSO32_SPI_FREQUENCY

#define MRAS_MS5607_I2C_ADDRESS             0x76
#define MRAS_MS5607_I2C_BUS                 Wire2

#define MRAS_ADXL375_CHIP_SELECT            3
#define MRAS_ADXL375_SPI_BUS                MRAS_LSM6DSO32_SPI_BUS
#define MRAS_ADXL375_SPI_FREQUENCY          MRAS_LSM6DSO32_SPI_FREQUENCY

#define MRAS_GNSS_I2C_BUS                   Wire2
#define MRAS_GNSS_I2C_FREQUENCY             400000

#endif
/**
 * ================================
 * TELEMETRY RADIO
 * ================================
 */

// carrier frequency in MHz
#define RADIO_FREQUENCY                     868.0

// bandwidth in kHz
#define RADIO_BANDWIDTH                     500.0

// LoRa spreading factor
#define RADIO_SPREADING_FACTOR              5

// LoRa coding rate
#define RADIO_CODING_RATE                   5

// LoRa sync word
#define RADIO_SYNC_WORD                     0x22

// output power in dBm
#define RADIO_POWER                         14

#ifdef BUILD_ENV_rocket

#define RADIO_CHIP_SELECT_PIN               31
#define RADIO_DIO1_PIN                      33
#define RADIO_RESET_PIN                     32
#define RADIO_BUSY_PIN                      34
#define RADIO_RX_ENABLE_PIN                 36
#define RADIO_TX_ENABLE_PIN                 35

#elif BUILD_ENV_ground

#define RADIO_CHIP_SELECT_PIN               0
#define RADIO_DIO1_PIN                      1
#define RADIO_RESET_PIN                     10
#define RADIO_BUSY_PIN                      9
#define RADIO_RX_ENABLE_PIN                 6
#define RADIO_TX_ENABLE_PIN                 5

#endif
#endif //MRAS_MRAS_CONFIG_H
