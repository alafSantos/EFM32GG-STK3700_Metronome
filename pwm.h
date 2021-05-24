#ifndef PWM_H
#define PWM_H

#ifndef BIT
#define BIT(N) (1U<<(N))
#endif

#define PWM1  BIT(1)

#define PWM_LOC0            0
#define PWM_LOC1            1
#define PWM_LOC2            2
#define PWM_LOC3            3
#define PWM_LOC4            4
#define PWM_LOC5            5
#define PWM_LOC_UNUSED      -1

#define PWM_FORTE     5000
#define PWM_FRACO     1000
#define PWM_DESLIGADO 0

int         PWM_Init(uint32_t PWMs, TIMER_TypeDef* timer, int loc0, int loc1, int loc3);
int         PWM_Config(TIMER_TypeDef *timer, unsigned div, unsigned top, int pol);
int         PWM_Write(TIMER_TypeDef *timer, unsigned channel, unsigned value);
unsigned    PWM_Read(TIMER_TypeDef *timer, unsigned channel);
void        PWM_Start(TIMER_TypeDef *timer);
void        PWM_Stop(TIMER_TypeDef *timer);
#endif  // PWM_H

