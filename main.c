

#include <util/delay.h>
#include "i2cmaster.h"
#define write_address 0xD0
#define read_address 0xD1
#define second 0x00
#define minute 0x01
#define hour 0x02
//uint8_t s,h,m;
#define F_CPU 8000000UL
#include <util/delay.h>
uint8_t ss,hh,mm;
//uint8_t binary;
void uart_initalize(unsigned int BAUDRATE)
{
	UBRR0H = (BAUDRATE>>8);
	UBRR0L = BAUDRATE;
	UCSR0B =0b00011000;
	UCSR0C =0b10000110;
}
unsigned char usart_recivedata()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void usart_transmitchar(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0= data;
}

void set_time(uint8_t ss,uint8_t mm,uint8_t hh)
{
	i2c_start();
	i2c_send_address(write_address);
	i2c_write_data(0x00);
	i2c_write_data(ss);
	i2c_write_data(mm);
	i2c_write_data(hh);
	i2c_stop();
}

void get_time()
{
	i2c_start();
	i2c_send_address(write_address);
	i2c_write_data(0x00);
	i2c_stop();
	i2c_start();
	i2c_read_address(read_address);
	ss=i2c_read_data();
	mm=i2c_read_data();
	hh=i2c_read_data();
	i2c_stop();
}




	


int main(void)
{
	uart_initalize(51);  
	DDRA=0xFF;
    DDRB=0xFF;
	set_time(0x01,0x02,0x05);
	
    while (1) 
    {
	
       get_time();
	   PORTA=ss>>4;
	   PORTB&=~(1<<PINB0);
	   _delay_ms(50);
	   PORTB|=(1<<PINB0);
	   PORTB&=~(1<<PINB1);
	   PORTA=ss&(0x0F);
	   _delay_ms(50);
	   PORTB|=(1<<PINB1);
	   
	   mm= get_time();
	   PORTA=mm>>4;
	   PORTB&=~(1<<PINB2);
	   _delay_ms(50);
	   PORTB|=(1<<PINB2);
	   PORTB&=~(1<<PINB3);
	   PORTA=mm&(0x0F);
	   _delay_ms(50);
	   PORTB|=(1<<PINB3);
	   
	   hh=get_time(); 
	   PORTA=hh>>4;
	   PORTB&=~(1<<PINB4);
	   _delay_ms(50);
	   PORTB|=(1<<PINB4);
	   PORTB&=~(1<<PINB5);
	   PORTA=hh&(0x0F);
	   _delay_ms(50);
	   PORTB|=(1<<PINB5);  
	    
	  usart_transmitchar((unsigned char)ss);
 	  usart_transmitchar((unsigned char)mm);
 	  usart_transmitchar((unsigned char)hh);
	
	                                                                                             
	  PORTB &=~(1<<PINB0);
	  PORTA=00000100;
	 
	}
}