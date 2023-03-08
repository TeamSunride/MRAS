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
#define RADIO_FREQUENCY                     2406

// bandwidth in kHz
#define RADIO_BANDWIDTH                     203.125

// LoRa spreading factor
#define RADIO_SPREADING_FACTOR              12

// LoRa coding rate denominator. Allowed values range from 5 to 8.
#define RADIO_CODING_RATE                   7

// LoRa sync word
#define RADIO_SYNC_WORD                     0x22

// output power in dBm
#define RADIO_POWER                         (4) // -18 to 13 dBm on SX128x

// LoRa preamble length in symbols. Allowed values range from 1 to 65535.
#define RADIO_PREAMBLE_LENGTH               12

// TCXO reference voltage to be set on DIO3. Defaults to 1.6 V, set to 0 to skip.
#define RADIO_TCXO_VOLTAGE                  0

// Whether to use only LDO regulator (true) or DC-DC regulator (false). Defaults to false.
// TODO: investigate the implications of this
// We've had this set to true for all testing so far. (incl. April 2022 test in peaks)
#define RADIO_USE_LDO                       true

#ifdef BUILD_ENV_rocket

#define RADIO_CHIP_SELECT_PIN               31
#define RADIO_DIO1_PIN                      33
#define RADIO_RESET_PIN                     32
#define RADIO_BUSY_PIN                      34
#define RADIO_RX_ENABLE_PIN                 36
#define RADIO_TX_ENABLE_PIN                 35
#define RADIO_SPI_BUS                       SPI1

#elif BUILD_ENV_ground

#define RADIO_CHIP_SELECT_PIN               0
#define RADIO_DIO1_PIN                      1
#define RADIO_RESET_PIN                     10
#define RADIO_BUSY_PIN                      9
#define RADIO_RX_ENABLE_PIN                 6
#define RADIO_TX_ENABLE_PIN                 5
#define RADIO_SPI_BUS                       SPI

#endif

/**
 * ================================
 * LOGGING
 * ================================
 */

#define MRAS_STARTUP_STRING "\n"\
"   Welcome to\n"\
"  __  __   _____                _____ \n"\
" |  \\/  | |  __ \\      /\\      / ____|\n"\
" | \\  / | | |__) |    /  \\    | (___  \n"\
" | |\\/| | |  _  /    / /\\ \\    \\___ \\ \n"\
" | |  | | | | \\ \\   / ____ \\   ____) |\n"\
" |_|  |_| |_|  \\_\\ /_/    \\_\\ |_____/ \n"\
"                                      \n\n"\
"   ❤ 2022 TeamSunride ❤\n\n"\
"=================================================\n\n"

#endif //MRAS_MRAS_CONFIG_H
