/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <stdio.h>
#include <pic18f4685.h>        /* For true/false definition */
#include <string.h> 

#include "uart.h"
#include "can.h"
#include "interrupts.h"

char num;

// Main Interrupt Service Routine (ISR)
void interrupt ISR(void)
{
    if(PIR3bits.RXB0IF)
    {
        Message newMessage;
        ecan_receive_rxb0(&newMessage);
        ecan_rxb0_clear();          // Clear flag
        PIR3bits.RXB0IF = 0;
        print_can_message(&newMessage);
    }
    if(PIR3bits.RXB1IF)
    {
        Message newMessage;
        ecan_receive_rxb1(&newMessage);
        ecan_rxb1_clear();
        PIR3bits.RXB1IF = 0;
        print_can_message(&newMessage);
    }
}

/* Print CAN message sid and data to UART */
void print_can_message(Message* mess)
{
    unsigned int sid = mess->sid;
    double number;
    memcpy(&number, &mess->data, mess->len);
    long integer;
    memcpy(&integer, &mess->data, mess->len);
    
    if(sid == 0x106 || sid == 0x107)
    {
        char letter;
        if(sid == 0x106)
            letter = 'X';
        else
            letter = 'Y';
        char uart_text[10];
        sprintf(uart_text, "%c: %.3g \t", letter, number);
        uart_write_text(uart_text);
    }
    else
    {
        char uart_text[22];
        sprintf(uart_text, "Z: %.3g \r\n", number);
        uart_write_text(uart_text);
    }
    
    /*char uart_text[20];
    if(sid <= 0x110)
    {
        sprintf(uart_text, "%x:%f\r\n", mess->sid, number);
    }
    else
    {
        sprintf(uart_text, "%x:%li\r\n", mess->sid, integer);
    }
    
    uart_write_text(uart_text); */
}
