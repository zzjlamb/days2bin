/*
Utilities for writing and reading to flash

Our target sector is 4k from xb_offset + 

*/

#include "flash_utils.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/flash.h"
#include <hardware/sync.h>
#include "time.h"

struct Bin_Info binsData [NUM_BIN_KINDS]={};

// Populate the binsData array with some test settings
void make_test_data(){

    binsData[RED_BIN].dd = 11;
    binsData[RED_BIN].mm = 1;
    binsData[RED_BIN].yy = 24;
    binsData[RED_BIN].interval = 7;

    binsData[YELLOW_BIN].dd = 11;
    binsData[YELLOW_BIN].mm = 1;
    binsData[YELLOW_BIN].yy = 24;
    binsData[YELLOW_BIN].interval = 14;

    binsData[GREEN_BIN].interval = 0;
}

void write_flash(){ 
    
    uint8_t buf[FLASH_PAGE_SIZE]={};

    uint8_t * binsDataPtr = (uint8_t*)&binsData;
    for(int i=0;i < sizeof(binsData);i++){
        buf[i]=binsDataPtr[i];
    }

    uint8_t * ap = (uint8_t*) getAddressPersistent();
    uint32_t xb = XIP_BASE;
    uint32_t xb_offset = (uint32_t)ap - xb;

    printf("Persistent flash address: %p. Offset from XIP_BASE: %x\n", ap, xb_offset);
    printf("Flash contents:\n");
    for (int i=0;i<32;i++){
        for (int j = 0; j<16;j++){
            printf("%3u ",ap[i*16+j]);
        }
        printf("\n");
    }
    printf("\n\n");

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(xb_offset,FLASH_SECTOR_SIZE);
    flash_range_program(xb_offset, buf, FLASH_PAGE_SIZE);
    restore_interrupts (ints);

    printf("Flash contents after write:\n");
    for (int i=0;i<32;i++){
        for (int j = 0; j<16;j++){
            printf("%3u ",ap[i*16+j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

struct Bin_Info * read_flash(){
    struct Bin_Info * ap = (struct Bin_Info*) getAddressPersistent();
    return ap;
}
 