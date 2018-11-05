#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include "c8051F000.h"
#include "math.h"
#include "MYIIC.h"
#include "libc8051fxxx.h"

#define SYSCLK       22118400          // External crystal oscillator frequency
#define SAMPLE_RATE  51200             // Sample frequency in Hz

sbit CR_start = P0^6;

sbit green = P0^2;
sbit fd_pwm = P0^2;
sbit fd_start = P0^3;
extern unsigned int counter0;
          
extern unsigned char local_ID;
/******************************************************************************/
/*       Task 0 'job0':  RTX-51 tiny starts execution with task 0             */
/******************************************************************************/
job0 () _task_ 0  {
	Init_Device();
	UART0_Init ();
	Timer3_Init (SYSCLK/SAMPLE_RATE);   // Initialize Timer3 to overflow at

  ADC0_Init ();                       // Init ADC
	ADCEN = 1;                          // enable ADC
	PRT0CF = 0xff;                     // Set TX pin to push-pull
	DAC0H = 0xff;
	DAC0L = 0xf0;
	CR_start = 1;
 	DAC1H = 0x00;
	DAC1L = 0x00;                    
	local_ID=read_add(0x30);
	green = 0;
  os_create_task (1);                 /* start task 1                         */
  os_create_task (2);                 /* start task 2                         */
	WDTCN = 0xA5;
  while (1)  {                        /* endless loop                         */
    reply();
//		ADC_READ_R();
		os_send_signal (1);
  }
}

/******************************************************************************/
/*   Task 1 'job1':  RTX-51 tiny starts this task with os_create_task (1)     */
/******************************************************************************/
job1 () _task_ 1  {
  while (1)  {                        /* endless loop                         */     
    os_wait (K_SIG, 0, 0);            /* wait for signal                      */
		counter0++;
		if (counter0<340)
			{	
				green =1;
			}
			else if (counter0<360)
			{	
				green =0;
			}
			else if (counter0<380)
			{	
				green =1;
			}
			else if(counter0<400)
			{	
				green =0;
			}
			else
				counter0=0;
  }
}

/******************************************************************************/
/*    Task 2 'job2':  RTX-51 tiny starts this task with os_create_task (2)    */
/******************************************************************************/
job2 () _task_ 2  {
  while (1)  {                        /* endless loop                         */   
      WDTCN = 0xA5;	
		os_wait (K_TMO, 10, 0);
  }
}

