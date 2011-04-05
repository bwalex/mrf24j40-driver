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

struct ieee802_15_4_MAChdr {
	unsigned char fc_low;
	unsigned char fc_high;
	unsigned char seq_no;
	unsigned short dest_pan;
	unsigned short dest_addr;
	unsigned short src_addr;
};

/* Frame type */
#define FCFRTYP_BEACON	0x00
#define FCFRTYP_DATA	0x01
#define FCFRTYP_ACK		0x02
#define FCFRTYP_MCMD	0x03

/* Addressing mode */
#define FCADDR_NONE		0x00
#define FCADDR_SHORT	0x02
#define FCADDR_EXT		0x03

/* Frame Control Low bits */
#define FCFRTYP(x)	((x & 0x07)) /* Bit 0 - 2 */
#define FCSECEN		(1 << 3)			/* Bit 3 */
#define FCFRPEN		(1 << 4)			/* Bit 4 */
#define FCREQACK	(1 << 5)			/* Bit 5 */
#define FCPANCOMP	(1 << 6) /* Yes! srcpan = destpan */ /* Bit 6 */

/* Frame Control High bits */
#define FCDADDRM(x)	((x & 0x03) << 2)	/* Bit 10-11 */
#define FCFRVER(x)	((x & 0x03) << 4)	/* Bit 12-13 */
#define FCSADDRM(x) ((x & 0x03) << 6)	/* Bit 14-15 */

/* http://www.libelium.com/development/articles/091811814228 */
