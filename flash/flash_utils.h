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
    // Initial collection date
    // NB this does not match c date types eg C mday is 0-30
    
    uint8_t dd;        //  day 1-31
    uint8_t mm;         // month 1-12
    uint8_t yy;         // year 00-99

    uint8_t interval;   // Collection interval in days
};

inline uint8_t *getAddressPersistent() {
extern uint8_t ADDR_PERSISTENT[];
    return ADDR_PERSISTENT;
}

// Populate the binsData array with some test settings
void make_test_data();

void write_flash();

#ifdef __cplusplus
}
#endif

#endif