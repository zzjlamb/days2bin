#ifndef FLASH_UTILS_H
#define FLASH_UTILS_H

#include <stdint.h>

inline uint32_t *getAddressPersistent() {
extern uint32_t ADDR_PERSISTENT[];
    return ADDR_PERSISTENT;
}

#endif