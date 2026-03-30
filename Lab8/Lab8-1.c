/*

 * Copyright 2016-2026 NXP

 * All rights reserved.

 * SPDX-License-Identifier: BSD-3-Clause

 */


#include <stdio.h>

#include "board.h"

#include "peripherals.h"

#include "pin_mux.h"

#include "clock_config.h"

#include "fsl_debug_console.h"


void PORTC_PORTD_IRQHandler(void) {


    if ((PORTC->ISFR & (1U << 3)) != 0) {

        for (volatile int i = 0; i < 20000; i++);

        if ((PTA->PDIR & (1U << 4)) == 0) {

            PTD->PTOR = (1U << 5);

        }


        PORTC->ISFR = (1U << 3);

    }

}


int main(void) {

    /* Init board hardware. */

    BOARD_InitBootPins();

    BOARD_InitBootClocks();

    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

    BOARD_InitDebugConsole();

#endif


    __disable_irq();

    NVIC_DisableIRQ(PORTC_PORTD_IRQn);

    SIM->SCGC5 |= (1 << 9) | (1 << 11) | (1 << 12);


    PORTC->PCR[3] = 0xA0103;

    PTC->PDDR &= ~(1U << 3);


    PORTA->PCR[4] = 0x00103;

    PTA->PDDR &= ~(1U << 4);


    PORTD->PCR[5] = 0x00100;

    PTD->PDDR |= (1U << 5);

    PTD->PSOR = (1U << 5);


    NVIC_SetPriority(PORTC_PORTD_IRQn, 128);

    NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);

    NVIC_EnableIRQ(PORTC_PORTD_IRQn);


    __enable_irq();


    while(1) {

        __WFI();

    }


    return 0;

}
