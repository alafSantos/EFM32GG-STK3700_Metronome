#include <stdint.h>
#include "gpio.h"
#include "led.h"

void LED_Init(uint32_t leds) 
{
    GPIO_Init(GPIOD,0,leds);
    GPIO_WritePins(GPIOD,leds,0);
}

void LED_On(uint32_t leds) 
{
    GPIO_WritePins(GPIOD,0,leds);
}

void LED_Off(uint32_t leds)
{
    GPIO_WritePins(GPIOD,leds,0);
}

void LED_Toggle(uint32_t leds)
{
    GPIO_TogglePins(GPIOD,leds);
}

void LED_Write(uint32_t off, uint32_t on) 
{
    GPIO_WritePins(GPIOD,off,on);
}
