/*
/   SISTEMAS EMBARCADOS 2
/   Aluno: Alaf do Nascimento Santos
/   Matricula: 2017100781
/   Projeto Final - Metronomo de 3 compassos e 180 andamentos.
*/

//Serial pelo terminal
//tio --baudrate 115200 --databits 8 --flow none --stopbits 1 --parity none /dev/ttyACM0

#include "metronome.h"
#include "tt_tasks.h"

int main(void)
{  
    boot_System();
    while (1) Task_Dispatch();
}
