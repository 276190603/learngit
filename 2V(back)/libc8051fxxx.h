#ifndef __lib80c51fxxx_H__
#define __lib80c51fxxx_H__

void Reset_Sources_Init();
void DAC_Init();
void Voltage_Reference_Init();
void Port_IO_Init();
void Oscillator_Init();
void Interrupts_Init();
void Init_Device(void);	
void UART0_Init (void);
void Send_Hex(unsigned char chr);
void RS485_Receive_Data(unsigned char *buf,unsigned char *len);
void reply(void);
void ADC0_Init (void);
void Timer3_Init (int counts);
unsigned int float2half(float source);
float ADC_READ_V(void);
float ADC_READ_R(void);	
float ADC_READ_T(void);
void fangdian(void);
#endif