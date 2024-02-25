/**
 * @file spi.h
 * @author jake-is-ESD-protected
 * @date 2024-02-24
 * @brief SPI peripheral abstraction for MMTool-DSP.
 *
 * After lots of trial and error, the SPI abstraction here
 * runs completely without external or timer interrupts
 * and without a busy-poll in a loop. DMA reception and
 * sending is kicked off by the command and data mechanism
 * present here. SPI starts with a pending TXRX flag for
 * DMA which is enacted when a command word (32 bit) arrives.
 * While it arrives, a handshake word is sent back for
 * identification, it can be found as `SPI_ACK_WORD`.
 * The process then parses the command and waits for either
 * a data transmission or reception, which is enacted by
 * empty frames sent by the host. The expected length of 
 * the incoming/outgoing data are in the 16 MSBs of the 
 * command word, the 16 LSBs are the command type.
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "port.h"

#define SPI_TX_BUF_SIZE 2048
#define SPI_RX_BUF_SIZE 2048

/// @brief Initialize the SPI peripheral abstraction.
void spi_init(void);

/// @brief De-initialize the SPI peripheral abstraction.
void spi_deinit(void);

/// @brief Transmit SPI data in DMA-mode from the internal buffer.
/// @param size Size of buffer data in bytes.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_tx_internal(uint16_t size);

/// @brief Transmit SPI data in DMA-mode from a given buffer. 
/// @param pData Buffer to transmit.
/// @param size Size of buffer data in bytes.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_tx_external(uint8_t *pData, uint16_t size);

/// @brief Receive SPI data in DMA-mode into the internal buffer. 
/// @param size Size of buffer data in bytes.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_rx_internal(uint16_t size);

/// @brief Receive SPI data in DMA-mode into a given buffer.
/// @param pData Buffer to receive into.
/// @param size Expected size of buffer data in bytes.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_rx_external(uint8_t *pData, uint16_t size);

/// @brief Async-await a 32-bit command and send back a handshake word.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_cmd_handshake(void);

#endif // _SPI_H_