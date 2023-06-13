/*
 * dispMap.c
 *
 *  Created on: Jun 13, 2023
 *      Author: zirk
 */
#include "main.h"
#include "fonts.h"
#include "ssd1306.h"
#include "test.h"

dispTable homeScr =
{
	.currentChoice = 0,
	.maxChoice = 4,
	.choiceName = {"STATS", "SYS_INFO", "GPS_INFO", "VEHICLE_STAT"},
};

dispTable *currentScr = &homeScr;

void displayRefresh(ROT_INPUT rotInput)
{
	if(rotInput == INCR)
	{
		if(currentScr->currentChoice == (currentScr->maxChoice-1))
			currentScr->currentChoice = 0;
		else
			currentScr->currentChoice += 1;

		  SSD1306_Clear();
		  SSD1306_GotoXY (0,0);
		  SSD1306_Puts (currentScr->choiceName[currentScr->currentChoice], &Font_11x18, 1);
		  SSD1306_UpdateScreen(); //display
	}
	else if(rotInput == DECR)
	{
		if(currentScr->currentChoice == 0)
			currentScr->currentChoice = (currentScr->maxChoice-1);
		else
			currentScr->currentChoice -= 1;

		  SSD1306_Clear();
		  SSD1306_GotoXY (0,0);
		  SSD1306_Puts (currentScr->choiceName[currentScr->currentChoice], &Font_11x18, 1);
		  SSD1306_UpdateScreen(); //display
	}
}
