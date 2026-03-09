/*
 * Copyright 2016-2026 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file	lab7.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

#define LOOPS_PER_MS 12000

void delay(uint32_t ms) {
	volatile uint32_t i, j;

	for (i = 0; i < ms; i++) {
		for (j = 0; j < LOOPS_PER_MS; j++) {
			__asm("nop");
		}
	}
}
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	SIM->SCGC5 |= (1 << 9) | (1 << 11) | (1 << 12) | (1 << 13);

	PORTA->PCR[4]  = 0x103;
	PORTC->PCR[3]  = 0x103;
	PORTD->PCR[5]  = 0x100;
	PORTE->PCR[31] = 0x100;

	PTE->PDDR |= (1U << 31);
	PTD->PDDR |= (1 << 5);
	PTA->PDDR &= ~(1 << 4);
	PTC->PDDR &= ~(1 << 3);

	PTE->PDOR |= (1U << 31);
	PTD->PDOR |= (1 << 5);

	/* Force the counter to be placed into memory. */
	volatile static int i = 0 ;
	volatile static int j = 0 ;

	while(1) {
		i = PTA->PDIR & (1 << 4);
		j = PTC->PDIR & (1 << 3);

		// 1. Both SW1 and SW3 are NOT pressed
		if (i && j) {
			PTE->PDOR &= ~(1U << 31); // Red LED ON  (Write 0)
			PTD->PDOR |=  (1 << 5);   // Green LED OFF (Write 1)
		}

		// 2. SW1 is pressed and SW3 is NOT pressed
		else if (!i && j) {
			PTD->PDOR &= ~(1 << 5);   // Green LED ON (Write 0)
			PTE->PTOR  =  (1U << 31); // Red LED blink (Toggle)
			delay(100);
		}

		// 3. SW1 is NOT pressed and SW3 is pressed
		else if (i && !j) {
			PTD->PDOR |=  (1 << 5);   // Green LED OFF (Write 1)
			PTE->PTOR  =  (1U << 31); // Red LED blink (Toggle)
			delay(100);
		}

		// 4. Both SW1 and SW3 are pressed
		else {
			// First phase: Red ON, Green OFF
			PTE->PDOR &= ~(1U << 31); // Red LED ON
			PTD->PDOR |=  (1 << 5);   // Green LED OFF
			delay(100);

			// Second phase: Red OFF, Green ON (Alternate)
			PTE->PDOR |=  (1U << 31); // Red LED OFF
			PTD->PDOR &= ~(1 << 5);   // Green LED ON
			delay(100);
		}
	}
	return 0 ;
}
