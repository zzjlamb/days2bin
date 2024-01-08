/*
Utilities for writing and reading to flash

Our target sector is 4k from xb_offset + 

*/

#include "flash_utils.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/flash.h"
#include <hardware/sync.h>

void write_flash(){
   uint8_t buf[FLASH_PAGE_SIZE];
    for (int i=0; i<FLASH_PAGE_SIZE;i++){
        buf[i]=0;
    }
    buf [0] = 1;
    buf [1] = 2;
    buf [3] = 3;

    uint32_t * ap = (uint32_t*) getAddressPersistent();
    uint32_t xb = XIP_BASE;
    uint32_t xb_offset = (uint32_t)ap - xb;

    printf("Persistent flash address: %p. Offset from XIP_BASE: %x\n", ap, xb_offset);
    printf("Flash contents:\n");
    for (int i=0;i<16;i++){
        printf("%2x ",ap[i]);
    }
    printf("\n\n");

    uint32_t ints = save_and_disable_interrupts();
    flash_range_program(xb_offset, buf, FLASH_PAGE_SIZE);
    restore_interrupts (ints);

    printf("Flash contents after write:\n");
    for (int i=0;i<16;i++){
        printf("%2x ",ap[i]);
    }
    printf("\n\n");


}



 