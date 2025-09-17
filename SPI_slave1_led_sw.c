/*
 * File:   SPI_slave_led_sw.c
 * Author: admin
 *
 * Created on June 16, 2023, 5:04 PM
 */
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include<PIC16F877A.h>
#define _XTAL_FREQ 20000000
#define baud_rate 9600

#define led1 RB1
#define sw1   RC2

void Data_Transmit(unsigned char Tx_Data);


void main(void) 
{
    TRISB1 = 0;     //led1 configured as input
    TRISC2 = 1;     //sw1 configured as input
    
    TRISC5 = 0;     //sw1 configured as input
    TRISC4 = 1;     //sw1 configured as input
    TRISC3 = 1;     //led1 configured as input
    
    led1=0;
    sw1=1;
    
    SSPSTAT =0X00;
    //SSPCON1 =0X25;
    
    SSPEN=1; 
    CKP=0; 
    SSPM3=0;
    SSPM2=1;
    SSPM1=0;
    SSPM0=1;
     while(1)
    {
        
        if(SSPBUF=='A')
        {
            //__delay_ms(30);
            led1=!led1;
            
        }
   if(sw1==0)
        {
             __delay_ms(250);
             Data_Transmit('1');
        }
        else
        {
            // __delay_ms(50);
             Data_Transmit('D');
        }
    }
    return;
}

void Data_Transmit(unsigned char Tx_Data)
{
	SSPBUF = Tx_Data;
	while(!SSPIF);			//when TI==1 condition false
	SSPIF=0;
}