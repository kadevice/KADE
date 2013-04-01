/*
 * KADE - Kick Ass Dynamic Encoder
 * Copyright (c) 2012 Bruno Freitas - bootsector@ig.com.br
 *                    Jon Wilson    - degenatrons@gmail.com
 *                    Kevin Mackett - kevin@sharpfork.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TWI_H
#define __TWI_H

#include <avr/io.h>
#include <avr/interrupt.h>

/*! \brief Definition of pin used as SDA. */
#define SDA PD0

/*! \brief Definition of pin used as SCL. */
#define SCL PC2

/*! \brief Definition of 7 bit slave address. */
#define SLAVE_ADDRESS 0x52


#define INITIALIZE_SDA()        ( PORTD &= ~ (1 << SDA) )    //!< Clear port.
#define READ_SDA()              ( PIND & (1 << SDA) )       //!< read pin value
#define READ_SCL()              ( PINC & (1 << SCL) )

#define SETSDA()  ( PORTD &= ~(1 << SDA) ) //Tristate
#define CLRSDA()  ( PORTD |= (1 << SDA) )  //Pull it low


/* External interrupt macros. These are device dependent. */
#define INITIALIZE_TWI_INTERRUPT()    (EICRA |= (1<<ISC01))  //!< Sets falling edge of SDA generates interrupt.
#define ENABLE_TWI_INTERRUPT()        (EIMSK |= (1<<INT0))   //!< Enables SDA interrupt.
#define DISABLE_TWI_INTERRUPT()       (EIMSK &= ~(1<<INT0))  //!< Disables SDA interrupt.
#define CLEAR_TWI_INTERRUPT_FLAG()    (EIFR = (1<<INTF0))    //!< Clears interrupt flag.


/* Dedicated general purpose registers. There are device dependent and should be set in IAR compiler configuration */
register char TWSR asm("r15"); // __no_init __regvar char TWSR @15; //!< Dedicated register which emulates TWI module TWSR
register char TWDR asm("r14"); // __no_init __regvar char TWDR @14; //!< Dedicated register which emulates TWI module TWDR
register char TWEA asm("r13"); // __no_init __regvar char TWEA @13; //!< Dedicated register for acknowlegedement. If set, ACK is sent otherwise not. Similar to TWEA bit of TWi module.

/*Normal decalarations of above variables. INCLUDE THESE IF NOT USING DEDICATED REGIATERS*/
//char TWSR = 0;
//char TWDR = 0;
//char TWEA = 0;

//! \name macros for twi state machine
//! @{
# define TWI_SLA_REQ_W_ACK_RTD              0x60    
# define TWI_SLA_DATA_RCV_ACK_RTD           0x80
# define TWI_SLA_DATA_RCV_NACK_RTD          0x88

# define TWI_SLA_REQ_R_ACK_RTD              0xA8
# define TWI_SLA_DATA_SND_ACK_RCV           0xB8
# define TWI_SLA_DATA_SND_NACK_RCV          0xC0
# define TWI_SLA_LAST_DATA_SND_ACK_RCV      0xC8

# define TWI_SLA_REPEAT_START               0xA0
# define TWI_SLA_STOP                       0x68
# define I2C_IDLE                           0x00
//! @}

unsigned char readI2Cslavebyte(void);
void twi_slave_init( void );
void twi_slave_enable( void );

void twi_slave_disable( void );
void receivedata(void);
void senddata(void);
void TWI_state_machine(void);
void GetStartCondition(void);


#endif //__TWI_H
