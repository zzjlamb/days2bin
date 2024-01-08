#ifndef STORED_DATA_H
#define STORED_DATA_H

#include <time.h>

struct Bin_Info {
    time_t date;
    uint8_t interval;
};

Bin_Info binsData [3];

#endif

