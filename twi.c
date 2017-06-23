#include "twi.h"

void twi_init()
{
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
	TWBR = 72;     // set SCL to 100kHz
	TWSR = 0;     // set prescaler
}

void twi_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0); //Wait till start condition is transmitted
	while( (TWSR & TW_STATUS_MASK ) != TW_START); // Check for the acknowledgement
}

void twi_repeated_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while( (TWCR & (1<<TWINT) ) == 0); // wait till restart condition is transmitted
	while( (TWSR & TW_STATUS_MASK) != TW_REP_START); // Check for the acknowledgement
}

void twi_write_address(unsigned char data)
{
	TWDR=data;  // Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while((TWCR & (1<<TWINT)) == 0); // Wait till complete TWDR byte transmitted
	while((TWSR & TW_STATUS_MASK) != TW_MT_SLA_ACK);  // Check for the acknowledgement
}

void twi_read_address(unsigned char data)
{
	TWDR=data;  // Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while ((TWCR & (1<<TWINT)) == 0); // Wait till complete TWDR byte received
	while((TWSR & TW_STATUS_MASK) != TW_MR_SLA_ACK);  // Check for the acknowledgement
}

void twi_write_data(unsigned char data)
{
	TWDR=data;  // put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while ((TWCR & (1<<TWINT)) == 0); // Wait till complete TWDR byte transmitted
	while((TWSR & TW_STATUS_MASK) != TW_MT_DATA_ACK); // Check for the acknowledgement
}

unsigned char twi_read_data(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);    // Clear TWI interrupt flag,Enable TWI
	while ((TWCR & (1<<TWINT)) == 0 ); // Wait till complete TWDR byte transmitted
	while((TWSR & TW_STATUS_MASK) != TW_MR_DATA_ACK); // Check for the acknowledgement
	return TWDR;
}

void twi_stop(void)
{
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	while((TWCR & (1<<TWSTO)) == 0);  // Wait till stop condition is transmitted
}



