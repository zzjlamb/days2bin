#ifndef FLASH_UTILS_H
#define FLASH_UTILS_H

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_BIN_KINDS 3
#define RED_BIN 0
#define YELLOW_BIN 1
#define GREEN_BIN 2

struct Bin_Info {
    time_t date;        // Initial collection date
    uint8_t interval;   // Collection interval in days
};

Bin_Info binsData [NUM_BIN_KINDS];

inline uint8_t *getAddressPersistent() {
extern uint8_t ADDR_PERSISTENT[];
    return ADDR_PERSISTENT;
}

void write_flash();

#ifdef __cplusplus
}
#endif

#endif