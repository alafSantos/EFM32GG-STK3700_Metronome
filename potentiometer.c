#include <stdint.h>
#include "em_device.h"
#include "potentiometer.h"
#include "adc.h"

static int32_t caltemp;            // Calibration Temperature
static int32_t caltempread;        // Temperature reading at 1v25

static void GetCalibrationValues(void) 
{
    caltemp = (DEVINFO->CAL>>16)&0xFF;              // 0x0FE0_81B2
    caltempread = (DEVINFO->ADC0CAL2>>20)&0xFFF;    // 0x0FE0_81BE
}

uint32_t Potentiometer_Init(uint32_t freq) 
{
    ADC_Init(freq);
    GetCalibrationValues();
    return 0;
}

uint32_t Potentiometer_GetRawReading(void)
{
    return ADC_Read(ADC_CH0);
}
