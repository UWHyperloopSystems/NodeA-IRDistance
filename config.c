/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "config.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
    OSCCONbits.IRCF2 = 1;       // All set -> 4 MHz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    
    OSCCONbits.SCS1 = 0;        // All clear -> select primary oscillator
    OSCCONbits.SCS0 = 0;
    
    OSCTUNEbits.PLLEN = 1;      // Enable PLL x4
}

void enable_interrupts(void)
{
    /* Enable Interrupts */
    RCONbits.IPEN   = 0;    // Enable interrupt priority
    INTCONbits.GIE  = 1;    // Enable interrupts
    INTCONbits.PEIE = 1;    // Enable peripheral interrupts.
    
    //PIE1bits.RCIE   = 1;    // Enable USART receive interrupt
    PIE3bits.RXB0IE = 1;    // Enable CAN receive buffer 0 interrupt
    PIE3bits.RXB1IE = 1;    // Enable CAN receive buffer 1 interrupt
}

void wait_ms(uint16_t time)
{
    static long timel = 0;
    timel = time * 400l;
    for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}

void setAnalogIn()
{
    //Set Port AN0-AN10 to Analog
    ADCON1bits.PCFG = 0;            
    ADCON2bits.ADFM = 1;    //Right justified - values converted to 0-1023
                            //Registers ADRESH and ADRESL hold this converted value
    
    //V-REF+ is VDD and V-REF- is VSS
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    
    //Set Acquisition Time to be 4T_AD
    ADCON2bits.ACQT2 = 0;
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT0 = 0;
    
    //Set A/D Conversion clock frequency F_OSC/32
    ADCON2bits.ADCS2 = 0;
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS0 = 0;

    
    //Set Analog ports as Input
    TRISAbits.TRISA0 = 1;   //AN0
    TRISAbits.TRISA1 = 1;   //AN1
    TRISAbits.TRISA2 = 1;   //AN2
    TRISAbits.TRISA3 = 1;   //AN3
    TRISAbits.TRISA5 = 1;   //AN4
    TRISEbits.TRISE0 = 1;   //AN5
    TRISEbits.TRISE1 = 1;   //AN6
    TRISEbits.TRISE2 = 1;   //AN7
    
    
    //Enable ADC
    ADCON0bits.ADON = 1; 
}

void setActuatorCntrl()
{
    //Set RD0-RD7 and RC0-RC7 as Digital outputs
    TRISDbits.TRISD0 = 0;   //A2_0
    TRISDbits.TRISD1 = 0;   //A2_1
    TRISDbits.TRISD2 = 0;   //A3_0
    TRISDbits.TRISD3 = 0;   //A3_1
    TRISDbits.TRISD4 = 0;   //A6_0
    TRISDbits.TRISD5 = 0;   //A6_1
    TRISDbits.TRISD6 = 0;   //A7_0
    TRISDbits.TRISD7 = 0;   //A7_1

    TRISCbits.TRISC0 = 0;   //A0_0
    TRISCbits.TRISC1 = 0;   //A0_1
    TRISCbits.TRISC2 = 0;   //A1_0
    TRISCbits.TRISC3 = 0;   //A1_1
    TRISCbits.TRISC4 = 0;   //A4_0
    TRISCbits.TRISC5 = 0;   //A4_1
    //TRISCbits.TRISC6 = 0;   //A5_0 --- UART TX
    //TRISCbits.TRISC7 = 0;   //A5_1 --- UART RX
    
    TRISBbits.TRISB0 = 0;   //Temp A5_0
    TRISBbits.TRISB1 = 0;   //Temp A5_1
    
    //Debug LED for interrupts
    TRISAbits.TRISA7 = 0;   //A2_0


}