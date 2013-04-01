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

#include "TWI.h"

/* Global variables */
unsigned char incomingBuffer[32]; //!< Incoming buffer
unsigned char outgoingBuffer[32] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; //!< Preloaded outgoing buffer for testing
unsigned char walker = 0; //!< Walks through the buffer array.

/*! \brief initialize twi slave mode
 */
void twi_slave_init( void )
{
    INITIALIZE_SDA(); 
    INITIALIZE_TWI_INTERRUPT();
    TWEA = 1;
    
    TWSR = I2C_IDLE;
}


/*! \brief enable twi slave
 */
void twi_slave_enable( void )
{
  CLEAR_TWI_INTERRUPT_FLAG();
  ENABLE_TWI_INTERRUPT();
}


/*! \brief disable twi slave
 */
void twi_slave_disable( void )
{
  DISABLE_TWI_INTERRUPT();
  CLEAR_TWI_INTERRUPT_FLAG();
}


/*! \brief Interrupt service routine for negative egde on SDA
 */

ISR(INT0_vect)
{
  volatile char retval;
  
  if(TWSR == I2C_IDLE)
  {
    GetStartCondition();
  }
  
  //!Call the TWi state machine
  TWI_state_machine();
  CLEAR_TWI_INTERRUPT_FLAG();
  ENABLE_TWI_INTERRUPT();

  
}

/*! \brief Read the slave byte after start condition
 */
inline unsigned char readI2Cslavebyte(void)
{
  char index = 0;
  unsigned char val = 0;
  char cPin = 0;
  
  
  //Let SCL go low first. MCU comes here while SCL is still high
  while(READ_SCL());
  
  //!read 8 bits from master, respond with ACK.
  //!SCL could be high or low depending on CPU speed
  for(index = 0;index < 8; index++)
  {
    while(!READ_SCL());
    cPin = READ_SDA();
    val = (val<<1) | cPin;
    while(READ_SCL())
    {
      //if SDA changes while SCL is high, it indicates STOP or START
      if((val & 1)!= cPin)
      {
        if(READ_SDA())
          TWSR = TWI_SLA_STOP;
        else
          TWSR = TWI_SLA_REPEAT_START;
        return 0;
        //!return READ_SDA()?I2C_STOP_DETECTED:I2C_START_DETECTED;
      } 
      else
        cPin = READ_SDA();
    }
  }
  
  //!Send ACK, SCL is low now
  if((val & 0xFE) == (SLAVE_ADDRESS << 1))
  {
    CLRSDA();
    while(!READ_SCL());
    while(READ_SCL());
    SETSDA();
  }
  else
  {
    TWSR = I2C_IDLE;
    return 0;
  }
  return val; 
}

/*! \brief TWI slave send data
 */
inline void senddata(void)
{
  char index;
  for(index = 0;index < 8; index++)
  {
    while(READ_SCL());
    if((TWDR >> (7 - index))&1)
      SETSDA();
    else
      CLRSDA();
    while(!READ_SCL());
  }
  //!See if we get ACK or NACk
  while(READ_SCL());
  
  //!tristate the pin to see if ack comes or not
  SETSDA();
  
  while(!READ_SCL());
  if(!READ_SDA())
    TWSR = TWI_SLA_DATA_SND_ACK_RCV;
  else
    TWSR = TWI_SLA_DATA_SND_NACK_RCV;
}


/*! \brief TWI slave receive data
 */
inline void receivedata(void)
{
  char index;
  TWDR = 0;
  
  //!read 8 bits from master, respond with ACK.
  //!SCL could be high or low depending on CPU speed
  for(index = 0;index < 8; index++)
  {
    while(!READ_SCL());
    TWDR = (TWDR<<1) | READ_SDA();
    while(READ_SCL())
    {
      //!if SDA changes while SCL is high, it indicates STOP or START
      if((TWDR & 1)!= READ_SDA())
      {
        if(READ_SDA())
          TWSR = TWI_SLA_STOP;
        else
          TWSR = TWI_SLA_REPEAT_START;
        return;
      } 
    }
  }
  
  if(TWEA)
  { 
    //!Send ACK, SCL is low now
    CLRSDA();
    while(!READ_SCL());
    while(READ_SCL());
    SETSDA();
    TWSR = TWI_SLA_DATA_RCV_ACK_RTD;
    TWEA = 0;
  }
  else
  {
    TWSR = TWI_SLA_DATA_RCV_NACK_RTD;
  }
  
  
  
}


/*! \brief TWI state machine software algorithm that emulates the hardware TWI state machine.
 */
void TWI_state_machine(void)
{
    //! get current state
START: 
    //! \brief lock twi task              
    switch (TWSR) 
    {    
        /*! Own SLA_W has been received; 
         *! ACK has been returned
         */
        case TWI_SLA_REQ_W_ACK_RTD: 
            walker = 0;
            incomingBuffer[walker++] = TWDR; 
            TWEA = 1;
            receivedata();
            goto START;
            
            break;
            
            
        //! data recieved, NACK has been returned
        case TWI_SLA_DATA_RCV_NACK_RTD:
            TWSR = I2C_IDLE;
            TWEA = 1;
            
            break;
        
        //! data recieved, ack has been returned
        case TWI_SLA_DATA_RCV_ACK_RTD:
            incomingBuffer[walker++] = TWDR;
            TWEA = 1;
            
            receivedata();
            goto START;
            
            break;


        /*! Own SLA_R has been received; 
         *! ACK has been returned
         */
        case TWI_SLA_REQ_R_ACK_RTD:
        	//TODO: Call here user callback function that fills outgoingBuffer
            walker = 0;  
            TWDR = outgoingBuffer[walker++];
            TWEA = 1;
            
            senddata();
            goto START;
            
            break;

        //! data has been transmitted, ACK has been received.
        case TWI_SLA_DATA_SND_ACK_RCV:
            TWDR = outgoingBuffer[walker++];
            TWEA = 1;
            
            senddata();
            goto START;
            
            break;
            
        //! last data has been transmitted, ACK has been received.
        case TWI_SLA_LAST_DATA_SND_ACK_RCV:
         
        //! data has been transmitted, NACK has been received.
        case TWI_SLA_DATA_SND_NACK_RCV:
            TWEA = 1;
            TWSR = I2C_IDLE;
            
            break;

        //! met stop or repeat start
        case TWI_SLA_STOP:
              //! return to idle state
              TWEA = 1;
              TWSR = I2C_IDLE;
          
            break;
        case TWI_SLA_REPEAT_START:
        	//TODO: Call here user callback function that consumes incomingBuffer
        	GetStartCondition();
        	goto START;
          
        //! Idle or bus error
        case I2C_IDLE:
        default:
            TWEA = 1;
            
            break;        
    }
}

/*! \brief Identify start condition
 */
inline void GetStartCondition(void)
{
  char retval = 0;
  //!Make sure it is the start by checking SCL high when SDA goes low
  if(READ_SCL())
  {
    DISABLE_TWI_INTERRUPT();
  }
  else //!false trigger; exit the ISR
  {
    CLEAR_TWI_INTERRUPT_FLAG();
    ENABLE_TWI_INTERRUPT();
    return;
  }
  //!lop for one or several start conditions before a STOP
  if(TWSR == I2C_IDLE || TWSR == TWI_SLA_REPEAT_START)
  {
    retval = readI2Cslavebyte(); //!read address
    if(retval == 0)//!STOP or otehr address received
    {
      TWSR = I2C_IDLE;
      CLEAR_TWI_INTERRUPT_FLAG();
      ENABLE_TWI_INTERRUPT();
      return;
    }
    else
    {
      if(retval & 1)
        TWSR = TWI_SLA_REQ_R_ACK_RTD;
      else
        TWSR = TWI_SLA_REQ_W_ACK_RTD;
    }
  }
  TWDR = retval;
  
}
