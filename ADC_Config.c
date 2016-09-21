
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

#include "ADC_Config.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */

// Select the AN0 pin to be used for ADC
void selectAN0()
{
    ADCON0bits.CHS = 0x00;
}

// Select the AN1 pin to be used for ADC
void selectAN1()
{
    ADCON0bits.CHS = 0x01;
}

// Select the AN2 pin to be used for ADC
void selectAN2()
{
    ADCON0bits.CHS = 0x02;
}

// Select the AN3 pin to be used for ADC
void selectAN3()
{
    ADCON0bits.CHS = 0x03;
}

// Select the AN4 pin to be used for ADC
void selectAN4()
{
    ADCON0bits.CHS = 0x04;
}

// Select the AN5 pin to be used for ADC
void selectAN5()
{
    ADCON0bits.CHS = 0x05;
}

// Select the AN6 pin to be used for ADC
void selectAN6()
{
    ADCON0bits.CHS = 0x06;
}

// Select the AN7 pin to be used for ADC
void selectAN7()
{
    ADCON0bits.CHS = 0x07;
}

unsigned int readADC()
{
    unsigned int digitalVal;
    //Start ADC for general channel
    ADCON0bits.GO_NOT_DONE = 1;
        
    //Wait for conversion to finish
    while (ADCON0bits.GO_NOT_DONE == 1);
        
    //Read ADC value from High/Low registers
    digitalVal = ADRESL;
    digitalVal += ADRESH << 8;
    return digitalVal;
}
