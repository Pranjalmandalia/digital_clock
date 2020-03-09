#include <avr/io.h>

void i2c_init()
{
	TWBR=0x48; // set bit rate
	TWSR=(0<<TWPS0)|(0<<TWPS1);  // prescaling 1
	
}

void i2c_start( )
{
	TWCR=0x00; //making control register bits low 
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while((TWSR & 0xF8)!=0x08);
	
}

void i2c_send_address(uint8_t write_address)

{
	TWDR=write_address; //slave address and write condition
	TWCR=(1<<TWINT)|(1<<TWEN); //enable twi and clear flag
	while (!(TWCR & (1<<TWINT)));//wait till address is transmitted
	while((TWSR & 0xF8)!=0x18); //ack received
}

void i2c_repeat_start(uint8_t read_address)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	while((TWSR & 0xF8)!=0x10);
	TWDR=read_address;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	while((TWSR & 0xF8)!=0x40);
}

void i2c_write_data(uint8_t data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while((TWSR & 0xF8)!=0x28);
}
void i2c_read_address(uint8_t read_address)
{
	TWDR=read_address;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	while((TWSR & 0xF8)!=0x40);
}
 uint8_t i2c_read_data()
{
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA); //enable twi and clear flag
	while (!(TWCR & (1<<TWINT)));//wait till address is transmitted
	return(TWDR);
}

uint8_t i2c_send_nack()
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	return(TWDR);
}
void i2c_stop()
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN); //this sends the stop condition
	while (!(TWCR & (1<<TWSTO)));//wait till stop is transmitted
}
