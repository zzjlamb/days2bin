/* C driver for DS3231 on Pico
 *
 * Adapted from Simple Raspberry Pi Pico driver for DS3231 RTC module.
 * by Victor Gabriel Costin. Licensed under the MIT license.
 * https://github.com/CostinV92/SimpleDS3231-Pico
 * which was written in C++
 */ 

#ifndef DS3231_H
#define DS3231_H

#include "stdio.h"
#include "pico/stdlib.h"


/* Device address */
#define DS3231_ADDR                 0x68

/* Device registers */
/* Data registers */
#define DS3231_SEC_REG              0x00
#define DS3231_MIN_REG              0x01
#define DS3231_HOU_REG              0x02
#define DS3231_DOW_REG              0x03
#define DS3231_DAY_REG              0x04
#define DS3231_MON_REG              0x05
#define DS3231_YEAR_REG             0x06
#define DS3231_NO_DATA_REG          0x07

/* Alarm registers */
#define DS3231_ALM1_SEC_REG         0x07
#define DS3231_ALM1_MIN_REG         0x08
#define DS3231_ALM1_HOU_REG         0x09
#define DS3231_ALM1_DAY_REG         0x0A
#define DS3231_ALM1_DAT_REG         0x0A

#define DS3231_ALM2_MIN_REG         0x0B
#define DS3231_ALM2_HOU_REG         0x0C
#define DS3231_ALM2_DAY_REG         0x0D
#define DS3231_ALM2_DAT_REG         0x0D

/* Control registers */
#define DS3231_CONTROL_REG          0x0E
#define DS3231_CTL_STA_REG          0x0F
#define DS3231_AGN_OFF_REG          0x10
#define DS3231_MSB_TMP_REG          0x11
#define DS3231_LSB_TMP_REG          0x12



    uint8_t             get_temp();

    uint8_t             get_hou();
    uint8_t             get_min();
    uint8_t             get_sec();
    const char*         get_time_str();

    void                set_sec(uint8_t sec);
    void                set_min(uint8_t min);
    void                set_hou(uint8_t hou, bool am_pm_format, bool is_pm);
    void                set_time(uint8_t hou, uint8_t min, uint8_t sec,
                                 bool am_pm_format, bool is_pm);

    uint8_t             get_day();
    uint8_t             get_mon();
    int                 get_year();
    const char*         get_date_str();

    void                set_day(uint8_t day);
    void                set_mon(uint8_t mon);
    void                set_year(int year);
    void                set_date(uint8_t day, uint8_t mon, int year);





#endif