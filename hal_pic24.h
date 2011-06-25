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

#include <p24fxxxx.h>

#define CS_HIGH()	(LATBbits.LATB0 = 1)
#define CS_LOW()	(LATBbits.LATB0 = 0)

#define RESET_HIGH()	(LATBbits.LATB1 = 1)
#define RESET_LOW()	(LATBbits.LATB1 = 0)

#define WAKE_HIGH()	(LATBbits.LATB2 = 1)
#define WAKE_LOW()	(LATBbits.LATB2 = 0)

#define DELAY_1MS	delay_1ms

void spi_write(unsigned char v);
unsigned char spi_read(void);
void delay_1ms(void);
