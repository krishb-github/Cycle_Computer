//
// Created by sztuka on 22.01.2023.
//

#ifndef STM32_SERIAL_DMA_NEO6M_PARSE_H
#define STM32_SERIAL_DMA_NEO6M_PARSE_H


#include <stm32f1xx_hal.h>
#include <string.h>
#include <stdlib.h>

#define MSGHEAD         0U
#define UTC_TIME        1U
#define VALIDSTATUS     2U
#define LAT             3U
#define LATDIR          4U
#define LONG            5U
#define LONGDIR         6U
#define SPEED           7U
#define DATE            9U
/*******************************************************************************
 * @brief GPS data structure for storing parsed data
 ******************************************************************************/
typedef struct NMEA_DATA {
    char *headType;
    char *utcTime;
    char *validStatus;
    char *lat;
    char *latDir;
    char *lon;
    char *lonDir;
    char *speed;
    char *course;
    char *utcDate;
} GPS;
/*******************************************************************************
 * @brief Parses NMEA data from the GPS module
 * @param gps_data Pointer to GPS struct, writes data to it
 * @param buffer Pointer to buffer string with NMEA data
 ******************************************************************************/
void nmea_parse(GPS *gps_data, char *buffer);
void nmea_mem_init(GPS *gps_data);
#endif //STM32_SERIAL_DMA_NEO6M_PARSE_H


