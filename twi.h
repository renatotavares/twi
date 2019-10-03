//hacktoberfest

#ifndef TWI_H_
#define TWI_H_


#include <avr/io.h>
#include <util/twi.h>

#ifdef __cplusplus
extern "C" {
	#endif

	void twi_init(void);
	void twi_repeated_start(void);
	void twi_write_address(unsigned char data);
	void twi_read_address(unsigned char data);
	void twi_write_data(unsigned char data);
	unsigned char twi_read_data(void);
	void twi_stop(void);


	#ifdef __cplusplus
}
#endif


#endif /* TWI_H_ */
