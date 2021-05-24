#include "metronome.h"

volatile uint8_t andamento = 20, compasso = 2, t = 0, pulso_i = 0, compasso2 = 3, andamento2 = 21;
static uint32_t contaPulso = 0, ticks = 0;
char s[10];

void Delay(uint32_t v) 
{
    uint32_t lim = ticks+v;
    while ( ticks < lim ) {}
}

void SysTick_Handler(void)
{
    static int counter = 0;

    ticks++;
    contaPulso++;
   
    if( counter != 0 ) counter--;
    else counter = SOFTDIVIDER-1;
}

uint32_t getTime(void)
{
    return ticks;
}

uint32_t bpm2ms(uint8_t x)
{
    return (uint32_t)(30000/x);    
}

long map(long x, long in_min, long in_max, long out_min, long out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void boot_System(void)
{
    LED_Init(LED1|LED2|LED3);

    (void) SystemCoreClockSet(CLOCK_HFXO,1,1);
    SysTick_Config(SystemCoreClock/SYSTICKDIVIDER);   

    Button_Init(BUTTON1|BUTTON2);
    
    Task_Init();
    Task_Add(Task0,3,0);  //BUZZER            (OUTPUT)
    Task_Add(Task1,100,0);  //LER               (INPUT)
    Task_Add(Task2,50,0);  //LCD + UART + LEDs (OUTPUT)
    
    printf("\nHello!");
    printf("\nStarting......\n");

    LCD_Init();
    LCD_SetAll();
    Delay(DELAYVAL);
    LCD_ClearAll();
    Delay(DELAYVAL);

    PWM_Init(PWM1,TIMER0,PWM_LOC3,PWM_LOC_UNUSED,PWM_LOC_UNUSED);
   
    Potentiometer_Init(500000);

    __enable_irq();
}



void Task0(void)
{
    uint32_t time_ms = bpm2ms(andamento); //tempo de beep

    if((contaPulso < time_ms)||!time_ms)
        return;

    uint8_t pulso = 0;
    pulso = (pulso_i == 0) ? 1 : 0;    
    // printf("%u\n", (unsigned) pulso);

    if (pulso_i >= (compasso-1)) pulso_i = 0;
    else if (pulso_i < 0) pulso_i = 0;
    else pulso_i++;

    if (pulso) //caso FORTE
    {
        PWM_Write(TIMER0,0,PWM_FORTE);
        LED_On(LED2); 
        LED_Off(LED1);
    }
    else //caso FRACO
    {
        PWM_Write(TIMER0,0,PWM_FRACO);
        LED_On(LED1); 
        LED_Off(LED2);
        //LED_Off(LED1);
    }

    Delay(100);
    PWM_Write(TIMER0,0,PWM_DESLIGADO);
    LED_Off(LED1); 
    LED_Off(LED2);
    Delay(time_ms - 100);
	contaPulso = 0;			   
}

void Task1(void) 
{
        /*
            "DEBOUNCE" DO POTENCIOMETRO
        */
        uint32_t j = 0, k = 0;

        for (int i = 0; i<50; i++)
        {   
            k = Potentiometer_GetRawReading();
            k = map(k, 0, 255, 20, 200);    
            if (k != andamento) j++;
        }
        
        if (j==50)
           andamento = k;
        t = andamento;
        
        sprintf(s,"%3d BPM",t);

        /*
          BOTAO DA DIREITA SOMA
          BOTAO DA ESQUERDA SUBTRAI
        */        
        uint32_t b = Button_ReadReleased();
        if(b&BUTTON2)compasso++;
        else if(b&BUTTON1 && compasso > 2) compasso--;
        else if(b&BUTTON1)compasso = 4;
}

void Task2(void)
{
        /*
            ATUALIZA TUDO (LCD + GPIOs + LEDs)
        */

        if((compasso == compasso2) && (andamento == andamento2)) return;
        switch(compasso)
        {
            case 2:
                LCD_WriteNumericDisplay("2-4"); 
             //   LED_On(LED1); 
             //   LED_Off(LED2);
             //   LED_Off(LED3);
                break;

            case 3:
                LCD_WriteNumericDisplay("3-4");  
              //  LED_On(LED2); 
              //  LED_Off(LED1);
              //  LED_Off(LED3);   
                break;
        
            case 4:
                LCD_WriteNumericDisplay("4-4");
             //   LED_On(LED3); 
             //   LED_Off(LED2);
             //   LED_Off(LED1);
                break;

            default: 
                compasso = 2;
             //   LED_On(LED1); 
             //   LED_Off(LED2);
             //   LED_Off(LED3);
                LCD_WriteNumericDisplay("2-4");
        }
        LCD_WriteAlphanumericDisplay(s);

       /*
            SAIDA POR UART
       */
        printf("Andamento: %u BPM\n",(unsigned) andamento);
        printf("Compasso: %u/4\n", (unsigned) compasso);
        compasso2 = compasso;
        andamento2 = andamento;
}

