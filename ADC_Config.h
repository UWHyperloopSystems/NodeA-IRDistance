/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
void selectAN0();
void selectAN1();
void selectAN2();
void selectAN3();
void selectAN4();
void selectAN5();
void selectAN6();
void selectAN7();

unsigned int readADC();



/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

