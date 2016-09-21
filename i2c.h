/******************************************************************************/
/* Function prototypes and definitions                                        */
/******************************************************************************/

void i2c_init(void);
void i2c_wait(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
void i2c_address(unsigned char address, unsigned char mode);
unsigned char i2c_read(unsigned char ack);
unsigned short i2c_get_udata(char mAddr, char addr);
short i2c_get_data(char mAddr, char addr);
void i2c_write_raw(char cnt, char cmd);