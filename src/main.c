/**
 * @file main.c
 * @author jake-is-ESD-protected
 * @date 2024-02-25
 * @brief Main program entry. Configured in Arduino-style.
 *
 * Any calls by the HAL itself are done before `port_setup()`
 * is called. This function and this file in general can be
 * treated as user-level code, which sits above the HAL code.
 */


#include "port.h"
#include "memory.h"
#include "spi.h"

void port_setup(void){
    spi_init();
}


void port_loop(void){

}

