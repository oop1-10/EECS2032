#include "fsl_device_registers.h"

#include "fsl_gpio.h"

#include "fsl_port.h"

#include "fsl_clock.h"


#define BOARD_LED_GREEN_GPIO GPIOD

#define BOARD_LED_GREEN_PORT PORTD

#define BOARD_LED_GREEN_PIN  5U


void SysTick_Handler(void) {

    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_PIN);

}


int main(void) {

    CLOCK_EnableClock(kCLOCK_PortD);


    gpio_pin_config_t led_gpio_config = {

        kGPIO_DigitalOutput,

        1

    };

    PORT_SetPinMux(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, kPORT_MuxAsGpio);

    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &led_gpio_config);


    SysTick_Config(SystemCoreClock / 4U);


    while (1) {

    }

}
