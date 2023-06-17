//
// Created by Tom Danvers on 05/01/2023.
//

#ifndef MRAS_MRAS_CONFIG_H
#define MRAS_MRAS_CONFIG_H

#define ENABLE_BUZZER                       true
#define ENABLE_BEEPING                      false

#define USE_ASSISTNOW                       false
#define USING_AMPLIFIER                     true

#define MAXM10s_ID                          6
#define SAMM10Q_ID                          7

/**
 * ================================
 * SENSORS
 * ================================
 */

#ifdef BUILD_ENV_kalpha

#define MRAS_LSM6DSO32_CHIP_SELECT          4
#define MRAS_LSM6DSO32_SPI_BUS              SPI1
#define MRAS_LSM6DSO32_SPI_FREQUENCY        5e6

#define MRAS_LIS3MDL_CHIP_SELECT            40
#define MRAS_LIS3MDL_SPI_BUS                MRAS_LSM6DSO32_SPI_BUS
#define MRAS_LIS3MDL_SPI_FREQUENCY          MRAS_LSM6DSO32_SPI_FREQUENCY

#define MRAS_MS5607_I2C_ADDRESS             0x76
#define MRAS_MS5607_I2C_BUS                 Wire
#define MRAS_MS5607_I2C_FREQUENCY           400000

#define MRAS_ADXL375_CHIP_SELECT            20
#define MRAS_ADXL375_SPI_BUS                MRAS_LSM6DSO32_SPI_BUS
#define MRAS_ADXL375_SPI_FREQUENCY          MRAS_LSM6DSO32_SPI_FREQUENCY

#define MRAS_MAX_M10S_GNSS_I2C_BUS          Wire
#define MRAS_MAX_M10S_GNSS_I2C_FREQUENCY    MRAS_MS5607_I2C_FREQUENCY

#define MRAS_SAM_M10Q_GNSS_I2C_BUS          Wire1
#define MRAS_SAM_M10Q_GNSS_I2C_FREQUENCY    MRAS_MS5607_I2C_FREQUENCY

#define BUZZER_PIN                          37

#endif

#ifdef BUILD_ENV_dart

#define MRAS_LSM6DSO32_CHIP_SELECT          40
#define MRAS_LSM6DSO32_SPI_BUS              SPI
#define MRAS_LSM6DSO32_SPI_FREQUENCY        5e6

#define MRAS_LIS3MDL_CHIP_SELECT            37
#define MRAS_LIS3MDL_SPI_BUS                MRAS_LSM6DSO32_SPI_BUS
#define MRAS_LIS3MDL_SPI_FREQUENCY          MRAS_LSM6DSO32_SPI_FREQUENCY

#define MRAS_MS5607_I2C_ADDRESS             0x76
#define MRAS_MS5607_I2C_BUS                 Wire2
#define MRAS_MS5607_I2C_FREQUENCY           400000

#define MRAS_ADXL375_CHIP_SELECT            3
#define MRAS_ADXL375_SPI_BUS                MRAS_LSM6DSO32_SPI_BUS
#define MRAS_ADXL375_SPI_FREQUENCY          MRAS_LSM6DSO32_SPI_FREQUENCY

#define MRAS_MAX_M10S_GNSS_I2C_BUS                   MRAS_MS5607_I2C_BUS
#define MRAS_MAX_M10S_GNSS_I2C_FREQUENCY             MRAS_MS5607_I2C_FREQUENCY

#define BUZZER_PIN                          10

#endif
/**
 * ================================
 * TELEMETRY RADIO
 * ================================
 */

// carrier frequency in MHz
#define RADIO_FREQUENCY                     869.525 // centre of the 869.4-869.65MHz band with 250kHz bandwidth

// bandwidth in kHz
#define RADIO_BANDWIDTH                     250

// LoRa spreading factor
#define RADIO_SPREADING_FACTOR              5

// LoRa coding rate denominator. Allowed values range from 5 to 8.
#define RADIO_CODING_RATE                   8

// LoRa sync word
#define RADIO_SYNC_WORD                     0x22

// output power in dBm - up to 22dbm for 868/915,
#define RADIO_POWER                         15

// LoRa preamble length in symbols. Allowed values range from 1 to 65535.
#define RADIO_PREAMBLE_LENGTH               8

// TCXO reference voltage to be set on DIO3. Defaults to 1.6 V, set to 0 to skip.
#define RADIO_TCXO_VOLTAGE                  0

// Whether to use only LDO regulator (true) or DC-DC regulator (false). Defaults to false.
// TODO: investigate the implications of this
// We've had this set to true for all testing so far. (incl. April 2022 test in peaks)
#define RADIO_USE_LDO                       true

#ifdef BUILD_ENV_kalpha

#define RADIO_CHIP_SELECT_PIN               30
#define RADIO_DIO1_PIN                      10
#define RADIO_RESET_PIN                     25
#define RADIO_BUSY_PIN                      8
#define RADIO_RX_ENABLE_PIN                 24
#define RADIO_TX_ENABLE_PIN                 9
#define RADIO_SPI_BUS                       SPI

#endif

#ifdef BUILD_ENV_dart

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
