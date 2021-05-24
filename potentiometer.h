#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdint.h>

uint32_t Potentiometer_Init(uint32_t freq);
uint32_t Potentiometer_GetRawReading(void);

#endif
