#ifndef METRONOME_H
#define METRONOME_H

#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "em_device.h"
#include "led.h"
#include "lcd.h"
#include "pwm.h"
#include "clock_efm32gg2.h"
#include "potentiometer.h"
#include "uart2.h"
#include "button.h"
#include "gpio.h"
#include "led.h"
#include "tt_tasks.h"

#define SYSTICKDIVIDER 1000
#define SOFTDIVIDER 1000
#define DELAYVAL 2

void Delay(uint32_t v);
void SysTick_Handler(void);
uint32_t getTime(void);
void Task0(void);
void Task1(void);
void Task2(void);
void pulsar(uint8_t pulso);
void boot_System(void);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif
