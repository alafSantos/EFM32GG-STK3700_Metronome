#ifndef LED_H
#define LED_H

#include <stdint.h>

#ifndef BIT
#define BIT(N) (1U<<(N))
#endif

#define LED1 BIT(2)
#define LED2 BIT(3)
#define LED3 BIT(4)

void LED_Init(uint32_t leds);
void LED_On(uint32_t leds);
void LED_Off(uint32_t leds);
void LED_Toggle(uint32_t leds);
void LED_Write(uint32_t off, uint32_t on);

#endif
