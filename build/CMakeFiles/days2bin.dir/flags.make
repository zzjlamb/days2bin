# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# compile ASM with /Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-gcc
# compile C with /Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-gcc
# compile CXX with /Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-g++
ASM_DEFINES = -DCYW43_LWIP=1 -DLIB_PICO_ASYNC_CONTEXT_POLL=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RAND=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_UART=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_POLL=1 -DPICO_DEOPTIMIZED_DEBUG=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PROGRAM_NAME=\"days2bin\" -DPICO_PROGRAM_VERSION_STRING=\"0.1\" -DPICO_TARGET_NAME=\"days2bin\" -DPICO_USE_BLOCKED_RAM=0

ASM_INCLUDES = -I/Users/john/pico/days2bin -I/Users/john/pico/days2bin/.. -I/Users/john/pico/days2bin/access_point -I/Users/john/pico/days2bin/access_point/dhcpserver -I/Users/john/pico/days2bin/access_point/dnsserver -I/Users/john/pico/pico-sdk/src/common/pico_stdlib/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_gpio/include -I/Users/john/pico/pico-sdk/src/common/pico_base/include -I/Users/john/pico/days2bin/build/generated/pico_base -I/Users/john/pico/pico-sdk/src/boards/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_platform/include -I/Users/john/pico/pico-sdk/src/rp2040/hardware_regs/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_base/include -I/Users/john/pico/pico-sdk/src/rp2040/hardware_structs/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_claim/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_sync/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_irq/include -I/Users/john/pico/pico-sdk/src/common/pico_sync/include -I/Users/john/pico/pico-sdk/src/common/pico_time/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_timer/include -I/Users/john/pico/pico-sdk/src/common/pico_util/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_uart/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_resets/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_clocks/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_pll/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_vreg/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_watchdog/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_xosc/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_divider/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_runtime/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_printf/include -I/Users/john/pico/pico-sdk/src/common/pico_bit_ops/include -I/Users/john/pico/pico-sdk/src/common/pico_divider/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_double/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_float/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_malloc/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_bootrom/include -I/Users/john/pico/pico-sdk/src/common/pico_binary_info/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_stdio/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_int64_ops/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_mem_ops/include -I/Users/john/pico/pico-sdk/src/rp2_common/boot_stage2/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_i2c/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_async_context/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_lwip/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_rand/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_unique_id/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_flash/include -I/Users/john/pico/pico-sdk/lib/lwip/src/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_arch/include -I/Users/john/pico/pico-sdk/lib/cyw43-driver/src -I/Users/john/pico/pico-sdk/lib/cyw43-driver/firmware -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_driver/cybt_shared_bus -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_pio/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_dma/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_exception/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_driver/include -I/Users/john/pico/days2bin/build/pico-sdk/src/rp2_common/pico_cyw43_driver

ASM_FLAGS = -mcpu=cortex-m0plus -mthumb -O0 -g -ffunction-sections -fdata-sections

C_DEFINES = -DCYW43_LWIP=1 -DLIB_PICO_ASYNC_CONTEXT_POLL=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RAND=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_UART=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_POLL=1 -DPICO_DEOPTIMIZED_DEBUG=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PROGRAM_NAME=\"days2bin\" -DPICO_PROGRAM_VERSION_STRING=\"0.1\" -DPICO_TARGET_NAME=\"days2bin\" -DPICO_USE_BLOCKED_RAM=0

C_INCLUDES = -I/Users/john/pico/days2bin -I/Users/john/pico/days2bin/.. -I/Users/john/pico/days2bin/access_point -I/Users/john/pico/days2bin/access_point/dhcpserver -I/Users/john/pico/days2bin/access_point/dnsserver -I/Users/john/pico/pico-sdk/src/common/pico_stdlib/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_gpio/include -I/Users/john/pico/pico-sdk/src/common/pico_base/include -I/Users/john/pico/days2bin/build/generated/pico_base -I/Users/john/pico/pico-sdk/src/boards/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_platform/include -I/Users/john/pico/pico-sdk/src/rp2040/hardware_regs/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_base/include -I/Users/john/pico/pico-sdk/src/rp2040/hardware_structs/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_claim/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_sync/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_irq/include -I/Users/john/pico/pico-sdk/src/common/pico_sync/include -I/Users/john/pico/pico-sdk/src/common/pico_time/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_timer/include -I/Users/john/pico/pico-sdk/src/common/pico_util/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_uart/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_resets/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_clocks/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_pll/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_vreg/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_watchdog/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_xosc/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_divider/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_runtime/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_printf/include -I/Users/john/pico/pico-sdk/src/common/pico_bit_ops/include -I/Users/john/pico/pico-sdk/src/common/pico_divider/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_double/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_float/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_malloc/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_bootrom/include -I/Users/john/pico/pico-sdk/src/common/pico_binary_info/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_stdio/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_int64_ops/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_mem_ops/include -I/Users/john/pico/pico-sdk/src/rp2_common/boot_stage2/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_i2c/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_async_context/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_lwip/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_rand/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_unique_id/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_flash/include -I/Users/john/pico/pico-sdk/lib/lwip/src/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_arch/include -I/Users/john/pico/pico-sdk/lib/cyw43-driver/src -I/Users/john/pico/pico-sdk/lib/cyw43-driver/firmware -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_driver/cybt_shared_bus -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_pio/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_dma/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_exception/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_driver/include -I/Users/john/pico/days2bin/build/pico-sdk/src/rp2_common/pico_cyw43_driver

C_FLAGS = -mcpu=cortex-m0plus -mthumb -O0 -g -std=gnu11 -ffunction-sections -fdata-sections

CXX_DEFINES = -DCYW43_LWIP=1 -DLIB_PICO_ASYNC_CONTEXT_POLL=1 -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_CYW43_ARCH=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RAND=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_UART=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UNIQUE_ID=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico_w\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_CYW43_ARCH_POLL=1 -DPICO_DEOPTIMIZED_DEBUG=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PROGRAM_NAME=\"days2bin\" -DPICO_PROGRAM_VERSION_STRING=\"0.1\" -DPICO_TARGET_NAME=\"days2bin\" -DPICO_USE_BLOCKED_RAM=0

CXX_INCLUDES = -I/Users/john/pico/days2bin -I/Users/john/pico/days2bin/.. -I/Users/john/pico/days2bin/access_point -I/Users/john/pico/days2bin/access_point/dhcpserver -I/Users/john/pico/days2bin/access_point/dnsserver -I/Users/john/pico/pico-sdk/src/common/pico_stdlib/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_gpio/include -I/Users/john/pico/pico-sdk/src/common/pico_base/include -I/Users/john/pico/days2bin/build/generated/pico_base -I/Users/john/pico/pico-sdk/src/boards/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_platform/include -I/Users/john/pico/pico-sdk/src/rp2040/hardware_regs/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_base/include -I/Users/john/pico/pico-sdk/src/rp2040/hardware_structs/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_claim/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_sync/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_irq/include -I/Users/john/pico/pico-sdk/src/common/pico_sync/include -I/Users/john/pico/pico-sdk/src/common/pico_time/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_timer/include -I/Users/john/pico/pico-sdk/src/common/pico_util/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_uart/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_resets/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_clocks/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_pll/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_vreg/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_watchdog/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_xosc/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_divider/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_runtime/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_printf/include -I/Users/john/pico/pico-sdk/src/common/pico_bit_ops/include -I/Users/john/pico/pico-sdk/src/common/pico_divider/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_double/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_float/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_malloc/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_bootrom/include -I/Users/john/pico/pico-sdk/src/common/pico_binary_info/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_stdio/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_int64_ops/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_mem_ops/include -I/Users/john/pico/pico-sdk/src/rp2_common/boot_stage2/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_i2c/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_async_context/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_lwip/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_rand/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_unique_id/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_flash/include -I/Users/john/pico/pico-sdk/lib/lwip/src/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_arch/include -I/Users/john/pico/pico-sdk/lib/cyw43-driver/src -I/Users/john/pico/pico-sdk/lib/cyw43-driver/firmware -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_driver/cybt_shared_bus -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_pio/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_dma/include -I/Users/john/pico/pico-sdk/src/rp2_common/hardware_exception/include -I/Users/john/pico/pico-sdk/src/rp2_common/pico_cyw43_driver/include -I/Users/john/pico/days2bin/build/pico-sdk/src/rp2_common/pico_cyw43_driver

CXX_FLAGS = -mcpu=cortex-m0plus -mthumb -O0 -g -std=gnu++17 -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables -fno-rtti -fno-use-cxa-atexit
