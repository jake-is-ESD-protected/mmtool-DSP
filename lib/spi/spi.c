/**
 * @file spi.c
 * @author jake-is-ESD-protected
 * @date 2024-02-24
 * @brief SPI peripheral abstraction for MMTool-DSP.
 *
 * 
 */

#include "spi.h"
#include "cross_platform.h"
#include "sys_err.h"

static SPI_HandleTypeDef* spi_p = NULL;

static uint8_t tx_buf[SPI_TX_BUF_SIZE] = {0};
static uint8_t rx_buf[SPI_RX_BUF_SIZE] = {0};

static spi_instruction_t instr = {0};

void spi_init(void){
    spi_p = &hspi1;
    if(spi_cmd_handshake() != HAL_OK){
        sys_err_handler();
    }
}

void spi_deinit(void){
    /// TODO: populate properly, this is unusable rn
    spi_p = NULL;
}

HAL_StatusTypeDef spi_tx_internal(uint16_t size){
    return HAL_SPI_Transmit_DMA(spi_p, tx_buf, size);
}


HAL_StatusTypeDef spi_tx_external(uint8_t *pData, uint16_t size){
    return HAL_SPI_Transmit_DMA(spi_p, pData, size);
}


HAL_StatusTypeDef spi_rx_internal(uint16_t size){
    return HAL_SPI_Receive_DMA(spi_p, rx_buf, size);
}


HAL_StatusTypeDef spi_rx_external(uint8_t *pData, uint16_t size){
    return HAL_SPI_Receive_DMA(spi_p, pData, size);
}


HAL_StatusTypeDef spi_cmd_handshake(void){
    static const uint32_t ack = SPI_ACK_WORD;
    return HAL_SPI_TransmitReceive_DMA(spi_p, (uint8_t*)&ack, (uint8_t*)&instr.raw, sizeof(instr.raw));
}


/// @brief  Device has sent all requested data, wait for next command.
/// @param hspi 
/// @attention Calling `spi_tx_internal` or `spi_tx_external` will lead here.
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
    if(spi_cmd_handshake() != HAL_OK){
        sys_err_handler();
    }
}


/// @brief Device has received all sent data, wait for next command.
/// @param hspi 
/// @attention Calling `spi_rx_internal` or `spi_rx_external` will lead here.
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
    if(spi_cmd_handshake() != HAL_OK){
        sys_err_handler();
    }
}

/// @brief Device has received command and sent its identifier as handshake.
/// @param hspi 
/// @attention Calling `spi_cmd_handshake()` will lead here.
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
    if(instr.cmd == SPI_REQUEST_DUMMY_DATA){
        memset32(tx_buf, SPI_DUMMY_WORD, instr.len);
    }
    if(spi_tx_internal(instr.len) != HAL_OK){
        sys_err_handler();
    }
}