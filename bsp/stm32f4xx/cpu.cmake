add_definitions(-DSTM32F4XX)
add_definitions(-DARM)
add_definitions(-DEMBEDDED_ARM)
add_definitions(-DARM5E_ASM)
add_definitions(-DARM7M_ASM)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4")
SET(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m4")
#${CMAKE_ASM_FLAGS} 