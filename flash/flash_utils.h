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
#define MAGIC_NUMBER_BIN 3      // Dummy extra bin to hold magic number
#define MAGIC_NUMBER 0xA4       // Bit pattern to indicate flash data has been initialised
                                // Erased flash would be 0xFF

typedef struct __attribute__((packed)) Bin_Info {
    // Initial collection date
    // NB this does not match c date types eg C mday is 0-30
    
    uint8_t interval;   // Collection interval in weeks
    uint8_t yy;         // year 00-99
    uint8_t mm;         // month 1-12
    uint8_t dd;        //  day 1-31

} Bin_Info;

// Populate the binsData array with some test settings
void make_test_data();      // For development and debugging only
void write_flash();

// Returns a pointer to the Bin_Info data in flash
Bin_Info * read_flash();

// fills an array of int - one for each bin type
// -1 means no collection for that bin colour 
void getDaysToCollection(int dayArray[NUM_BIN_KINDS], uint8_t clock_century, uint8_t clock_yy, uint8_t clock_mm, uint8_t clock_dd);

#ifdef __cplusplus
}
#endif

#endif