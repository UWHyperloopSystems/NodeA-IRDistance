/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h> 

#endif

#include "can.h"
#include "uart.h"
#include "i2c.h"
#include "user.h"
#include "config.h"
#include "interrupts.h"
#include "ADC_Config.h"    /* ADC Channel selects and read function */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */
// Adjust to system clock
#define _XTAL_FREQ 16000000

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/
//void print_can_message(Message* mess);

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
Message data; //global message used to send can signals
unsigned int distance0 = 0;
unsigned int distance1 = 0;

void main(void)
{
    /* Initialization functions called below */
    ConfigureOscillator();
    
    //uart_init(9600);
    ecan_init();
    //i2c_init();
    setAnalogIn();
     
    TRISAbits.TRISA0 = 0;    // set pin digital 0 as an output
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    TRISDbits.TRISD2 = 0;

    int wait = 10;
    char firstByte = 1;
    char secondByte = 1;
    char thirdByte = 1;
    char fourthByte = 1;

    while(1)
    {  
        LATAbits.LATA7 ^= 1; // switches every iteration of while loop
        wait_ms(wait);

      
        while(!(RXB0CONbits.RXB0FUL)){};
        
        Message newMessage;
        ecan_receive_rxb0(&newMessage);

        if(newMessage.data[0] == 0x02){ //to check its reading analog
            LATAbits.LATA0 ^= 1;
            selectAN6();
            distance0 = readADC();
            if(distance0 > 1){
                LATAbits.LATA6 ^= 1;
                firstByte = distance0/256;  
                secondByte = distance0%256; 
            }
            selectAN2();
            distance1 = readADC();
            if(distance1 > 1){
                LATDbits.LATD2 ^= 1;
                thirdByte = distance1/256;  
                fourthByte = distance1%256; 
            }
            data.sid = 0x001;
            data.len = 4;
            data.data[0] = firstByte;
            data.data[1] = secondByte;
            data.data[2] = thirdByte;
            data.data[3] = fourthByte;
            ecan_send(&data);  
        }                    
        ecan_rxb0_clear();          // Clear flag
        wait_ms(wait);
    }
}
