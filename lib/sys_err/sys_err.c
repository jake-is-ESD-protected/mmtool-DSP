/**
 * @file sys_err.c
 * @author jake-is-ESD-protected
 * @date 2024-02-24
 * @brief Top-level ubiquitous error handling.
 *
 * 
 */

#include "sys_settings.h"
#include "sys_err.h"
#include "port.h"

#ifdef SYS_USE_LED_LOOP_ERR_HANDLER
void sys_err_handler(void){
    HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_SET);
    HAL_Delay(SYS_LED_LOOP_ERR_BLINK_TIME_MS);
    HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_RESET);
    HAL_Delay(SYS_LED_LOOP_ERR_BLINK_TIME_MS);
}
#else
void sys_err_handler(void){
    /// TODO: Add meaningful error handling
}
#endif