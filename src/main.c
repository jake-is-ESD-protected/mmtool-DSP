#include "port.h"
#include "memory.h"

#define BUF_SIZE 1

uint8_t rx_buf[BUF_SIZE] = {0};
uint8_t tx_buf[BUF_SIZE] = {0};
uint8_t large_buf[128] = {0};
uint16_t i = 0;

void port_setup(void){
    HAL_SPI_Receive_DMA(&hspi1, rx_buf, BUF_SIZE);
}

void port_loop(void){
    HAL_SPI_Receive_DMA(&hspi1, rx_buf, BUF_SIZE);
    // HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_SET);
    // HAL_Delay(500);
    // HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_RESET);
    // HAL_Delay(500);
}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi){

}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
    memcpy(tx_buf, rx_buf, BUF_SIZE);
    HAL_SPI_Transmit_DMA(&hspi1, tx_buf, BUF_SIZE);
    large_buf[i++] = rx_buf[0];
    if(i == 128){
        i = 0;
    }
}

