/* Part of LED Matrix Arduino library
 * Copyright (C) 2017 Kane Wallmann
 * See LICENCE.txt for license (MIT)*/

#include <LedMatrix.h>

// Cathode pin array
int cpin[] = { 2,3,4,5,6,7,8,9 };

// Anode pin array
int apin[] = { 14,15,16,17,18,19,20,21 };

LedMatrix matrix( apin, 8, cpin, 8, LED_MATRIX_0DEG );

unsigned long ms;
int position, len;
char* str = "Hello, World!";

void setup()
{
	ms = millis();
	position = 0;
	len = strlen( str );
}

void loop()
{
	// Must be called more frequently than refresh rate (2ms default)
	matrix.ledTask();

	// Evert 150ms scroll the message
	if( millis() - ms > 150 )
	{
		position--;

		// Clear display
		matrix.clear();

		// Cycle through string and draw characters
		for( int a = 0; a < len; a++ )
		{
			char c = str[a];
			matrix.drawBytes( ascii_5x8[c], 5, position + (6*a), 0 );
		}

		// Wrap scrolling
		if( position < -(len*6) )
		{
			position = 9;
		}

		ms = millis();
	}
}
