
#define SET_DC_PIN                 PORTB |= _BV(PB2)  
#define CLEAR_DC_PIN               PORTB &= ~_BV(PB2)
#define SET_SCE_PIN                PORTB |= _BV(PB0)  
#define CLEAR_SCE_PIN              PORTB &= ~_BV(PB0)
#define SET_RST_PIN                PORTB |= _BV(PB1)
#define CLEAR_RST_PIN              PORTB &= ~_BV(PB1) //Was same as set pin
  
// Function prototypes

void spi_init ( void );									// Initilize SPI interface
void LCD_init ( void );									// Initilize the LCD display
void LCD_clear ( void );								// Clear the Lcd display
void LCD_gotoXY ( unsigned char x, unsigned char y );	// Tell the LCD controller where to write
void LCD_writeData ( unsigned char data );				// Write pixels to screen
void LCD_writeCommand ( unsigned char command );		//Send a command to the LCD controller
void LCD_drawChar ( unsigned char ch );					// Draw a character to the screen
void LCD_print (char *);

// This is the font we use with the function LCD_drawChar.
// Each character has 5 pixels avaliable in width, but it doesn't have to use all 5.
//
// If a character uses less than 5 pixels in width, fill the unused pixeles with 0b10000000.
// This is the value for "skip", and simply draws nothing (Not even a blank space, 
// if you want a blank space, use 0b00000000).
//
// A blank space is automatically added in between each character, so don't include any character spacing
// in the font. 










































static const unsigned char font[] = {
// -1-			-2-			-3-			-4-			-5-
0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b10000000, //*SPACE*
0b01011100, 0b10000000, 0b10000000, 0b10000000, 0b10000000, //!
0b00001100, 0b00000000, 0b00001100, 0b10000000, 0b10000000, //"
0b00101000, 0b01111100, 0b00101000, 0b01111100, 0b00101000, //#
0b01010000, 0b01011000, 0b11101100, 0b00101000, 0b10000000, //$
0b00000100, 0b01100000, 0b00010000, 0b00001100, 0b01000000, //%
0b00101000, 0b01010100, 0b01010100, 0b00100000, 0b01010000, //&
0b00001100, 0b10000000, 0b10000000, 0b10000000, 0b10000000, //'
0b00111000, 0b01000100, 0b10000000, 0b10000000, 0b10000000, //(
0b01000100, 0b00111000, 0b10000000, 0b10000000, 0b10000000, //)
0b00010100, 0b00001000, 0b00010100, 0b10000000, 0b10000000, //*
0b00010000, 0b00111000, 0b00010000, 0b10000000, 0b10000000, //+
0b11000000, 0b01000000, 0b10000000, 0b10000000, 0b10000000, //,
0b00010000, 0b00010000, 0b00010000, 0b10000000, 0b10000000, //-
0b01000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, //.
0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, ///
0b00111000, 0b01000100, 0b01000100, 0b00111000, 0b10000000, //0
0b00000100, 0b01111100, 0b10000000, 0b10000000, 0b10000000, //1
0b01100100, 0b01010100, 0b01010100, 0b01001000, 0b10000000, //2
0b01000100, 0b01010100, 0b01010100, 0b00101000, 0b10000000, //3
0b00110000, 0b00101000, 0b01111100, 0b00100000, 0b10000000, //4
0b01011100, 0b01010100, 0b01010100, 0b00100100, 0b10000000, //5
0b00111000, 0b01010100, 0b01010100, 0b00100000, 0b10000000, //6
0b00000100, 0b01100100, 0b00010100, 0b00001100, 0b10000000, //7
0b00101000, 0b01010100, 0b01010100, 0b00101000, 0b10000000, //8
0b00001000, 0b01010100, 0b01010100, 0b00111000, 0b10000000, //9
0b00101000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, //:
0b01101000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, //;
0b00010000, 0b00101000, 0b01000100, 0b10000000, 0b10000000, //<
0b00101000, 0b00101000, 0b00101000, 0b10000000, 0b10000000, //=
0b01000100, 0b00101000, 0b00010000, 0b10000000, 0b10000000, //>
0b00000100, 0b01010100, 0b00010100, 0b00001000, 0b10000000, //?
0b00111000, 0b01000100, 0b01110100, 0b01010100, 0b00111000, //@
0b01111000, 0b00100100, 0b00100100, 0b01111000, 0b10000000, //A
0b01111100, 0b01010100, 0b01010100, 0b00101000, 0b10000000, //B
0b00111000, 0b01000100, 0b01000100, 0b10000000, 0b10000000, //C
0b01111100, 0b01000100, 0b01000100, 0b00111000, 0b10000000, //D
0b01111100, 0b01010100, 0b01010100, 0b01000100, 0b10000000, //E
0b01111100, 0b00010100, 0b00010100, 0b00000100, 0b10000000, //F
0b00111000, 0b01000100, 0b01010100, 0b01110100, 0b10000000, //G
0b01111100, 0b00010000, 0b00010000, 0b01111100, 0b10000000, //H
0b01000100, 0b01111100, 0b01000100, 0b10000000, 0b10000000, //I
0b00100000, 0b01000000, 0b01000100, 0b00111100, 0b10000000, //J
0b01111100, 0b00010000, 0b00101000, 0b01000100, 0b10000000, //K
0b01111100, 0b01000000, 0b01000000, 0b10000000, 0b10000000, //L
0b01111100, 0b00001000, 0b00010000, 0b00001000, 0b01111100, //M
0b01111100, 0b00001000, 0b00010000, 0b01111100, 0b10000000, //N
0b00111000, 0b01000100, 0b01000100, 0b00111000, 0b10000000, //O
0b01111100, 0b00100100, 0b00100100, 0b00011000, 0b10000000, //P
0b00111000, 0b01000100, 0b01000100, 0b10111000, 0b10000000, //Q
0b01111100, 0b00100100, 0b00100100, 0b01011000, 0b10000000, //R
0b01001000, 0b01010100, 0b01010100, 0b00100100, 0b10000000, //S
0b00000100, 0b01111100, 0b00000100, 0b10000000, 0b10000000, //T
0b00111100, 0b01000000, 0b01000000, 0b00111100, 0b10000000, //U
0b00111100, 0b01000000, 0b00110000, 0b00001100, 0b10000000, //V
0b00111100, 0b01000000, 0b00111000, 0b01000000, 0b00111100, //W
0b01101100, 0b00010000, 0b00010000, 0b01101100, 0b10000000, //X
0b00001100, 0b01010000, 0b01010000, 0b00111100, 0b10000000, //Y
0b01100100, 0b01010100, 0b01001100, 0b10000000, 0b10000000, //Z
0b01111100, 0b01000100, 0b10000000, 0b10000000, 0b10000000, // [
0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, /* \ */
0b01000100, 0b01111100, 0b10000000, 0b10000000, 0b10000000, // ]
0b00001000, 0b00000100, 0b00001000, 0b10000000, 0b10000000, // ^
0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b10000000, // _
0b00000100, 0b00001000, 0b10000000, 0b10000000, 0b10000000, // `
0b00110000, 0b01001000, 0b01001000, 0b01111000, 0b10000000, // a
0b01111100, 0b01001000, 0b01001000, 0b00110000, 0b10000000, // b
0b00110000, 0b01001000, 0b01001000, 0b10000000, 0b10000000, // c
0b00110000, 0b01001000, 0b01001000, 0b01111100, 0b10000000, // d
0b00110000, 0b01101000, 0b01011000, 0b00010000, 0b10000000, // e
0b00010000, 0b01111000, 0b00010100, 0b10000000, 0b10000000, // f
0b00011000, 0b10100100, 0b10100100, 0b01111100, 0b10000000, // g
0b01111100, 0b00001000, 0b00001000, 0b01110000, 0b10000000, // h
0b01110100, 0b10000000, 0b10000000, 0b10000000, 0b10000000, // i
0b01000000, 0b00110100, 0b10000000, 0b10000000, 0b10000000, // j
0b01111100, 0b00100000, 0b00110000, 0b01000100, 0b10000000, // k
0b01111100, 0b10000000, 0b10000000, 0b10000000, 0b10000000, // l
0b01111000, 0b00001000, 0b01111000, 0b00001000, 0b01110000, // m
0b01111000, 0b00001000, 0b00001000, 0b01110000, 0b10000000, // n
0b00110000, 0b01001000, 0b01001000, 0b00110000, 0b10000000, // o
0b11111000, 0b01001000, 0b01001000, 0b00110000, 0b10000000, // p
0b00110000, 0b01001000, 0b01001000, 0b11111000, 0b10000000, // q
0b01111000, 0b00010000, 0b00001000, 0b10000000, 0b10000000, // r
0b01010000, 0b01011000, 0b01101000, 0b00101000, 0b10000000, // s
0b00001000, 0b00111100, 0b01001000, 0b10000000, 0b10000000, // t
0b00111000, 0b01000000, 0b01000000, 0b01111000, 0b10000000, // u
0b00111000, 0b01000000, 0b00100000, 0b00011000, 0b10000000, // v
0b00011000, 0b01100000, 0b00011000, 0b01100000, 0b00011000, // w
0b01001000, 0b00110000, 0b01001000, 0b10000000, 0b10000000, // x
0b00011000, 0b10100000, 0b10100000, 0b01111000, 0b10000000, // y
0b01001000, 0b01101000, 0b01011000, 0b01001000, 0b10000000, // z
0b00010000, 0b01101100, 0b01000100, 0b10000000, 0b10000000, // {
0b01111110, 0b10000000, 0b10000000, 0b10000000, 0b10000000, // |
0b01000100, 0b01101100, 0b00010000, 0b10000000, 0b10000000, // }
0b00001000, 0b00000100, 0b00001000, 0b00000100, 0b10000000  // ~
};