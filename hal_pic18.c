/* 
 * Copyright (C) 2011, Alex Hornung  
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */

#include <p18cxxx.h>
#include <delays.h>

void spi_write(unsigned char v)
{
	unsigned char i;

	PIR1bits.SSPIF = 0;
	i = SSPBUF;
	do
	{
		SSPCON1bits.WCOL = 0;
		SSPBUF = v;
	} while( SSPCON1bits.WCOL );

	while( PIR1bits.SSPIF == 0 );
}

unsigned char spi_read(void)
{
	spi_write(0x00);
	return SSPBUF;
}

void delay_1ms(void)
{
	/* Not really a ms, but doesn't matter. */
	Delay1KTCYx(1);
}
