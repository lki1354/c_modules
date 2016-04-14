/*! \file buffer.c
 *  \brief 
 *  \author Lukas Kiechle
 *  \date 2016-03-26 creat date
 *  \copyright  
 *	\version 0.1
 */

#include "buffer.h"


void buffer_init(buffer_t* buffer, uint8_t* data, uint8_t len){
  buffer->_data = data;
  buffer->capacity = len;
  buffer_clear(buffer);
}

void buffer_clear(buffer_t *  buffer){
  buffer->info = 1<<EMPTY_BUFFER;
  buffer->_mounted = 0;
  buffer->_entry = 0;
  buffer->_exit = 0;
}

int16_t buffer_write_byte(buffer_t* buffer, uint8_t byte){
  uint8_t buffer_point = 0;

  if( buffer->info & FULL_BUFFER){
    return -1; 
  }
  
  buffer->_data[ buffer->_entry] = byte;
  
  buffer->_mounted++;
  if(buffer->_mounted >= buffer->capacity){
    buffer->info |= 1<<FULL_BUFFER;
  }

  buffer_point = buffer->_entry++;
  if( buffer_point >= buffer->capacity){
    buffer->_entry = 0;
  }else{
    buffer->_entry = buffer_point;
  }

  if( buffer->_mounted >= buffer->capacity*0.9 ){
    buffer->info |= 1<<FULL_90_BUFFER;
  }

  return 0;

}

int16_t buffer_write_bytes(buffer_t* buffer, uint8_t *data, uint8_t len){
  int16_t result = 0;
  uint8_t i=0;

  while( (i<len) && (result==0) ){
    result = buffer_write_byte(buffer,data[i]);
    i++;
  }
  return result;
}

int16_t buffer_read_byte(buffer_t* buffer){
  int16_t return_value = 0;
  uint8_t buffer_point = 0;
  
  if( buffer->info & EMPTY_BUFFER){
    return -1; 
  }

  return_value = buffer->_data[buffer->_exit];
  
  buffer->_mounted--;

  buffer_point = buffer->_exit++;
  if(buffer_point >= buffer->_entry){
    buffer->_exit = buffer->_entry;
  }else if( buffer_point >= buffer->capacity ){
    buffer->_exit = 0;
  }else{
    buffer->_exit = buffer_point;
  }
  
  return return_value;

}

int16_t buffer_read_bytes(buffer_t* buffer, uint8_t *data, uint8_t len){
  int16_t result = 0;
  uint8_t i=0;

  while( (i<len) && (result==0) ){
    result = buffer_read_byte(buffer);
    data[i] = (uint8_t) result;
    i++;
  }
  if( i == (len-1) ){
    result = 0;
  }
  return result;


}

uint8_t buffer_get_size(buffer_t* buffer){
  return buffer->_mounted;
}
uint8_t buffer_get_capacity(buffer_t* buffer){
  return buffer->capacity;
}


