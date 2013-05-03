SET(CPU_CMAKE ${CMAKE_CURRENT_LIST_FILE})

ADD_DEFINE(STM32F4XX)
ADD_DEFINE(ARM)

SET(CMAKE_C_FLAGS "-isystem ${TOOLCHAIN_INC_DIR} -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4 -fno-builtin -Wall -Wextra -std=gnu99 ${CMAKE_C_FLAGS}") # CACHE INTERNAL "c compiler flags"
SET(CMAKE_CXX_FLAGS "-isystem ${TOOLCHAIN_INC_DIR} -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4 -fno-builtin -Wall  -fdata-sections -ffunction-sections ${CMAKE_C_FLAGS}") # CACHE INTERNAL "cxx compiler flags"
SET(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m4" CACHE INTERNAL "asm compiler flags")
