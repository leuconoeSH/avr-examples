
#define F_CPU 8000000						/* crystal f				 */
#define UART_BAUD 9600						/* serial transmission speed */
#define UART_CONST F_CPU/16/UART_BAUD-1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "uart.h"

uint8_t read_gray_code_from_encoder(void )
{
 uint8_t val=0;

  if(!bit_is_clear(PIND, PD2))
	val |= (1<<1);

  if(!bit_is_clear(PIND, PD3))
	val |= (1<<0);

  return val;
}

int main(void)
{
  uint8_t val=0, val_tmp =0;

  /* init UART */
  UART_init(UART_CONST);

  /* set PD2 and PD3 as input */
  DDRD &=~ (1 << PD2);				/* PD2 and PD3 as input */
  DDRD &=~ (1 << PD3);        
  PORTD |= (1 << PD3)|(1 << PD2);   /* PD2 and PD3 pull-up enabled   */

  /* ready start value */
  val = read_gray_code_from_encoder();

  /* enable interrupt's */
  sei();

   while(1) 
   {
	   val_tmp = read_gray_code_from_encoder(); 

	   if(val != val_tmp)
	   {
		   if( /*(val==2 && val_tmp==3) ||*/
			   (val==3 && val_tmp==1) ||
			   /*(val==1 && val_tmp==0) ||*/
			   (val==0 && val_tmp==2)
			 )
		   {
				UART_putchar(*PSTR("+"));
		   }
		   else if( /*(val==3 && val_tmp==2) ||*/
			   (val==2 && val_tmp==0) ||
			   /*(val==0 && val_tmp==1) ||*/
			   (val==1 && val_tmp==3)
			 )
		   {
				UART_putchar(*PSTR("-"));
		   }

		   val = val_tmp;
	   }

	   _delay_ms(1);
   }

  return 0;
}
