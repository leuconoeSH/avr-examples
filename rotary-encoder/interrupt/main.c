
#define F_CPU 8000000
#define UART_BAUD 9600				/* serial transmission speed */
#define UART_CONST F_CPU/16/UART_BAUD-1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "uart.h"

//INT0 interrupt 
ISR(INT0_vect )
{
	if(!bit_is_clear(PIND, PD3))
	{
		UART_putchar(*PSTR("+"));
	}
	else
	{
		UART_putchar(*PSTR("-"));
	}
}

//INT1 interrupt
ISR(INT1_vect )
{
	if(!bit_is_clear(PIND, PD2))
	{
		UART_putchar(*PSTR("+"));
	}
	else
	{
		UART_putchar(*PSTR("-"));
	}
}

int main(void)
{
  /* init uart */
  UART_init(UART_CONST);

  /* set PD2 and PD3 as input */
  DDRD &=~ (1 << PD2);				/* PD2 and PD3 as input */
  DDRD &=~ (1 << PD3);        
  PORTD |= (1 << PD3)|(1 << PD2);   /* PD2 and PD3 pull-up enabled   */

  GICR |= (1<<INT0)|(1<<INT1);		/* enable INT0 and INT1 */
  MCUCR |= (1<<ISC01)|(1<<ISC11)|(1<<ISC10); /* INT0 - falling edge, INT1 - reising edge */

  /* enable interrupt's */
  sei();


   while(1) 
   {
	//do nothing ;) 
	_delay_ms(1);
   }

  return 0;
}
