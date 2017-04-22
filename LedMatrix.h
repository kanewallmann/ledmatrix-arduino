/* Part of LED Matrix Arduino library
 * Copyright (C) 2017 Kane Wallmann
 * See LICENCE.txt for license (MIT)*/

#ifndef __LEDMATRIX_H
#define __LEDMATRIX_H

#include <Arduino.h>
#include <stdbool.h>

#define LED_MATRIX_DEFAULT_DELAY    (2000)         // Default number of micros to pass before moving to next column
#define LED_MATRIX_MAX_COLS            (32)        // Memory for LED state is pre-allocated, this is the max number of cols
#define LED_MATRIX_MAX_ROWS            (32)        // Memory for LED state is pre-allocated, this is the max number fo rows

typedef enum
{
	LED_MATRIX_0DEG,
	LED_MATRIX_90DEG,
	LED_MATRIX_180DEG,
	LED_MATRIX_270DEG
}
		LedMatrixMode;

/**
 * Contains 5x8 English font
 *
 * Example usage:
 *
 * // Draw the letter T at 0,0
 * matrix.DrawBytes( ascii_5x8['T'], 5, 0, 0 );
 */
extern byte ascii_5x8[][5];

/**
 * Helper class for dealing with LED Matrices
 *
 * Example usage:
 *
 * // A 4x4 matrix with pins 1234 as anodes and 5678 as cathodes
 * int apin[] = {1,2,3,4};
 * int cpin[] = {5,6,7,8};
 * LedMatrix led( apin, 4, cpin, 4, LED_MATRIX_0DEG );
 * led.setPixel( 2, 2, true );			// Turn pixel at 2,2 on
 *
 * // Called in program loop
 * led.ledTask();
 */
class LedMatrix
{
public:
	/**
	 * @param apin 			Pointer to array of pins that are the anodes (positive) on the LED matrix
	 * @param apin_count 	Number of anode pins in the above array
	 * @param cpin 			Pointer to array of pins that are the cathodes (negative) on the LED matrix
	 * @param cpin_count 	Number of cathode pins in the above array
	 * @param mode			(Optional) Rotation
	 */
	LedMatrix(int* apin, int apin_count, int* cpin, int cpin_count, LedMatrixMode mode = LED_MATRIX_0DEG);

	/**
	 * Turns all pixels off.
	 */
	void clear();

	/**
	 * Draws an image on the matrix. You can safely call this and point to pixels outside of the visible area. This
	 * method will only try to draw pixels that are within its bounds. This is useful for scrolling text and images.
	 *
	 * @param data 			Pointer to a 2-dimensional array such that data = bool[height][width]
	 * @param x				The x position on the matrix to draw the image
	 * @param y				The y position on the matrix to draw the image
	 * @param width 		The width of the 2-dimensional array
	 * @param height 		The height of the 2-dimensional array
	 */
	void draw(bool* data, int x, int y, int width, int height);

	/**
	 * Sets LEDs on or off depending on the bit values of the supplied byte.
	 *
	 * @param data 			The byte containing 0 for off and 1 for on
	 * @param x 			The horizontal position to start drawing
	 * @param y 			The vertical position to start drawing
	 * @param horizontal 	Draws horizontally when true, else vertically
	 */
	void drawByte(byte data, int x, int y, bool horizontal = false);

	/**
	 * Sets LEDs on or off depending on the bit values of the supplied byte array.
	 *
	 * @param data 			The byte array containing 0 for off and 1 for on
	 * @param x 			The horizontal position to start drawing
	 * @param y 			The vertical position to start drawing
	 * @param horizontal 	Draws the bits horizontally when true, else vertically
	 */
	void drawBytes(byte* data, int count, int x, int y, bool horizontal = false);

	/**
	 * Turns a pixel on or off.
	 *
	 * @param x 			The horizontal position
	 * @param y 			The vertical position
	 * @param state 		On or off
	 */
	void setPixel(int x, int y, bool state);

	/**
	 * Must be called more frequently than LED_MATRIX_FREQUENCY. Performs the actual work on the LED matrix.
	 */
	void ledTask();

	/**
	 * Set the rotation mode of the matrix.
	 *
	 * @param mode 			The rotation mode
	 */
	void setMode(LedMatrixMode mode);

	/**
	 * Sets the frequency this matrix scans at.
	 *
	 * @param micro			The number of microseconds to keep each LED on
	 */
	void setDelay(unsigned long micros);

private:
	/**
	 * Pointer to array of anode pins.
	 */
	int* apin;

	/**
	 * Points to array of cathode pins.
	 */
	int* cpin;

	/**
	 * Length of anode array.
	 */
	int apin_count;

	/**
	 * Length of cathod array.
	 */
	int cpin_count;

	/**
	 * Rotation mode for this matrix.
	 */
	LedMatrixMode mode;

	/**
	 * A 2-dimensional array of booleans indicating the state of each LED.
	 */
	bool state[LED_MATRIX_MAX_COLS][LED_MATRIX_MAX_ROWS];

	/**
	 * Keeps track of time passed for frequency calculation.
	 */
	unsigned long timer;

	/**
	 * The frequency this matrix is scanning at. In milliseconds.
	 */
	unsigned long delay;

	/**
	 * The current column we are up to in the scanning process.
	 */
	int current_col;
};

#endif //MATRIX_LEDMATRIX_H
