/**
 * @file cross_platform.h
 * @author jake-is-ESD-protected
 * @date 2024-02-25
 * @brief File which contains parameters needed by both mmtool and mmtool-DSP.
 *
 * 
 */

#ifndef _CROSS_PLATFORM_H_
#define _CROSS_PLATFORM_H_

#include <inttypes.h>
#include "memory.h"

typedef struct{
    union{
        uint32_t raw;
        struct{
            uint16_t cmd;
            uint16_t len;
        };
    };
}spi_instruction_t;

#define SPI_ACK_WORD (0x0BADC0DE)
#define SPI_DUMMY_WORD (0xBADBABE5)
#define SPI_MAX_BYTE_PER_BURST 4094

typedef enum{
    SPI_REQUEST_ADC_DATA,
    SPI_EXPECT_DAC_DATA,
    SPI_REQUEST_DUMMY_DATA,
    SPI_NUM_INSTRUCTIONS
} spi_cmd_t;

void memset32( void * dest, uint32_t value, uintptr_t size )
{
  uintptr_t i;
  const uint8_t b = sizeof(uint32_t);
  for( i = 0; i < (size & (~(b-1))); i+=b ){
    memcpy( ((char*)dest) + i, &value, b);
  }  
  for( ; i < size; i++ ){
    ((char*)dest)[i] = ((char*)&value)[i&(b-1)];
  }  
}


#endif // _CROSS_PLATFORM_H_