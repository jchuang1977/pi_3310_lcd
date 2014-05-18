/*
=================================================================================
 Name        : pcd8544_rpi.c
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

modifed by hobbyologist: www.bdug.org.au

 Description :
     A simple PCD8544 LCD (Nokia3310/5110) for Raspberry Pi for displaying some system informations.
	 Makes use of WiringPI-library of Gordon Henderson (https://projects.drogon.net/raspberry-pi/wiringpi/)

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 LCD pins      Raspberry Pi
	 LCD1 - GND    P06  - GND
	 LCD2 - VCC    P01 - 3.3V
	 LCD3 - CLK    P11 - GPIO0
	 LCD4 - Din    P12 - GPIO1
	 LCD5 - D/C    P13 - GPIO2
	 LCD6 - CS     P15 - GPIO3
	 LCD7 - RST    P16 - GPIO4
	 LCD8 - LED    P01 - 3.3V 

  Note: you must pass four lines of texts (spaces are ok) to the program.  These will then be displayed ont he Nokia 5110 screen.

================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
 */

#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "PCD8544.h"

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;
  
// lcd contrast 
int contrast = 50;
  
int main ( int argc, char *argv[] )
{
    if ( argc <5 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s Line1 Line2 Line3 Line4\n", argv[0] );
        exit(1);
    }
    else 
    {
  
        // check wiringPi setup
        if (wiringPiSetup() == -1)
        {
            printf("wiringPi-Error\n");
            exit(1);
        }
  
          // init and clear lcd
          LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
          delay(150);
          LCDclear();
  
          // show logo
          LCDshowLogo();
  
	  char Line1[14];
	  char Line2[14]; 
	  char Line3[14]; 
	  char Line4[14]; 
	  sprintf(Line1, "%s", "");
	  sprintf(Line2, "%s", "");
	  sprintf(Line3, "%s", "");
	  sprintf(Line4, "%s", "");


          delay(300);
  
	  // clear lcd
       	   LCDclear();
	  
	  sprintf(Line1, "%s", argv[1]);
	  sprintf(Line2, "%s", argv[2]);
	  sprintf(Line3, "%s", argv[3]);
	  sprintf(Line4, "%s", argv[4]);
	  
	  // build screen
	  LCDdrawstring(0, 0, "PRL: GPS");
	  LCDdrawline(0, 10, 83, 10, BLACK);
	  LCDdrawstring(0, 12, Line1);
	  LCDdrawstring(0, 20, Line2);
	  LCDdrawstring(0, 28, Line3);
	  LCDdrawstring(0, 36, Line4);
	  LCDdisplay();
	  
	  delay(1000);
       	  LCDclear();
     }

     return 0;
}
