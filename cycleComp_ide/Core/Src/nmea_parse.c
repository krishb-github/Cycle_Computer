//
// Created by sztuka on 22.01.2023.
//
#include "nmea_parse.h"
#include <stdio.h>

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
	gps_data->utcDate = malloc(8);
}

void nmea_parse(GPS *gps_data, char *buffer)
{
	char *paramVal;
	int i=0;
	double speedkm;
	char *tmp;

	paramVal = strtok(buffer, ",");
	while( paramVal != NULL)
	{
		switch(i)
		{
			case MSGHEAD:
				//gps_data->headType = malloc(10);
				strcpy(gps_data->headType, paramVal);
				i++;
				break;

			case UTC_TIME:
				//gps_data->utcTime = malloc(12);
				sprintf(gps_data->utcTime, "%.6s", paramVal);
				//strcpy(gps_data->utcTime, paramVal);
				i++;
				break;

			case VALIDSTATUS:
				//gps_data->validStatus = malloc(10);
				if(strcmp(paramVal, 'A') != 0)
					sprintf(gps_data->validStatus, "LOCKED");
				else
					sprintf(gps_data->validStatus, "NO LOCK");
				//strcpy(gps_data->validStatus, paramVal);
				i++;
				break;

			case LAT:
				//gps_data->lat = malloc(10);
				strcpy(gps_data->lat, paramVal);
				i++;
				break;

			case LATDIR:
				//gps_data->latDir = malloc(2);
				strcpy(gps_data->latDir, paramVal);
				i++;
				break;

			case LONG:
				//gps_data->lon = malloc(12);
				strcpy(gps_data->lon, paramVal);
				i++;
				break;

			case LONGDIR:
				//gps_data->lonDir = malloc(2);
				strcpy(gps_data->lonDir, paramVal);
				i++;
				break;

			case SPEED:
				//gps_data->speed = malloc(10);
				speedkm = strtod(paramVal, &tmp);
				speedkm *= 1.852;
				sprintf(paramVal, "%03d", (int)speedkm);
				strcpy(gps_data->speed, paramVal);
				i++;
				break;

			case DATE:
				//gps_data->utcDate = malloc(8);
				strcpy(gps_data->utcDate, paramVal);
				i++;
				break;

			default:
				i++;
				break;

		}
		paramVal = strtok(NULL, ",");
	}
}
