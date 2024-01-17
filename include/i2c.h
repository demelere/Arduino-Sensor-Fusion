#ifndef I2C_H
#define I2C_H

void TWI_init();
void TWI_start();
void TWI_stop();
void TWI_write(uint8_t data);
uint8_t TWI_read_ack();
uint8_t TWI_read_nack();

#endif // I2C_H
