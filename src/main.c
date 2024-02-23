#include "port.h"
#include "memory.h"

#define BUF_SIZE 1

uint8_t rx_buf[BUF_SIZE] = {0};
uint8_t tx_buf[BUF_SIZE] = {0};
uint8_t large_buf[128] = {0};
uint8_t i = 0;
uint8_t restart = 0;

void port_setup(void){
    HAL_SPI_Receive_DMA(&hspi1, rx_buf, BUF_SIZE);
}

void port_loop(void){
    if(restart){
        HAL_SPI_Receive_DMA(&hspi1, rx_buf, BUF_SIZE);
        restart = 0;
    }
    // HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_SET);
    // HAL_Delay(500);
    // HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_RESET);
    // HAL_Delay(500);
}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi){
    
    
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
    uint8_t val = rx_buf[0]++;
    val++;
    large_buf[i++] = val;
    HAL_SPI_Transmit_DMA(&hspi1, &val, BUF_SIZE);
    if(i == 32){
        i = 0;
    }
    restart = 1;
}
