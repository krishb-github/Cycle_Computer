//
// Created by sztuka on 22.01.2023.
//
#include "nmea_parse.h"
#include <stdio.h>

extern uint32_t newSpeed;

void nmea_mem_init(GPS *gps_data)
{
	gps_data->headType = malloc(10);
	gps_data->utcTime = malloc(12);
	gps_data->validStatus = malloc(10);
	gps_data->lat = malloc(10);
	gps_data->latDir = malloc(2);
	gps_data->lon = malloc(12);
	gps_data->lonDir = malloc(2);
	gps_data->speed = malloc(10);
	gps_data->utcDate = malloc(10);
}

void nmea_parse(GPS *gps_data, char *buffer)
{
	char *paramVal;
	int i=0;
	double speedkm, course;
	char *tmp;
	uint8_t breakCheck=0;

	paramVal = strtok(buffer, ",");
	while( paramVal != NULL)
	{
		switch(i)
		{
			case MSGHEAD:
				strcpy(gps_data->headType, paramVal);
				i++;
				break;

			case UTC_TIME:
				sprintf(gps_data->utcTime, "%c%c:%c%c:%c%c", paramVal[0], paramVal[1], paramVal[2], paramVal[3], paramVal[4], paramVal[5]);
				//strcpy(gps_data->utcTime, paramVal);
				if(strcmp(paramVal, "V") == 0)
				{
					newSpeed = 0;
					paramVal = "000000";
					sprintf(gps_data->utcTime, "%.6s", paramVal);
					paramVal = "INVALID";
					strcpy(gps_data->lat, paramVal);
					strcpy(gps_data->lon, paramVal);
					paramVal = "!";
					strcpy(gps_data->latDir, paramVal);
					strcpy(gps_data->lonDir, paramVal);
					sprintf(gps_data->validStatus, "NO LOCK");
					paramVal = "000";
					strcpy(gps_data->speed, paramVal);
					paramVal = "XXXXXX";
					strcpy(gps_data->utcDate, paramVal);

					breakCheck = 1;
				}
				i++;
				break;

			case VALIDSTATUS:
				if(strcmp(paramVal, "A") == 0)
					sprintf(gps_data->validStatus, " LOCKED");
				else if(strcmp(paramVal, "V") == 0)
				{
					newSpeed = 0;
					paramVal = "INVALID";
					strcpy(gps_data->lat, paramVal);
					strcpy(gps_data->lon, paramVal);
					paramVal = "!";
					strcpy(gps_data->latDir, paramVal);
					strcpy(gps_data->lonDir, paramVal);
					sprintf(gps_data->validStatus, "NO LOCK");
					paramVal = "000";
					strcpy(gps_data->speed, paramVal);
					paramVal = "XXXXXX";
					strcpy(gps_data->utcDate, paramVal);

					breakCheck = 1;
				}
				i++;
				break;

			case LAT:
				strcpy(gps_data->lat, paramVal);
				i++;
				break;

			case LATDIR:
				strcpy(gps_data->latDir, paramVal);
				i++;
				break;

			case LONG:
				strcpy(gps_data->lon, paramVal);
				i++;
				break;

			case LONGDIR:
				strcpy(gps_data->lonDir, paramVal);
				i++;
				break;

			case SPEED:
				speedkm = strtod(paramVal, &tmp);
				speedkm = (double)speedkm * 1.852;
				newSpeed = speedkm;
				sprintf(paramVal, "%03d", (int)speedkm);
				strcpy(gps_data->speed, paramVal);
				i++;
				break;

			case COURSE:
				course = strtod(paramVal, &tmp);
				if(course >= 010100)
				{
					strcpy(gps_data->utcDate, paramVal);
					breakCheck = 1;
				}
				i++;
				break;

			case DATE:
				sprintf(gps_data->utcDate, "%c%c-%c%c-%c%c", paramVal[0], paramVal[1], paramVal[2], paramVal[3], paramVal[4], paramVal[5]);
				//strcpy(gps_data->utcDate, paramVal);
				i++;
				break;

			default:
				i++;
				break;

		}
		paramVal = strtok(NULL, ",");
		if(breakCheck == 1)
			break;
	}
}
