
/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic18f4685.h>        /* For true/false definition */
#include "i2c.h"

#define I2C_WRITE 0
#define I2C_READ 1

// Initialize MSSP port. (12F1822 - other devices may differ)
void i2c_init(void)
{
    /* Set SCL and SDA pins as inputs */
    TRISCbits.RC3 = 1;           	
	TRISCbits.RC4 = 1;

    /* I2C enabled, Master mode */
	SSPCON1= 0b00101000;
	SSPCON2 = 0x00;
    
    // I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) 
    SSPADD = 79;            // To get 100kHz
    SSPSTAT = 0b11000000; 	// Slew rate disabled

}

// i2c_Wait - wait for I2C transfer to finish
void i2c_wait(void){
    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));
}

// i2c_Start - Start I2C communication
void i2c_start(void)
{
 	i2c_wait();
	SSPCON2bits.SEN = 1;
}

// i2c_Restart - Re-Start I2C communication
void i2c_restart(void){
 	i2c_wait();
	SSPCON2bits.RSEN = 1;
}

// i2c_Stop - Stop I2C communication
void i2c_stop(void)
{
 	i2c_wait();
 	SSPCON2bits.PEN = 1;
}

// i2c_Write - Sends one byte of data
void i2c_write(unsigned char data)
{
 	i2c_wait();
 	SSPBUF = data;
}

// i2c_Address - Sends Slave Address and Read/Write mode
// mode is either I2C_WRITE or I2C_READ
void i2c_address(unsigned char address, unsigned char mode)
{
	i2c_wait();
 	SSPBUF = (address << 1) + mode;
}

// i2c_Read - Reads a byte from Slave device
unsigned char i2c_read(unsigned char ack)
{
	// Read data from slave
	// ack should be 1 if there is going to be more data read
	// ack should be 0 if this is the last byte of data read
 	unsigned char i2cReadData;

 	i2c_wait();
	SSPCON2bits.RCEN = 1;
 	i2c_wait();
 	i2cReadData = SSPBUF;
 	i2c_wait();
 	if (ack)
        ACKDT = 0;			// Ack
	else
        ACKDT = 1;			// NAck
	SSPCON2bits.ACKEN = 1;  // send acknowledge sequence

	return i2cReadData;
}

unsigned short i2c_get_udata(char mAddr, char addr)
{
    i2c_start();
    i2c_address(mAddr, 0);
    i2c_write(addr);
    i2c_restart();
    i2c_address(mAddr, 1);
    unsigned char data1 = i2c_read(1);
    unsigned char data0 = i2c_read(0);
    i2c_stop();
    return data0 + (data1 << 8);
}

short i2c_get_data(char mAddr, char addr)
{
    i2c_start();
    i2c_address(mAddr, 0);
    i2c_write(addr);
    i2c_restart();
    i2c_address(mAddr, 1);
    unsigned char data1 = i2c_read(1);
    unsigned char data0 = i2c_read(0);
    i2c_stop();
    return data0 + (data1 << 8);
}

void i2c_write_raw(char cnt, char cmd)
{
    i2c_start();
    i2c_address(0x77, 0);
    i2c_write(cnt);
    i2c_write(cmd);
    i2c_stop();
}
