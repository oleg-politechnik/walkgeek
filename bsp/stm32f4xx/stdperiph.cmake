SET(STM32F4XX_StdPeriph_DriverSrc_DIR ${STM32_USBLib_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/src)
SET(STM32F4XX_StdPeriph_DriverInc_DIR ${STM32_USBLib_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/inc)

INCLUDE_DIRECTORIES(
    ${STM32F4XX_StdPeriph_DriverInc_DIR}
)

ADD_DEFINE(USE_STDPERIPH_DRIVER)

SET(STDPERIPH_HEADERS
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/misc.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_adc.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_can.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_crc.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_cryp.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_dac.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_dbgmcu.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_dcmi.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_dma.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_exti.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_flash.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_fsmc.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_gpio.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_hash.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_i2c.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_iwdg.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_pwr.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_rcc.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_rng.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_rtc.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_sdio.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_spi.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_syscfg.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_tim.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_usart.h
    ${STM32F4XX_StdPeriph_DriverInc_DIR}/stm32f4xx_wwdg.h
)

SET(STDPERIPH_SOURCES
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/misc.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_adc.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_can.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_crc.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_cryp.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_dac.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_dbgmcu.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_dcmi.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_dma.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_exti.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_flash.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_fsmc.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_gpio.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_hash.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_i2c.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_iwdg.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_pwr.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_rcc.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_rng.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_rtc.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_sdio.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_spi.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_syscfg.c
    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_tim.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_usart.c
#    ${STM32F4XX_StdPeriph_DriverSrc_DIR}/stm32f4xx_wwdg.c
)

SET(STDPERIPH_LIB_NAME stdperiph_stm32f4xx)
ADD_LIBRARY(${STDPERIPH_LIB_NAME} STATIC ${STDPERIPH_SOURCES} ${STDPERIPH_HEADERS})
SET(LIBRARIES ${LIBRARIES}
    ${STDPERIPH_LIB_NAME}
)
