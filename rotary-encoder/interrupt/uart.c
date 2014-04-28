
#include <avr/io.h>
#include <avr/interrupt.h>

void UART_putchar(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;


} // end of UART_putchar()


void UART_putstring(unsigned char *txt)
{
	uint8_t i;

	for(i=0;i<255;i++)
	{
		if(!txt[i])
			break;

		UART_putchar(txt[i]);
	}
}

unsigned char UART_getchar(void)
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
} // end of UART_getchar()

void UART_init(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

} // end of UART_init()

//SIGNAL (SIG_UART_RECV)
ISR(USART_RXC_vect )
{
	//unsigned char c;
	//c = UDR;
}


