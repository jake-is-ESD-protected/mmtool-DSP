/**
 * @file spi.h
 * @author jake-is-ESD-protected
 * @date 2024-02-24
 * @brief SPI peripheral abstraction for MMTool-DSP.
 *
 * The SPI peripheral is configured with a soft-CS on
 * pin PB0 masked as externel interrupt (EXTI0). This
 * interrupt then triggers the flag for the DMA read
 * operation. In addition to the declarations listed 
 * below, the file `spi.c` contains the non-`__weak`
 * definitions of the `HAL_SPI_XxCpltCallback` functions
 * which contain application specific operations.
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "port.h"

#define SPI_TX_BUF_SIZE 1
#define SPI_RX_BUF_SIZE 1

/// @brief Initialize the SPI peripheral abstraction.
void spi_init(void);

/// @brief Transmit SPI data in DMA-mode from the internal buffer.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_tx_internal(void);

/// @brief Transmit SPI data in DMA-mode from a given buffer. 
/// @param pData Buffer to transmit.
/// @param size Size of buffer data in bytes.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_tx_external(uint8_t *pData, uint16_t size);

/// @brief Receive SPI data in DMA-mode into the internal buffer. 
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_rx_internal(void);

/// @brief Receive SPI data in DMA-mode into a given buffer.
/// @param pData Buffer to receive into.
/// @param size Expected size of buffer data in bytes.
/// @return `HAL_StatusTypeDef`: Status flag.
HAL_StatusTypeDef spi_rx_external(uint8_t *pData, uint16_t size);

#endif // _SPI_H_