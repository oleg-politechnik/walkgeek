SET(STM32F4XX_StdPeriph_DriverSrc_DIR ${STM32_USBSTDLib_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/src)
SET(STM32F4XX_StdPeriph_DriverInc_DIR )

INCLUDE_DIRECTORIES(
    ${STM32_USBSTDLib_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/inc
)

add_definitions(-DUSE_STDPERIPH_DRIVER)

SET(CSP_SOURCES ${CSP_SOURCES}
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
