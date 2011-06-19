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

/* Return values */
#define MRF24J40_INT_RX		0x01
#define MRF24J40_INT_TX		0x02
#define MRF24J40_INT_SEC	0x04

#define EIO			5
#define ENOMEM			12
#define EBUSY			16

/* Short Address Control Register Map */
#define RXMCR		0x00
#define PANIDL		0x01
#define PANIDH		0x02
#define	SADRL		0x03
#define SADRH		0x04
#define EADR0		0x05
#define EADR1		0x06
#define EADR2		0x07
#define EADR3		0x08
#define EADR4		0x09
#define EADR5		0x0A
#define EADR6		0x0B
#define EADR7		0x0C
#define RXFLUSH		0x0D

#define ORDER		0x10
#define TXMCR		0x11
#define ACKTMOUT	0x12
#define ESLOTG1		0x13
#define SYMTICKL	0x14
#define SYMTICKH	0x15
#define PACON0		0x16
#define PACON1		0x17
#define PACON2		0x18
#define TXBCON0		0x1A
#define TXNCON		0x1B
#define TXG1CON		0x1C
#define TXG2CON		0x1D
#define ESLOTG23	0x1E
#define ESLOTG45	0x1F

#define ESLOTG67	0x20
#define TXPEND		0x21
#define WAKECON		0x22
#define FRMOFFSET	0x23
#define TXSTAT		0x24
#define TXBCON1		0x25
#define GATECLK		0x26
#define TXTIME		0x27
#define HSYMTMRL	0x28
#define HSYMTMRH	0x29
#define SOFTRST		0x2A
#define SECCON0		0x2c
#define SECCON1		0x2d
#define TXSTBL		0x2e

#define RXSR		0x30
#define INTSTAT		0x31
#define INTCON		0x32
#define GPIO		0x33
#define TRISGPIO	0x34
#define SLPACK		0x35
#define RFCTL		0x36
#define SECCR2		0x37
#define BBREG0		0x38
#define BBREG1		0x39
#define BBREG2		0x3A
#define BBREG3		0x3B
#define BBREG4		0x3C
#define BBREG6		0x3E
#define CCAEDTH		0x3F

/* Long Address Control Register Map */
#define RFCON0		0x200
#define RFCON1		0x201
#define RFCON2		0x202
#define RFCON3		0x203
#define RFCON5		0x205
#define RFCON6		0x206
#define RFCON7		0x207
#define RFCON8		0x208
#define RFSTATE		0x20F

#define RSSI		0x210
#define SLPCON0		0x211
#define SLPCON1		0x220

#define MAINCNT0	0x226
#define MAINCNT1	0x227
#define MAINCNT2	0x228
#define MAINCNT3	0x229

#define UPNONCE0	0x240
#define UPNONCE1	0x241
#define UPNONCE2	0x242
#define UPNONCE3	0x243
#define UPNONCE4	0x244
#define UPNONCE5	0x245
#define UPNONCE6	0x246
#define UPNONCE7	0x247
#define UPNONCE8	0x248
#define UPNONCE9	0x249
#define UPNONCE10	0x24A
#define UPNONCE11	0x24B
#define UPNONCE12	0x24C

/* Long Address Memory Map */
#define TXNFIFO		0x000 /* - 0x07F, 128 bytes */
#define TXBFIFO		0x080 /* - 0x0FF, 128 bytes */
#define TXG1FIFO	0x100 /* - 0x17F, 128 bytes */
#define TXG2FIFO	0x180 /* - 0x1FF, 128 bytes */
#define SECKFIFO	0x280 /* - 0x2BF, 64 bytes */
#define RXFIFO		0x300 /* - 0x38F, 128 bytes */


/* RXMCR */
#define NOACKRSP	(1<<5)
#define PANCOORD	(1<<3)
#define COORD		(1<<2)
#define ERRPKT		(1<<1)
#define PROMI		(1)

/* RXFLUSH */
#define WAKEPOL		(1<<6)
#define WAKEPAD		(1<<5)
#define CMDONLY		(1<<3)
#define DATAONLY	(1<<2)
#define BCNONLY		(1<<1)
#define _RXFLUSH	(1)

/* TXMCR */
#define NOCSMA		(1<<7)
#define BATLIFEXT	(1<<6)
#define SLOTTED		(1<<5)
#define MACMINBE(x)	((x & 0x03)<<3)
#define CSMABF(x)	(x & 0x07)

/* ACKTMOUT */
#define DRPACK		(1<<7)

/* PACON2 */
#define FIFOEN		(1<<7)

/* TXNCON */
#define FPSTAT		(1<<4)
#define INDIRECT	(1<<3)
#define TXNACKREQ	(1<<2)
#define TXNSECEN	(1<<1)
#define TXNTRIG		(1)

/* TXPEND */
#define FPACK		(1)

/* WAKECON */
#define IMMWAKE		(1<<7)
#define REGWAKE		(1<<6)

/* TXSTAT */
#define CCAFAIL		(1<<5)
#define TXNSTAT		(1)

/* SOFTRST */
#define RSTPWR		(1<<2)
#define RSTBB		(1<<1)
#define RSTMAC		(1)

/* SECCON0 */
#define SECIGNORE	(1<<7)
#define SECSTART	(1<<6)
#define RXCIPHER(x)	((x & 0x07) << 3)
#define TXNCIPHER(x)	((x & 0x07))

/* SECCON1 */
#define DISDEC		(1<<1)
#define DISENC		(1)

/* TXSTBL */
#define RFSTBL(x)	((x & 0x0f) << 4)
#define MSIFS(x)	((x & 0x0f))

/* RXSR */
#define UPSECERR	(1<<6)
#define SECDECERR	(1<<2)


/* INTSTAT */
#define SLPIF		(1<<7)
#define WAKEIF		(1<<6)
#define HSYMTMRIF	(1<<5)
#define SECIF		(1<<4)
#define RXIF		(1<<3)
#define TXG2IF		(1<<2)
#define TXG1IF		(1<<1)
#define TXNIF		(1)

/* INTCON */
#define SLPIE		(1<<7)
#define WAKEIE		(1<<6)
#define HSYMTMRIE	(1<<5)
#define SECIE		(1<<4)
#define RXIE		(1<<3)
#define TXG2IE		(1<<2)
#define TXG1IE		(1<<1)
#define TXNIE		(1)

/* SLPACK */
#define _SLPACK		(1<<7)

/* RFCTL */
#define WAKECNT(x)	((x & 0x03) << 3)
#define RFRST		(1<<2)
#define RFTXMODE	(1<<1)
#define RFRXMODE	(1)

/* SECCR2 */
#define UPDEC		(1<<7)
#define UPENC		(1<<6)

/* BBREG0 */
#define TURBO		(1)

/* BBREG1 */
#define RXDECINV	(1<<2)

/* BBREG2 */
#define CCAMODE(x)	((x & 0x03) <<6)
#define CCASTH(x)	((x & 0x0F) <<2)

/* BBREG3 */
#define PREVALIDTH(x)	((x & 0x0F) <<4)

/* BBREG4 */
#define CSTH(x)		((x & 0x07) << 5)

/* BBREG6 */
#define RSSIMODE1	(1 << 7)
#define RSSIMODE2	(1<<6)
#define RSSIRDY		(1)

/* RFCON0 */
#define CHANNEL(x)	((x & 0x0F) << 4)
#define RFOPT(x)	((x & 0x0F))

/* RFCON1 */
#define VCOOPT(x)	((x & 0xFF))

/* RFCON2 */
#define PLLEN		(1<<7)

/* RFCON3 */
#define TXPWRL(x)	((x & 0x03) << 6)
#define TXPWRS(x)	((x & 0x07) << 3)

/* RFCON6 */
#define TXFIL		(1 << 7)

/* RFCON 7 */
#define SLPCLKSEL(x)	((x & 0x03) << 6)

/* RFCON8 */
#define RFVCO		(1 << 4)

/* SLPCON0 */
#define INTEDGE		(1<<1)
#define SLPCLKEN	(1)

/* SLPCON1 */
#define CLKOUTDIS	(1 << 5)	/* CLKOUTEN' */
#define SLPCLKDIV(x)	((x & 0x1F))


/* Partial reception flags */
#define MRF24J40_PART_RX_ABORT	(1 << 1)
#define MRF24J40_PART_RX_FIRST	(1)

void mrf24j40_init(int ch);
void mrf24j40_set_short_addr(int addr);
void mrf24j40_set_pan(int pan);
void mrf24j40_set_channel(int ch);
void mrf24j40_set_promiscuous(int crc_check);
void mrf24j40_txpkt(unsigned short dest, unsigned char *pkt, int len);
unsigned char mrf24j40_read_channel(void);
int mrf24j40_int_tasks(void);
int mrf24j40_rxpkt_intcb(unsigned char *d, int len, unsigned char *plqi,
    unsigned char *prssi);
int mrf24j40_rxpkt_part_intcb(unsigned char *d, int len, int flags,
	unsigned char *plqi, unsigned char *prssi);
int mrf24j40_txpkt_intcb(void);


/*
Some info about the (likely) content of the "reserved" registers:
-----------------------------------------------------------------

Bit 7-3 PEAKLATE[4:0]: Upper boundary of preamble searching time
00000: (optimized - Do Not Change)
01111: (default)
Bit 2-0 PEAKEARLY[2:0]: Lower boundary of preamble searching time
011: (default)
111: (optimized - Do Not Change)
0x3D BBREG5 PEAKLATE4 PEAKLATE3 PEAKLATE2 PEAKLATE1 PEAKLATE0 PEAKEARLY2 PEAKEARLY1 PEAKEARLY0



Bit 7-3 RXFC1[4:0]: RX Filter Control 1
00000: (default - Do Not Change)
Bit 2 RXFCO: RX Filter Calibration Output
0: (default)
1: (optimized - Do Not Change)
Bit 1-0 RXD2O[1:0]: RX Divide-by-2 Option
00: (default)
11: (optimized - Do Not Change)
0x204 RFCTRL4 RXFBW4 RXFBW3 RXFBW2 RXFBW1 RXFBW0 RXFCO RXD2O1 RXD2O0 0000 0000



SADRMODE[1:0]: Source Address Mode
00: Reserved (default)
01: Reserved
10: 16-bit short address
11: 64-bit extended address
0x212 SADRCTRL r r r r r r SADRMODE1 SADRMODE0 0000 0000



Received packet source address:
0x213 SRCADR_0 SRCADR7 SRCADR6 SRCADR5 SRCADR4 SRCADR3 SRCADR2 SRCADR1 SRCADR0 0000 0000
0x214 SRCADR_1 SRCADR15 SRCADR14 SRCADR13 SRCADR12 SRCADR11 SRCADR10 SRCADR9 SRCADR8 0000 0000
0x215 SRCADR_2 SRCADR23 SRCADR22 SRCADR21 SRCADR20 SRCADR19 SRCADR18 SRCADR17 SRCADR16 0000 0000
0x216 SRCADR_3 SRCADR31 SRCADR30 SRCADR29 SRCADR28 SRCADR27 SRCADR26 SRCADR25 SRCADR24 0000 0000
0x217 SRCADR_4 SRCADR39 SRCADR38 SRCADR37 SRCADR36 SRCADR35 SRCADR34 SRCADR33 SRCADR32 0000 0000
0x218 SRCADR_5 SRCADR47 SRCADR46 SRCADR45 SRCADR44 SRCADR43 SRCADR42 SRCADR41 SRCADR40 0000 0000
0x219 SRCADR_6 SRCADR55 SRCADR54 SRCADR53 SRCADR52 SRCADR51 SRCADR50 SRCADR49 SRCADR48 0000 0000
0x21A SRCADR_7 SRCADR63 SRCADR62 SRCADR61 SRCADR60 SRCADR59 SRCADR58 SRCADR57 SRCADR56 0000 0000


*/

