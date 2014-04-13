/*
 * Author: Minux
 * Author: Xiangfu Liu <xiangfu@openmobilefree.net>
 * Bitcoin:	1CanaaniJzgps8EV6Sfmpb7T8RutpaeyFn
 *
 * This is free and unencumbered software released into the public domain.
 * For details see the UNLICENSE file at the root of the source tree.
 */

//#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "system_config.h"
#include "miner.h"
#include "sha256.h"
#include "protocol.h"
#include "crc.h"

#define adjust_fan(value)	write_pwm(value)

struct mm_work mm_work;
struct result result;

static uint8_t g_pkg[AVA2_P_COUNT];
static uint8_t g_act[AVA2_P_COUNT];
static int new_stratum = 0;

void delay(unsigned int ms)
{
	unsigned int i;

	while (ms--) {
            SpinDelay((uint16_t)1000); // 1000 uSec = 1 milli Sec
	}
}

static void error(uint8_t n)
{
	uint8_t i = 0;

	while (i < 8) {
            delay(1000);
            i++;
	}
}

static void encode_pkg(uint8_t *p, int type, uint8_t *buf, unsigned int len)
{
	uint16_t crc;

	memset(p, 0, AVA2_P_COUNT);

	p[0] = AVA2_H1;
	p[1] = AVA2_H2;
	p[AVA2_P_COUNT - 2] = AVA2_T1;
	p[AVA2_P_COUNT - 1] = AVA2_T2;

	p[2] = type;
	p[3] = 1;
	p[4] = 1;

	switch(type) {
	case AVA2_P_ACKDETECT:
		p[5 + 0] = 'M';
		p[5 + 1] = 'M';
		memcpy(p + 5 + 2, MM_VERSION, 6);
		break;
	case AVA2_P_NONCE:
		memcpy(p + 5, buf, len);
		break;
	}

	crc = crc16(p + 5, AVA2_P_DATA_LEN);
	p[AVA2_P_COUNT - 4] = crc & 0x00ff;
	p[AVA2_P_COUNT - 3] = (crc & 0xff00) >> 8;

	//debug32("Send: %d\n", type);
}

static void send_pkg(int type, uint8_t *buf, unsigned int len)
{
	encode_pkg(g_act, type, buf, len);
	usb_write((char *)g_act, AVA2_P_COUNT);
}

static int decode_pkg(uint8_t *p, struct mm_work *mw)
{
	unsigned int expected_crc;
	unsigned int actual_crc;
	int idx, cnt;

	uint8_t *data = p + 5;

	idx = p[3];
	cnt = p[4];

	debug32("Receive: %d: %d/%d\n", p[2], idx, cnt);

	expected_crc = (p[AVA2_P_COUNT - 3] & 0xff) |
		((p[AVA2_P_COUNT - 4] & 0xff) << 8);

	actual_crc = crc16(data, AVA2_P_DATA_LEN);
	if(expected_crc != actual_crc) {
		debug32("PKG CRC failed (expected %08x, got %08x)\n",
			expected_crc, actual_crc);
		return 1;
	}

	switch (p[2]) {
	case AVA2_P_DETECT:
		send_pkg(AVA2_P_ACK, NULL, 0);
		send_pkg(AVA2_P_ACKDETECT, (uint8_t *)MM_VERSION, 6);
		break;
	case AVA2_P_STATIC:
		memcpy(&mw->coinbase_len, data, 4);
		memcpy(&mw->nonce2_offset, data + 4, 4);
		memcpy(&mw->nonce2_size, data + 8, 4);
		memcpy(&mw->merkle_offset, data + 12, 4);
		memcpy(&mw->nmerkles, data + 16, 4);
		debug32("P_STATIC:  %d, %d, %d, %d, %d\n",
			mw->coinbase_len,
			mw->nonce2_offset,
			mw->nonce2_size,
			mw->merkle_offset,
			mw->nmerkles);
		new_stratum = 0;
		break;
	case AVA2_P_JOB_ID:
		break;
	case AVA2_P_COINBASE:
		if (idx == 1)
			memset(mw->coinbase, 0, sizeof(mw->coinbase));
		memcpy(mw->coinbase + (idx - 1) * AVA2_P_DATA_LEN, data, AVA2_P_DATA_LEN);
		break;
	case AVA2_P_MERKLES:
		memcpy(mw->merkles[idx - 1], data, AVA2_P_DATA_LEN);
		break;
	case AVA2_P_HEADER:
		memcpy(mw->header + (idx - 1) * AVA2_P_DATA_LEN, data, AVA2_P_DATA_LEN);
		if (idx == cnt)
			new_stratum = 1;
		break;
	default:
		break;
	}

	return 0;
}

static int get_pkg()
{
	static char pre_last, last;
	static int start = 0, count = 2;

	while (1) {
		if (!uart_read_nonblock() && !start)
			break;

		pre_last = last;
		last = uart_read();

		if (start)
			g_pkg[count++] = last;

		if (count == AVA2_P_COUNT) {
			if (pre_last == AVA2_T1 && last == AVA2_T2) {
				if (!decode_pkg(g_pkg, &mm_work)) {
					;
				} else {
					debug32("E: package broken\n");
					send_pkg(AVA2_P_NAK, NULL, 0);
					return 1;
				}
			} else {
				debug32("E: package broken: %d-%02x, %02x\n",
					count, pre_last, last);
				send_pkg(AVA2_P_NAK, NULL, 0);
				start = 0;
				count = 2;
				return 1;
			}
			start = 0;
			count = 2;
		}

		if (pre_last == AVA2_H1 && last == AVA2_H2 && !start) {
			g_pkg[0] = pre_last;
			g_pkg[1] = last;
			start = 1;
			count = 2;
		}
	}

	return 0;
}

static int read_result()
{
	int ret = 0;

	while(!alink_rxbuf_empty()) {
		ret = 1;

		debug32("Found nonce:\n");
		alink_buf_status();
		alink_read_result(&result);
		hexdump((uint8_t *)&result, 20);
		send_pkg(AVA2_P_NONCE, (uint8_t *)&result, 20);
	}

	return ret;
}

int main(int argv, char **argc) {
	struct work work;

	delay(60);		/* Delay 60ms, wait for alink ready */
	wdg_init(1);
	wdg_feed((CPU_FREQUENCY / 1000) * 2); /* Configure the wdg to ~2 second, or it will reset FPGA */

	irq_setmask(0);
	irq_enable(1);

	uart_init();
	alink_init(0x3ff);

	adjust_fan(0x1f);

	new_stratum = 0;
	while (1) {
		wdg_feed((CPU_FREQUENCY / 1000) * 2);

		if (get_pkg())
			break;	/* FIXME */

		if (!new_stratum) {
			alink_flush_fifo();
			continue;
		}

		if (!alink_txbuf_full()) {
			miner_init_work(&mm_work, &work);
			miner_gen_work(&mm_work, &work);
			alink_send_work(&work);
		}

		read_result();

		/* TODO:
		 *   Send out heatbeat information every 2 seconds */
	}

	error(0xf);
	return 0;
}
