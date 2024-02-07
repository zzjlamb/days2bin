# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

if(CMAKE_HOST_APPLE)
#set(PICO_SDK_PATH "/home/john/pico/pico-sdk")
else()
 set(PICO_SDK_PATH "/home/john/pico/pico-sdk")
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

set(PICO_DEOPTIMIZED_DEBUG 1)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(MAKE_FS_DATA_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/external/makefsdata)

if (NOT EXISTS ${MAKE_FS_DATA_SCRIPT})
        file(DOWNLOAD
                https://raw.githubusercontent.com/krzmaz/lwip/e15654409d14a238aec5ed4bd5516063938c9345/src/apps/http/makefsdata/makefsdata
                ${MAKE_FS_DATA_SCRIPT}
                )
endif()
message("Running makefsdata script")
execute_process(COMMAND
        perl ${MAKE_FS_DATA_SCRIPT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        ECHO_OUTPUT_VARIABLE
        ECHO_ERROR_VARIABLE
        )
file(RENAME fsdata.c my_fsdata.c)

project(days2bin C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(days2bin 
      days2bin.cpp 
      flash/flash_utils.c 
      peripherals/SimpleDS3231_new.cpp 
      peripherals/busscan.c
      peripherals/glowbit.cpp
      access_point/picow_access_point.c
      access_point/dhcpserver/dhcpserver.c
      access_point/dnsserver/dnsserver.c
      access_point/ssi.c
      access_point/cgi.c
      )

pico_set_linker_script(days2bin ${CMAKE_SOURCE_DIR}/flash/memmap_custom.ld)

pico_set_program_name(days2bin "days2bin")
pico_set_program_version(days2bin "0.1")

pico_enable_stdio_uart(days2bin 1)
pico_enable_stdio_usb(days2bin 0)

# Add the standard library to the build
target_link_libraries(days2bin
        pico_stdlib
        hardware_i2c)

# Add the standard include files to the build
target_include_directories(days2bin PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
  ${CMAKE_CURRENT_LIST_DIR}/access_point
  ${CMAKE_CURRENT_LIST_DIR}/access_point/dhcpserver
  ${CMAKE_CURRENT_LIST_DIR}/access_point/dnsserver
)

# Add any user requested libraries
target_link_libraries(days2bin 
        #pico_cyw43_arch_none
        pico_cyw43_arch_lwip_poll
        pico_lwip_http
        )

pico_add_extra_outputs(days2bin)

