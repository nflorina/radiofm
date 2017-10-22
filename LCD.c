/* Name: AtMega8_LCD.c
 * Project: LCD Screen based on AVR USB driver
 * Author: Wkter@live.com
 * Creation Date: 2010-06-22
 */

#define F_CPU 16000000UL	// 12MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include "LCD.h"	// Font and some defines are here

 



// Global variables

int screenX, screenY;	// Used for keeping track of where the next data will be drawn

/*--------------------------------------------------------------------------------------------------
  Name         :  main
  Description  :  Main function
  Argument(s)  :  None
  Return value :  Various
--------------------------------------------------------------------------------------------------*/

// era main-ul aici :))

/*--------------------------------------------------------------------------------------------------
  Name         :  spi_init
  Description  :  Initialising atmega SPI for using with 3310 LCD
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
//SPI initialize
//clock rate: 12Mhz
void spi_init(void){
	
	// Enable SPI with no prescaler (The LCD controller is fast enough for this)
	// See ATMega8 Datasheet page XXX for use
	SPCR = ((0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0));
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_init
  Description  :  LCD controller initialization.
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
// Add startup code here
void LCD_init ( void ){
    
	_delay_ms(100);		// Allow some time to let things settle
	
	CLEAR_SCE_PIN;    	// Enable LCD writing
    
	CLEAR_RST_PIN;		// Reset LCD
    _delay_ms(100);		// Allow the LCD controller some time to reset
    SET_RST_PIN;		// Disable reset
	
	SET_SCE_PIN;		// Disable LCD writing

    LCD_writeCommand( 0x21 );  // LCD Extended Commands.
    LCD_writeCommand( 0xBf );  // Set LCD Vop (Contrast).
    LCD_writeCommand( 0x04 );  // Set Temp coefficent.
    LCD_writeCommand( 0x13 );  // LCD bias mode 1:48.
    LCD_writeCommand( 0x20 );  // LCD Standard Commands, Horizontal addressing mode.
    LCD_writeCommand( 0x0c );  // LCD in normal mode.

    LCD_clear();		// Clear the LCD so it's ready for use
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeCommand
  Description  :  Sends command to display controller.
  Argument(s)  :  command -> command to be sent
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
// There is no reason to mess with this function
void LCD_writeCommand ( unsigned char command ){

	//PORTB = _BV(PB0);	// Enable LED to indicate activity
    CLEAR_SCE_PIN;	  	//enable LCD
	
	CLEAR_DC_PIN;	  	// set LCD in command mode
	
    // Send data to display controller.
    SPDR = command;
	
    // Wait until Tx register empty.
    while(!(SPSR & (1<<SPIF)));

    SET_SCE_PIN;   	 	//disable LCD
	//PORTB &= ~_BV(PB0);
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_writeData
  Description  :  Sends Data to display controller.
  Argument(s)  :  Data -> Data to be sent
  Return value :  None.
--------------------------------------------------------------------------------------------------*/
// There is no reason to mess with this function
void LCD_writeData ( unsigned char Data ){
	
	//PORTB = _BV(PB0);	// Blink LED to indicate activity
    CLEAR_SCE_PIN;	  	// Enable LCD writing
	
	SET_DC_PIN;	  		//set LCD in Data mode
	
    // Send data to display controller.
    SPDR = Data;
	
    // Wait until Tx register empty.
    while ( !(SPSR & 0x80) );
	
	// Every time some data is written to the display, X value increases by 1
	screenX+=1;
	if(screenX>=84){	// If X has reached the end of the screen, continue on Y + 1
		screenX = 0;
		screenY+=1;	
		if(screenY>=6)	// If Y has reached the end of the screen, continue top, Y = 0
			screenY = 0;
	}

    SET_SCE_PIN;   	 		// Disable LCD writing
	//PORTB &= ~_BV(PB0);	// Turn off LED
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_clear
  Description  :  Clears the display
  Argument(s)  :  None.
  Return value :  None.
--------------------------------------------------------------------------------------------------*/

void LCD_clear ( void ){
 
	LCD_gotoXY (0,0);  	//start with (0,0) position

    for(int i=0; i<6; ++i)			//For all pixel banks in height
		for(int j=0; j<84; ++j)	//For all pixels in width
			LCD_writeData( 0x00 );	// Draw a blank pixel
   
    LCD_gotoXY (0,0);	//bring the XY position back to (0,0), just in case.
    
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_gotoXY
  Description  :  Sets cursor location to xy location corresponding to basic font size.
  Argument(s)  :  x - range: 0 to 84
  			   	  y -> range: 0 to 5
  Return value :  None.
--------------------------------------------------------------------------------------------------*/

void LCD_gotoXY ( unsigned char x, unsigned char y ){

	//Send command to display with XY values we want to draw at
    LCD_writeCommand (0x80 | x);   //column
	LCD_writeCommand (0x40 | y);   //row
	
	//Update the global XY variables, so we can keep track of them later
	screenX = x;
	screenY = y;
}

/*--------------------------------------------------------------------------------------------------
  Name         :  LCD_drawChar
  Description  :  Draws a character to display
  Argument(s)  :  ch -> Character to be drawn
  Return value :  None
--------------------------------------------------------------------------------------------------*/
 
void LCD_drawChar ( unsigned char ch ){

	// Newline = 0x0A in hex, if the char we want to draw is this,
	// we call gotoXY and increase Y by 1
	if(ch == 0x0A){
		LCD_gotoXY(0, ++screenY);
		return;	// We don't have anything more to do, return function.
	}
	
	// Sometimes the character we want to draw is too close to the edge of the screen
	// to be draw normally. To prevent the character from being partly drawn over 2 lines
	// we check if we have enough room so draw the character, and if we don't, we simply
	// draw it on the next line instead
	
	if(84-screenX < 5){	// If there are less than 5 pixels left of this ,
						// Count how many pixels this character needs
	
		int width = 0;
		for(int j=0; j<5; j++){
			// Do not count skips
			if(font [(ch-32)*5 + j] == 0b10000000)
				continue;
			width++;
		}
		// If the width of this character is over the amount of pixels left on the X axis
		if(width > 84-screenX)
			LCD_gotoXY(0, ++screenY);	// Goto next line
	}
	// For 5 pixels (Our font maximum width)
	for(int j=0; j<5; j++){
	
		// The first draw-able character we have is space (32 in decimal)
		// Our font do not use the first 32 ASCII characters, so we remove 32 from the character
		// we want to draw, and we get the same character as in out font!
		
		// As some of the characters don't use all 5 pixels, we can make it look nicer by not
		// drawing the empty space. 0b10000000 is the value for not drawing anything in our font, aka "skip"
		if(font [(ch-32)*5 + j] == 0b10000000)
			continue;
		
		// Remove 32 from the character we want to draw, and then draw is.
		LCD_writeData( font [(ch-32)*5 + j] );
	}
	
	//Draw one pixel of spacing between the character and the next one
	LCD_writeData(0x00);
}


void LCD_print (char *s)
{
	for (uint8_t i=0; s[i]!='\0';  i++)
	{
		LCD_drawChar (s[i]);
	}
}