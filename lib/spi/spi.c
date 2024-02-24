/**
 * @file spi.c
 * @author jake-is-ESD-protected
 * @date 2024-02-24
 * @brief SPI peripheral abstraction for MMTool-DSP.
 *
 * 
 */

#include "spi.h"

SPI_HandleTypeDef* spi_p = NULL;

uint8_t tx_buf[SPI_TX_BUF_SIZE] = {0};
uint8_t rx_buf[SPI_RX_BUF_SIZE] = {0};

void spi_init(void){
    spi_p = &hspi1;
}


HAL_StatusTypeDef spi_tx_internal(void){
    return HAL_SPI_Transmit_DMA(spi_p, tx_buf, SPI_TX_BUF_SIZE);
}


HAL_StatusTypeDef spi_tx_external(uint8_t *pData, uint16_t size){
    return HAL_SPI_Transmit_DMA(spi_p, pData, size);
}


HAL_StatusTypeDef spi_rx_internal(void){
    return HAL_SPI_Receive_DMA(spi_p, rx_buf, SPI_RX_BUF_SIZE);
}


HAL_StatusTypeDef spi_rx_external(uint8_t *pData, uint16_t size){
    return HAL_SPI_Receive_DMA(spi_p, pData, size);
}


void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi){

}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
    
}


void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi){
    
}


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
    uint8_t val = rx_buf[0]++;
    val++;
    spi_tx_external(&val, SPI_TX_BUF_SIZE);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_0){
        spi_rx_internal();
    }
}