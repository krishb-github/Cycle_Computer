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
#include "dispMap.h"
#include <stdio.h>

extern dispTable *currentScr;
dispTable gpsInfo;
dispTable serviceInt;
dispTable cycInfo;
dispTable homeScr;
dispTable showSpeed;

dispTable gpsInfo =
{
		.currentChoice = 0,
		.maxChoice = 0,
		.choiceName = {},
		.nextChoice = {},
};

dispTable serviceInt =
{
		.currentChoice = 0,
		.maxChoice = 0,
		.choiceName = {},
		.nextChoice = {},
};

dispTable cycInfo =
{
		.currentChoice = 0,
		.maxChoice = 5,
		.choiceName = {"TRIP_RESET", "MILES", "KM", "SERVICE", "HOME"},
		.nextChoice = {NULL, NULL, NULL, &serviceInt, &homeScr},
};

dispTable homeScr =
{
	.currentChoice = 0,
	.maxChoice = 3,
	.choiceName = {"GPS_INFO", "CYCLE_INFO", "BACK"},
	.nextChoice = {&gpsInfo, &cycInfo, &showSpeed},
};



extern dispTable *currentScr;

void displayRefresh(ROT_INPUT rotInput, dispTable *currentScr)
{
	if(currentScr == &showSpeed)
	{
		  SSD1306_GotoXY (0,0);
		  SSD1306_Puts ("ODO : 1234567", &Font_11x18, 1);
		  SSD1306_GotoXY (0, 17);
		  SSD1306_Puts ("TRIP : 1234", &Font_11x18, 1);
		  SSD1306_GotoXY (0, 34);
		  SSD1306_Puts ("SPD : xx kmph", &Font_11x18, 1);
		  SSD1306_UpdateScreen(); //display

		  return;
	}

	if(currentScr == &serviceInt)
	{
		int intvl = 500;
		char *tmp;
		sprintf(tmp, "%d",intvl);
		//while(get_int_status())
		{
			  SSD1306_GotoXY (0,0);
			  SSD1306_Puts ("INTVL : ", &Font_11x18, 1);
			  SSD1306_Puts (tmp, &Font_11x18, 1);

			  SSD1306_UpdateScreen(); //display
			  return;
		}
	}

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
	else
	{
		  SSD1306_Clear();
		  SSD1306_GotoXY (0,0);
		  SSD1306_Puts (currentScr->choiceName[currentScr->currentChoice], &Font_11x18, 1);
		  SSD1306_UpdateScreen(); //display
	}
}

void uiNavigation(uint8_t *choiceValid, ROT_INPUT rotInput, ROT_SWITCH *rotSw)
{
	  if((currentScr == &showSpeed) | (currentScr == &serviceInt))
	  {
		  currentScr = &homeScr;
	  }

	  if(*choiceValid && (*rotSw==PUSHED))
	  {
		  currentScr = currentScr->nextChoice[currentScr->currentChoice];
		  rotInput = NA;
		  *rotSw = NOT_PUSHED;
		  displayRefresh(rotInput, currentScr);
	  }
	  else if((*choiceValid) && (rotInput != NA))
	  {
		  displayRefresh(rotInput, currentScr);
	  }
	  *choiceValid = 0;

}





