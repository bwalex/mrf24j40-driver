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

#include "hal_pic18.h"
#include "MRF24J40.h"
#include "ieee802154.h"

static unsigned char seq_no = 0;

static unsigned char SPI_READ_LONG(int addr)
{
	unsigned char a_msb, a_lsb, d;

	a_msb = a_lsb = 0;
	a_msb = (((addr >> 3) & 0x7F) | 0x80);
	a_lsb = (((addr & 0x07) << 5));

	CS_LOW();
	spi_write(a_msb);
	spi_write(a_lsb);
	d = spi_read();
	CS_HIGH();

	return d;
}

static unsigned char SPI_READ_SHORT(unsigned char addr)
{
	unsigned char d;

	addr &= 0x3f;	/* Trim address to 6 bits */
	addr <<= 1;		/* Shift into the right position */
	addr &= ~0x01;	/* Clear write bit */

	CS_LOW();
	spi_write(addr);
	d = spi_read();
	CS_HIGH();

	return d;
}

static void SPI_WRITE_LONG(int addr, unsigned char d)
{
	unsigned char a_msb, a_lsb;

	a_msb = a_lsb = 0;
	a_msb = (((addr >> 3) & 0x7F) | 0x80);
	a_lsb = (((addr & 0x07) << 5) | (1<<4));

	CS_LOW();
	spi_write(a_msb);
	spi_write(a_lsb);
	spi_write(d);
	CS_HIGH();
}

static void SPI_WRITE_SHORT(unsigned char addr, unsigned char d)
{
	addr &= 0x3f;	/* Trim address to 6 bits */
	addr <<= 1;		/* Shift into the right position */
	addr |= 0x01;	/* Set R/W bit to write */

	CS_LOW();
	spi_write(addr);
	spi_write(d);
	CS_HIGH();
}

static void SPI_WRITE_FIFO(int addr, unsigned char *d, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		SPI_WRITE_LONG(addr++, d[i]);
	}
}

static void SPI_READ_FIFO(int addr, unsigned char *d, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		d[i] = SPI_READ_LONG(addr++);
	}
}

void mrf24j40_ie(void)
{
	/*
	 * Very intuitively IE (interrupt enable) set to 1
	 * causes the interrupt to be disabled...
	 */
	SPI_WRITE_SHORT(INTCON, ~(TXNIE | RXIE | SECIE));
}

void mrf24j40_pwr_reset(void)
{
	SPI_WRITE_SHORT(SOFTRST, RSTPWR);
}

void mrf24j40_bb_reset(void)
{
	SPI_WRITE_SHORT(SOFTRST, RSTBB);
}

void mrf24j40_mac_reset(void)
{
	/* NOTE: All control registers are reset by this! */
	SPI_WRITE_SHORT(SOFTRST, RSTMAC);
}

void mrf24j40_rf_reset(void)
{
	unsigned char old = SPI_READ_SHORT(RFCTL);

	SPI_WRITE_SHORT(RFCTL, old | RFRST);
	SPI_WRITE_SHORT(RFCTL, old & ~RFRST);
	DELAY_1MS();	/* Delay min 192us */
}

void mrf24j40_set_channel(int ch)
{
	/* translate channel */
	/* 0x00 -> Ch 11 */
	/* 0x01 -> Ch 12 */
	/* 0x0F -> Ch 26 */
	if (ch >= 11)
		ch -= 11;

	SPI_WRITE_LONG(RFCON0, CHANNEL(ch) | RFOPT(0x03));
	mrf24j40_rf_reset();
}

unsigned char mrf24j40_read_channel(void)
{
	return (11 + (SPI_READ_LONG(RFCON0) >> 4));
}

void mrf24j40_set_promiscuous(int crc_check)
{
	unsigned char w;

	/*
	 * Set promiscuous mode, disable auto-ACK and, if requested,
	 * accept packets with a CRC error.
	 */
	w = NOACKRSP;
	if (!crc_check)
		w |= ERRPKT;
	else
		w |= PROMI;

	SPI_WRITE_SHORT(RXMCR, w);
}

void mrf24j40_set_pan(int pan)
{
	SPI_WRITE_SHORT(PANIDH, pan>>8);
	SPI_WRITE_SHORT(PANIDL, pan & 0xFF);
}

void mrf24j40_set_short_addr(int addr)
{
	SPI_WRITE_SHORT(SADRH, addr>>8);
	SPI_WRITE_SHORT(SADRL, addr & 0xFF);
}

void mrf24j40_init(int ch)
{
	RESET_LOW();
	DELAY_1MS();
	RESET_HIGH();
	DELAY_1MS();
	SPI_WRITE_SHORT(SOFTRST, (RSTPWR | RSTBB | RSTMAC));
	while ((SPI_READ_SHORT(SOFTRST) & (RSTPWR | RSTBB | RSTMAC)) != 0);
	DELAY_1MS();

	SPI_WRITE_SHORT(PACON2, SPI_READ_SHORT(PACON2) | FIFOEN);
	SPI_WRITE_SHORT(TXSTBL, RFSTBL(9) | MSIFS(5));
	SPI_WRITE_LONG(RFCON0, CHANNEL(ch) | RFOPT(0x03));
	SPI_WRITE_LONG(RFCON1, VCOOPT(0x02));
	SPI_WRITE_LONG(RFCON2, PLLEN);
	SPI_WRITE_LONG(RFCON6, TXFIL);
	SPI_WRITE_LONG(RFCON7, SLPCLKSEL(0x02));
	SPI_WRITE_LONG(RFCON8, RFVCO);
	SPI_WRITE_LONG(SLPCON0, INTEDGE);	/* Set Rising Edge Interrupt Edge Polarity */
	SPI_WRITE_LONG(SLPCON1, SLPCLKDIV(1) | CLKOUTDIS);

	SPI_WRITE_SHORT(BBREG2, CCAMODE(0x03) | CCASTH(0x02));
	SPI_WRITE_SHORT(CCAEDTH, 0x60);

	/* Flush RX FIFO */
	SPI_WRITE_SHORT(RXFLUSH, _RXFLUSH);

	/* Enable interrupts */
	mrf24j40_ie();

	mrf24j40_rf_reset();
}

void mrf24j40_txpkt(unsigned short dest, unsigned char *pkt, int len)
{
	struct ieee802_15_4_MAChdr	pkt_header;
	int hlen = 0;
	int flen = 0;
	int addr = TXNFIFO;
	int i;

	flen += sizeof(pkt_header);
	//flen += 11;
	flen += len;

	SPI_WRITE_SHORT(TXNCON, SPI_READ_SHORT(TXNCON) & TXNACKREQ);

	pkt_header.dest_addr = (dest << 8) | (dest >> 8);
	pkt_header.src_addr = ((short)SPI_READ_SHORT(SADRH) << 8) | SPI_READ_SHORT(SADRL);
	pkt_header.dest_pan = ((short)SPI_READ_SHORT(PANIDH) << 8) | SPI_READ_SHORT(PANIDL);
	pkt_header.seq_no = seq_no++;
	pkt_header.fc_low = FCFRTYP(FCFRTYP_DATA) | /*FCREQACK | */FCPANCOMP;
	pkt_header.fc_high = FCDADDRM(FCADDR_SHORT) | FCFRVER(0) | FCSADDRM(FCADDR_SHORT);

	SPI_WRITE_LONG(addr++, hlen);
	SPI_WRITE_LONG(addr++, flen);

	for (i = 0; i < sizeof(pkt_header); i++) {
		SPI_WRITE_LONG(addr++, ((unsigned char *)&pkt_header)[i]);
	}

	for (i = 0; i < len; i++) {
		SPI_WRITE_LONG(addr++, pkt[i]);
	}

	SPI_WRITE_SHORT(TXNCON, SPI_READ_SHORT(TXNCON) | TXNTRIG);
}

int mrf24j40_txpkt_intcb(void)
{
	unsigned char stat = SPI_READ_SHORT(TXSTAT);
	if (stat & TXNSTAT) {
		if (stat & CCAFAIL)
			return EBUSY;
		else
			return EIO;
	} else {
		return 0;
	}
}

int mrf24j40_rxpkt_intcb(unsigned char *d, int len, unsigned char *plqi, unsigned char *prssi)
{
	int flen, i;
	int addr = RXFIFO;
	unsigned char lqi, rssi;

	/* Disable receiving more packets */
	SPI_WRITE_SHORT(BBREG1, SPI_READ_SHORT(BBREG1) | RXDECINV);

	flen = SPI_READ_LONG(addr++);
	if (flen > len) {
		/* Re-enable packet reception */
		SPI_WRITE_SHORT(BBREG1, SPI_READ_SHORT(BBREG1) & ~RXDECINV);
		return ENOMEM;
	}

	d[0] = flen;
	for (i = 1; i <= flen; i++) {
		d[i] = SPI_READ_LONG(addr++);
	}

	lqi = SPI_READ_LONG(addr++);
	rssi = SPI_READ_LONG(addr++);

	if (plqi != (void *)0)
		*plqi = lqi;

	if (prssi != (void *)0)
		*prssi = rssi;

	/* Flush RX FIFO */
	SPI_WRITE_SHORT(RXFLUSH, _RXFLUSH);

	/* Re-enable packet reception */
	SPI_WRITE_SHORT(BBREG1, SPI_READ_SHORT(BBREG1) & ~RXDECINV);
	return 0;
}

int mrf24j40_rxpkt_part_intcb(unsigned char *d, int len, int flags, unsigned char *plqi, unsigned char *prssi)
{
	int i;
	static int flen;
	static int addr;
	unsigned char lqi, rssi;

	/* Abort; flush and re-enable reception */
	if (flags & MRF24J40_PART_RX_ABORT) {
		/* Flush RX FIFO */
		SPI_WRITE_SHORT(RXFLUSH, _RXFLUSH);

		/* Re-enable packet reception */
		SPI_WRITE_SHORT(BBREG1, SPI_READ_SHORT(BBREG1) & ~RXDECINV);
		return -1;
	}

	if (flags & MRF24J40_PART_RX_FIRST) {
		/* Disable receiving more packets */
		SPI_WRITE_SHORT(BBREG1, SPI_READ_SHORT(BBREG1) | RXDECINV);

		addr = RXFIFO;
		flen = SPI_READ_LONG(addr++);

		/* Account for frame len */
		--len;
		*d++ = flen;
	}

	if (flen < len)
		len = flen;

	for (i = 0; i < len; i++) {
		d[i] = SPI_READ_LONG(addr++);
	}

	/* Adjust remaining frame length */
	flen -= len;

	if (flen == 0) {
		lqi = SPI_READ_LONG(addr++);
		rssi = SPI_READ_LONG(addr++);

		if (plqi != (void *)0)
			*plqi = lqi;

		if (prssi != (void *)0)
			*prssi = rssi;

		/* Flush RX FIFO */
		SPI_WRITE_SHORT(RXFLUSH, _RXFLUSH);

		/* Re-enable packet reception */
		SPI_WRITE_SHORT(BBREG1, SPI_READ_SHORT(BBREG1) & ~RXDECINV);
	}

	return flen;
}

int mrf24j40_int_tasks(void) {
	unsigned char stat;
	int ret = 0;

	stat = SPI_READ_SHORT(INTSTAT);

	if (stat & RXIF) {
		ret |= MRF24J40_INT_RX;
	}

	if (stat & TXNIF) {
		ret |= MRF24J40_INT_TX;
	}

	if (stat & SECIF) {
		ret |= MRF24J40_INT_SEC;
	}

	return ret;
}
