/*
 * gpio.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GPIO MODER options */
/* -------------------------------------------------*/
#define GPIO_MODE_MASK                  0x0003
#define GPIO_MODE_SHIFT                 0x0000

#define GPIO_MODE_INPUT                 0x0000
#define GPIO_MODE_OUTPUT                0x0001
#define GPIO_MODE_ALTERNATE             0x0002
#define GPIO_MODE_ANALOG                0x0003

/* GPIO OTYPER options */
/* -------------------------------------------------*/
#define GPIO_OTYPE_MASK                 0x0004
#define GPIO_OTYPE_SHIFT                0x0002

#define GPIO_OTYPE_PUSHPULL             0x0000
#define GPIO_OTYPE_OPENDRAIN            0x0004

/* GPIO OSPEEDR options */
/* -------------------------------------------------*/
#define GPIO_OSPEED_MASK                0x0018
#define GPIO_OSPEED_SHIFT               0x0003

#define GPIO_OSPEED_LOW                 0x0000
#define GPIO_OSPEED_MEDIUM              0x0008
#define GPIO_OSPEED_HIGH                0x0010
#define GPIO_OSPEED_VERY_HIGH           0x0018

/* GPIO PUPDR options */
/* -------------------------------------------------*/
#define GPIO_PUPD_MASK                  0x0060
#define GPIO_PUPD_SHIFT                 0x0005

#define GPIO_PUPD_NONE                  0x0000
#define GPIO_PUPD_PULLUP                0x0020
#define GPIO_PUPD_PULLDOWN              0x0040

/* GPIO ASCR options */
/* -------------------------------------------------*/
#define GPIO_ANALOG_SWITCH              0x0080
/* -------------------------------------------------*/

/* PIN configuration options */
/* -------------------------------------------------*/
#define GPIO_PIN_INDEX_MASK             0x000f
#define GPIO_PIN_INDEX_SHIFT            0x0000
#define GPIO_PIN_GROUP_MASK             0x00f0
#define GPIO_PIN_GROUP_SHIFT            0x0004
#define GPIO_PIN_AFSEL_MASK             0x0f00
#define GPIO_PIN_AFSEL_SHIFT            0x0008

#define GPIO_PIN_MASK(pin)              (1 << ((pin) & 0xf))

#if defined(STM32L476xx)    

/* PIN combinations for stm32l476 */
/* -------------------------------------------------*/
#define GPIO_PIN_PA0                    0x0000
#define GPIO_PIN_PA1                    0x0001
#define GPIO_PIN_PA2                    0x0002
#define GPIO_PIN_PA3                    0x0003
#define GPIO_PIN_PA4                    0x0004
#define GPIO_PIN_PA5                    0x0005
#define GPIO_PIN_PA6                    0x0006
#define GPIO_PIN_PA7                    0x0007
#define GPIO_PIN_PA8                    0x0008
#define GPIO_PIN_PA9                    0x0009
#define GPIO_PIN_PA10                   0x000a
#define GPIO_PIN_PA11                   0x000b
#define GPIO_PIN_PA12                   0x000c
#define GPIO_PIN_PA13                   0x000d
#define GPIO_PIN_PA14                   0x000e
#define GPIO_PIN_PA15                   0x000f
#define GPIO_PIN_PB0                    0x0010
#define GPIO_PIN_PB1                    0x0011
#define GPIO_PIN_PB2                    0x0012
#define GPIO_PIN_PB3                    0x0013
#define GPIO_PIN_PB4                    0x0014
#define GPIO_PIN_PB5                    0x0015
#define GPIO_PIN_PB6                    0x0016
#define GPIO_PIN_PB7                    0x0017
#define GPIO_PIN_PB8                    0x0018
#define GPIO_PIN_PB9                    0x0019
#define GPIO_PIN_PB10                   0x001a
#define GPIO_PIN_PB11                   0x001b
#define GPIO_PIN_PB12                   0x001c
#define GPIO_PIN_PB13                   0x001d
#define GPIO_PIN_PB14                   0x001e
#define GPIO_PIN_PB15                   0x001f
#define GPIO_PIN_PC0                    0x0020
#define GPIO_PIN_PC1                    0x0021
#define GPIO_PIN_PC2                    0x0022
#define GPIO_PIN_PC3                    0x0023
#define GPIO_PIN_PC4                    0x0024
#define GPIO_PIN_PC5                    0x0025
#define GPIO_PIN_PC6                    0x0026
#define GPIO_PIN_PC7                    0x0027
#define GPIO_PIN_PC8                    0x0028
#define GPIO_PIN_PC9                    0x0029
#define GPIO_PIN_PC10                   0x002a
#define GPIO_PIN_PC11                   0x002b
#define GPIO_PIN_PC12                   0x002c
#define GPIO_PIN_PC13                   0x002d
#define GPIO_PIN_PC14                   0x002e
#define GPIO_PIN_PC15                   0x002f
#define GPIO_PIN_PD0                    0x0030
#define GPIO_PIN_PD1                    0x0031
#define GPIO_PIN_PD2                    0x0032
#define GPIO_PIN_PD3                    0x0033
#define GPIO_PIN_PD4                    0x0034
#define GPIO_PIN_PD5                    0x0035
#define GPIO_PIN_PD6                    0x0036
#define GPIO_PIN_PD7                    0x0037
#define GPIO_PIN_PD8                    0x0038
#define GPIO_PIN_PD9                    0x0039
#define GPIO_PIN_PD10                   0x003a
#define GPIO_PIN_PD11                   0x003b
#define GPIO_PIN_PD12                   0x003c
#define GPIO_PIN_PD13                   0x003d
#define GPIO_PIN_PD14                   0x003e
#define GPIO_PIN_PD15                   0x003f
#define GPIO_PIN_PE0                    0x0040
#define GPIO_PIN_PE1                    0x0041
#define GPIO_PIN_PE2                    0x0042
#define GPIO_PIN_PE3                    0x0043
#define GPIO_PIN_PE4                    0x0044
#define GPIO_PIN_PE5                    0x0045
#define GPIO_PIN_PE6                    0x0046
#define GPIO_PIN_PE7                    0x0047
#define GPIO_PIN_PE8                    0x0048
#define GPIO_PIN_PE9                    0x0049
#define GPIO_PIN_PE10                   0x004a
#define GPIO_PIN_PE11                   0x004b
#define GPIO_PIN_PE12                   0x004c
#define GPIO_PIN_PE13                   0x004d
#define GPIO_PIN_PE14                   0x004e
#define GPIO_PIN_PE15                   0x004f
#define GPIO_PIN_PF0                    0x0050
#define GPIO_PIN_PF1                    0x0051
#define GPIO_PIN_PF2                    0x0052
#define GPIO_PIN_PF3                    0x0053
#define GPIO_PIN_PF4                    0x0054
#define GPIO_PIN_PF5                    0x0055
#define GPIO_PIN_PF6                    0x0056
#define GPIO_PIN_PF7                    0x0057
#define GPIO_PIN_PF8                    0x0058
#define GPIO_PIN_PF9                    0x0059
#define GPIO_PIN_PF10                   0x005a
#define GPIO_PIN_PF11                   0x005b
#define GPIO_PIN_PF12                   0x005c
#define GPIO_PIN_PF13                   0x005d
#define GPIO_PIN_PF14                   0x005e
#define GPIO_PIN_PF15                   0x005f
#define GPIO_PIN_PG0                    0x0060
#define GPIO_PIN_PG1                    0x0061
#define GPIO_PIN_PG2                    0x0062
#define GPIO_PIN_PG3                    0x0063
#define GPIO_PIN_PG4                    0x0064
#define GPIO_PIN_PG5                    0x0065
#define GPIO_PIN_PG6                    0x0066
#define GPIO_PIN_PG7                    0x0067
#define GPIO_PIN_PG8                    0x0068
#define GPIO_PIN_PG9                    0x0069
#define GPIO_PIN_PG10                   0x006a
#define GPIO_PIN_PG11                   0x006b
#define GPIO_PIN_PG12                   0x006c
#define GPIO_PIN_PG13                   0x006d
#define GPIO_PIN_PG14                   0x006e
#define GPIO_PIN_PG15                   0x006f
#define GPIO_PIN_PH0                    0x0070
#define GPIO_PIN_PH1                    0x0071
#define GPIO_PIN_NONE                   0x00ff

/* PIN confgurations for stm32l476 */
/* -------------------------------------------------*/
#define GPIO_PIN_PA8_MCO                0x0008
#define GPIO_PIN_PA13_JTMS_SWDIO        0x000d
#define GPIO_PIN_PA14_JTCK_SWCLK        0x000e
#define GPIO_PIN_PA15_JTDI              0x000f
#define GPIO_PIN_PB2_RTC_OUT            0x0012
#define GPIO_PIN_PB3_JTDO_TRACESWO      0x0013
#define GPIO_PIN_PB4_NJTRST             0x0014
#define GPIO_PIN_PB15_RTC_REFIN         0x001f
#define GPIO_PIN_PE2_TRACECK            0x0042
#define GPIO_PIN_PE3_TRACED0            0x0043
#define GPIO_PIN_PE4_TRACED1            0x0044
#define GPIO_PIN_PE5_TRACED2            0x0045
#define GPIO_PIN_PE6_TRACED3            0x0046

#define GPIO_PIN_PA8_USART1_CK          0x0708
#define GPIO_PIN_PA9_USART1_TX          0x0709
#define GPIO_PIN_PA10_USART1_RX         0x070a
#define GPIO_PIN_PA11_USART1_CTS        0x070b
#define GPIO_PIN_PA12_USART1_RTS_DE     0x070c
#define GPIO_PIN_PB3_USART1_RTS_DE      0x0713
#define GPIO_PIN_PB4_USART1_CTS         0x0714
#define GPIO_PIN_PB5_USART1_CK          0x0715
#define GPIO_PIN_PB6_USART1_TX          0x0716
#define GPIO_PIN_PB7_USART1_RX          0x0717
#define GPIO_PIN_PG9_USART1_TX          0x0769
#define GPIO_PIN_PG10_USART1_RX         0x076a
#define GPIO_PIN_PG11_USART1_CTS        0x076b
#define GPIO_PIN_PG12_USART1_RTS_DE     0x076c
#define GPIO_PIN_PG13_USART1_CK         0x076d

#define GPIO_PIN_PA0_USART2_CTS         0x0700
#define GPIO_PIN_PA1_USART2_RTS_DE      0x0701
#define GPIO_PIN_PA2_USART2_TX          0x0702
#define GPIO_PIN_PA3_USART2_RX          0x0703
#define GPIO_PIN_PA4_USART2_CK          0x0704
#define GPIO_PIN_PD3_USART2_CTS         0x0733
#define GPIO_PIN_PD4_USART2_RTS_DE      0x0734
#define GPIO_PIN_PD5_USART2_TX          0x0735
#define GPIO_PIN_PD6_USART2_RX          0x0736
#define GPIO_PIN_PD7_USART2_CK          0x0737

#define GPIO_PIN_PA6_USART3_CTS         0x0706
#define GPIO_PIN_PB0_USART3_CK          0x0710
#define GPIO_PIN_PB1_USART3_RTS_DE      0x0711
#define GPIO_PIN_PB10_USART3_TX         0x071a
#define GPIO_PIN_PB11_USART3_RX         0x071b
#define GPIO_PIN_PB12_USART3_CK         0x071c
#define GPIO_PIN_PB13_USART3_CTS        0x071d
#define GPIO_PIN_PB14_USART3_RTS_DE     0x071e
#define GPIO_PIN_PC4_USART3_TX          0x0724
#define GPIO_PIN_PC5_USART3_RX          0x0725
#define GPIO_PIN_PC10_USART3_TX         0x072a
#define GPIO_PIN_PC11_USART3_RX         0x072b
#define GPIO_PIN_PC12_USART3_CK         0x072c
#define GPIO_PIN_PD2_USART3_RTS_DE      0x0732
#define GPIO_PIN_PD8_USART3_TX          0x0738
#define GPIO_PIN_PD9_USART3_RX          0x0739
#define GPIO_PIN_PD10_USART3_CK         0x073a
#define GPIO_PIN_PD11_USART3_CTS        0x073b
#define GPIO_PIN_PD12_USART3_RTS_DE     0x073c

#define GPIO_PIN_PA0_UART4_TX           0x0800
#define GPIO_PIN_PA1_UART4_RX           0x0801
#define GPIO_PIN_PA15_UART4_RTS_DE      0x080f
#define GPIO_PIN_PB7_UART4_CTS          0x0817
#define GPIO_PIN_PC10_UART4_TX          0x082a
#define GPIO_PIN_PC11_UART4_RX          0x082b

#define GPIO_PIN_PB4_UART5_RTS_DE       0x0814
#define GPIO_PIN_PB5_UART5_CTS          0x0815
#define GPIO_PIN_PC12_UART5_TX          0x082c
#define GPIO_PIN_PD2_UART5_RX           0x0832

#define GPIO_PIN_PB10_LPUART1_RX        0x081a
#define GPIO_PIN_PB11_LPUART1_TX        0x081b
#define GPIO_PIN_PB12_LPUART1_RTS_DE    0x081c
#define GPIO_PIN_PB13_LPUART1_CTS       0x081d
#define GPIO_PIN_PC0_LPUART1_RX         0x0820
#define GPIO_PIN_PC1_LPUART1_TX         0x0821
#define GPIO_PIN_PG5_LPUART1_CTS        0x0865
#define GPIO_PIN_PG6_LPUART1_RTS_DE     0x0866
#define GPIO_PIN_PG7_LPUART1_TX         0x0867
#define GPIO_PIN_PG8_LPUART1_RX         0x0868

#define GPIO_PIN_PB5_I2C1_SMBA          0x0415
#define GPIO_PIN_PB6_I2C1_SCL           0x0416
#define GPIO_PIN_PB7_I2C1_SDA           0x0417
#define GPIO_PIN_PB8_I2C1_SCL           0x0418
#define GPIO_PIN_PB9_I2C1_SDA           0x0419
#define GPIO_PIN_PG13_I2C1_SDA          0x046d
#define GPIO_PIN_PG14_I2C1_SCL          0x046e
#define GPIO_PIN_PG15_I2C1_SMBA         0x046f

#define GPIO_PIN_PB10_I2C2_SCL          0x041a
#define GPIO_PIN_PB11_I2C2_SDA          0x041b
#define GPIO_PIN_PB12_I2C2_SMBA         0x041c
#define GPIO_PIN_PB13_I2C2_SCL          0x041d
#define GPIO_PIN_PB14_I2C2_SDA          0x041e
#define GPIO_PIN_PF0_I2C2_SDA           0x0450
#define GPIO_PIN_PF1_I2C2_SCL           0x0451
#define GPIO_PIN_PF2_I2C2_SMBA          0x0452

#define GPIO_PIN_PB2_I2C3_SMBA          0x0412
#define GPIO_PIN_PC0_I2C3_SCL           0x0420
#define GPIO_PIN_PC1_I2C3_SDA           0x0421
#define GPIO_PIN_PG6_I2C3_SMBA          0x0466
#define GPIO_PIN_PG7_I2C3_SCL           0x0467
#define GPIO_PIN_PG8_I2C3_SDA           0x0468

#define GPIO_PIN_PA4_SPI1_NSS           0x0504
#define GPIO_PIN_PA5_SPI1_SCK           0x0505
#define GPIO_PIN_PA6_SPI1_MISO          0x0506
#define GPIO_PIN_PA7_SPI1_MOSI          0x0507
#define GPIO_PIN_PA15_SPI1_NSS          0x050f
#define GPIO_PIN_PB3_SPI1_SCK           0x0513
#define GPIO_PIN_PB4_SPI1_MISO          0x0514
#define GPIO_PIN_PB5_SPI1_MOSI          0x0515
#define GPIO_PIN_PE12_SPI1_NSS          0x054c
#define GPIO_PIN_PE13_SPI1_SCK          0x054d
#define GPIO_PIN_PE14_SPI1_MISO         0x054e
#define GPIO_PIN_PE15_SPI1_MOSI         0x054f
#define GPIO_PIN_PG2_SPI1_SCK           0x0562
#define GPIO_PIN_PG3_SPI1_MISO          0x0563
#define GPIO_PIN_PG4_SPI1_MOSI          0x0564
#define GPIO_PIN_PG5_SPI1_NSS           0x0565

#define GPIO_PIN_PB9_SPI2_NSS           0x0519
#define GPIO_PIN_PB10_SPI2_SCK          0x051a
#define GPIO_PIN_PB12_SPI2_NSS          0x051c
#define GPIO_PIN_PB13_SPI2_SCK          0x051d
#define GPIO_PIN_PB14_SPI2_MISO         0x051e
#define GPIO_PIN_PB15_SPI2_MOSI         0x051f
#define GPIO_PIN_PC2_SPI2_MISO          0x0522
#define GPIO_PIN_PC3_SPI2_MOSI          0x0523
#define GPIO_PIN_PD0_SPI2_NSS           0x0530
#define GPIO_PIN_PD1_SPI2_SCK           0x0531
#define GPIO_PIN_PD3_SPI2_MISO          0x0533
#define GPIO_PIN_PD4_SPI2_MOSI          0x0534

#define GPIO_PIN_PA4_SPI3_NSS           0x0604
#define GPIO_PIN_PA15_SPI3_NSS          0x060f
#define GPIO_PIN_PB3_SPI3_SCK           0x0613
#define GPIO_PIN_PB4_SPI3_MISO          0x0614
#define GPIO_PIN_PB5_SPI3_MOSI          0x0615
#define GPIO_PIN_PC10_SPI3_SCK          0x062a
#define GPIO_PIN_PC11_SPI3_MISO         0x062b
#define GPIO_PIN_PC12_SPI3_MOSI         0x062c
#define GPIO_PIN_PG9_SPI3_SCK           0x0669
#define GPIO_PIN_PG10_SPI3_MISO         0x066a
#define GPIO_PIN_PG11_SPI3_MOSI         0x066b
#define GPIO_PIN_PG12_SPI3_NSS          0x066c

#define GPIO_PIN_PA6_QUADSPI_BK1_IO3    0x0a06
#define GPIO_PIN_PA7_QUADSPI_BK1_IO2    0x0a07
#define GPIO_PIN_PB0_QUADSPI_BK1_IO1    0x0a10
#define GPIO_PIN_PB1_QUADSPI_BK1_IO0    0x0a11
#define GPIO_PIN_PB10_QUADSPI_CLK       0x0a1a
#define GPIO_PIN_PB11_QUADSPI_BK1_NCS   0x0a1b
#define GPIO_PIN_PE10_QUADSPI_CLK       0x0a4a
#define GPIO_PIN_PE11_QUADSPI_BK1_NCS   0x0a4b
#define GPIO_PIN_PE12_QUADSPI_BK1_IO0   0x0a4c
#define GPIO_PIN_PE13_QUADSPI_BK1_IO1   0x0a4d
#define GPIO_PIN_PE14_QUADSPI_BK1_IO2   0x0a4e
#define GPIO_PIN_PE15_QUADSPI_BK1_IO3   0x0a4f

#define GPIO_PIN_PB8_SDMMC1_D4          0x0c18
#define GPIO_PIN_PB9_SDMMC1_D5          0x0c19
#define GPIO_PIN_PC6_SDMMC1_D6          0x0c26
#define GPIO_PIN_PC7_SDMMC1_D7          0x0c27
#define GPIO_PIN_PC8_SDMMC1_D0          0x0c28
#define GPIO_PIN_PC9_SDMMC1_D1          0x0c29
#define GPIO_PIN_PC10_SDMMC1_D2         0x0c2a
#define GPIO_PIN_PC11_SDMMC1_D3         0x0c2b
#define GPIO_PIN_PC12_SDMMC1_CK         0x0c2c
#define GPIO_PIN_PD2_SDMMC1_CMD         0x0c32

#define GPIO_PIN_PA0_SAI1_EXTCLK        0x0d00
#define GPIO_PIN_PA4_SAI1_FS_B          0x0d04
#define GPIO_PIN_PB3_SAI1_SCK_B         0x0d13
#define GPIO_PIN_PB4_SAI1_MCLK_B        0x0d14
#define GPIO_PIN_PB5_SAI1_SD_B          0x0d15
#define GPIO_PIN_PB6_SAI1_FS_B          0x0d16
#define GPIO_PIN_PB8_SAI1_MCLK_A        0x0d18
#define GPIO_PIN_PB9_SAI1_FS_A          0x0d19
#define GPIO_PIN_PB10_SAI1_SCK_A        0x0d1a
#define GPIO_PIN_PC3_SAI1_SD_A          0x0d23
#define GPIO_PIN_PD6_SAI1_SD_A          0x0d36
#define GPIO_PIN_PE2_SAI1_MCLK_A        0x0d42
#define GPIO_PIN_PE3_SAI1_SD_B          0x0d43
#define GPIO_PIN_PE4_SAI1_FS_A          0x0d44
#define GPIO_PIN_PE5_SAI1_SCK_A         0x0d45
#define GPIO_PIN_PE6_SAI1_SD_A          0x0d46
#define GPIO_PIN_PE7_SAI1_SD_B          0x0d47
#define GPIO_PIN_PE8_SAI1_SCK_B         0x0d48
#define GPIO_PIN_PE9_SAI1_FS_B          0x0d49
#define GPIO_PIN_PE10_SAI1_MCLK_B       0x0d4a
#define GPIO_PIN_PF6_SAI1_SD_B          0x0d56
#define GPIO_PIN_PF7_SAI1_MCLK_B        0x0d57
#define GPIO_PIN_PF8_SAI1_SCK_B         0x0d58
#define GPIO_PIN_PF9_SAI1_FS_B          0x0d59

#define GPIO_PIN_PA2_SAI2_EXTCLK        0x0d02
#define GPIO_PIN_PA15_SAI2_FS_B         0x0d0f
#define GPIO_PIN_PB12_SAI2_FS_A         0x0d1c
#define GPIO_PIN_PB13_SAI2_SCK_A        0x0d1d
#define GPIO_PIN_PB14_SAI2_MCLK_A       0x0d1e
#define GPIO_PIN_PB15_SAI2_SD_A         0x0d1f
#define GPIO_PIN_PC6_SAI2_MCLK_A        0x0d26
#define GPIO_PIN_PC7_SAI2_MCLK_B        0x0d27
#define GPIO_PIN_PC9_SAI2_EXTCLK        0x0d29
#define GPIO_PIN_PC10_SAI2_SCK_B        0x0d2a
#define GPIO_PIN_PC11_SAI2_MCLK_B       0x0d2b
#define GPIO_PIN_PC12_SAI2_SD_B         0x0d2c
#define GPIO_PIN_PD9_SAI2_MCLK_A        0x0d39
#define GPIO_PIN_PD10_SAI2_SCK_A        0x0d3a
#define GPIO_PIN_PD11_SAI2_SD_A         0x0d3b
#define GPIO_PIN_PD12_SAI2_FS_A         0x0d3c
#define GPIO_PIN_PG2_SAI2_SCK_B         0x0d62
#define GPIO_PIN_PG3_SAI2_FS_B          0x0d63
#define GPIO_PIN_PG4_SAI2_MCLK_B        0x0d64
#define GPIO_PIN_PG5_SAI2_SD_B          0x0d65
#define GPIO_PIN_PG9_SAI2_SCK_A         0x0d69
#define GPIO_PIN_PG10_SAI2_FS_A         0x0d6a
#define GPIO_PIN_PG11_SAI2_MCLK_A       0x0d6b
#define GPIO_PIN_PG12_SAI2_SD_A         0x0d6c

#define GPIO_PIN_PB1_DFSDM1_DATIN0      0x0611
#define GPIO_PIN_PB2_DFSDM1_CKIN0       0x0612
#define GPIO_PIN_PB6_DFSDM1_DATIN5      0x0616
#define GPIO_PIN_PB7_DFSDM1_CKIN5       0x0617
#define GPIO_PIN_PB8_DFSDM1_DATIN6      0x0618
#define GPIO_PIN_PB9_DFSDM1_CKIN6       0x0619
#define GPIO_PIN_PB10_DFSDM1_DATIN7     0x061a
#define GPIO_PIN_PB11_DFSDM1_CKIN7      0x061b
#define GPIO_PIN_PB12_DFSDM1_DATIN1     0x061c
#define GPIO_PIN_PB13_DFSDM1_CKIN1      0x061d
#define GPIO_PIN_PB14_DFSDM1_DATIN2     0x061e
#define GPIO_PIN_PB15_DFSDM1_CKIN2      0x061f
#define GPIO_PIN_PC0_DFSDM1_DATIN4      0x0620
#define GPIO_PIN_PC1_DFSDM1_CKIN4       0x0621
#define GPIO_PIN_PC2_DFSDM1_CKOUT       0x0622
#define GPIO_PIN_PC6_DFSDM1_CKIN3       0x0626
#define GPIO_PIN_PC7_DFSDM1_DATIN3      0x0627
#define GPIO_PIN_PD0_DFSDM1_DATIN7      0x0630
#define GPIO_PIN_PD1_DFSDM1_CKIN7       0x0631
#define GPIO_PIN_PD3_DFSDM1_DATIN0      0x0633
#define GPIO_PIN_PD4_DFSDM1_CKIN0       0x0634
#define GPIO_PIN_PD6_DFSDM1_DATIN1      0x0636
#define GPIO_PIN_PD7_DFSDM1_CKIN1       0x0637
#define GPIO_PIN_PE4_DFSDM1_DATIN3      0x0644
#define GPIO_PIN_PE5_DFSDM1_CKIN3       0x0645
#define GPIO_PIN_PE7_DFSDM1_DATIN2      0x0647
#define GPIO_PIN_PE8_DFSDM1_CKIN2       0x0648
#define GPIO_PIN_PE9_DFSDM1_CKOUT       0x0649
#define GPIO_PIN_PE10_DFSDM1_DATIN4     0x064a
#define GPIO_PIN_PE11_DFSDM1_CKIN4      0x064b
#define GPIO_PIN_PE12_DFSDM1_DATIN5     0x064c
#define GPIO_PIN_PE13_DFSDM1_CKIN5      0x064d
#define GPIO_PIN_PF13_DFSDM1_DATIN6     0x065d
#define GPIO_PIN_PF14_DFSDM1_CKIN6      0x065e

#define GPIO_PIN_PB12_SWPMI1_IO         0x0c1c
#define GPIO_PIN_PB13_SWPMI1_TX         0x0c1d
#define GPIO_PIN_PB14_SWPMI1_RX         0x0c1e
#define GPIO_PIN_PB15_SWPMI1_SUSPEND    0x0c1f

#define GPIO_PIN_PA8_OTG_FS_SOF         0x0a08
#define GPIO_PIN_PA10_OTG_FS_ID         0x0a0a
#define GPIO_PIN_PA11_OTG_FS_DM         0x0a0b
#define GPIO_PIN_PA12_OTG_FS_DP         0x0a0c
#define GPIO_PIN_PA13_OTG_FS_NOE        0x0a0d
#define GPIO_PIN_PC9_OTG_FS_NOE         0x0a29

#define GPIO_PIN_PA11_CAN1_RX           0x090b
#define GPIO_PIN_PA12_CAN1_TX           0x090c
#define GPIO_PIN_PB8_CAN1_RX            0x0918
#define GPIO_PIN_PB9_CAN1_TX            0x0919
#define GPIO_PIN_PD0_CAN1_RX            0x0930
#define GPIO_PIN_PD1_CAN1_TX            0x0931

#define GPIO_PIN_PA13_IR_OUT            0x010d
#define GPIO_PIN_PB9_IR_OUT             0x0119

#define GPIO_PIN_PA6_TIM1_BKIN          0x0106
#define GPIO_PIN_PA6_TIM1_BKIN_COMP2    0x0c06
#define GPIO_PIN_PA7_TIM1_CH1N          0x0107
#define GPIO_PIN_PA8_TIM1_CH1           0x0108
#define GPIO_PIN_PA9_TIM1_CH2           0x0109
#define GPIO_PIN_PA10_TIM1_CH3          0x010a
#define GPIO_PIN_PA11_TIM1_BKIN2        0x020b
#define GPIO_PIN_PA11_TIM1_BKIN2_COMP1  0x0c0b
#define GPIO_PIN_PA11_TIM1_CH4          0x010b
#define GPIO_PIN_PA12_TIM1_ETR          0x010c
#define GPIO_PIN_PB0_TIM1_CH2N          0x0110
#define GPIO_PIN_PB1_TIM1_CH3N          0x0111
#define GPIO_PIN_PB12_TIM1_BKIN         0x011c
#define GPIO_PIN_PB12_TIM1_BKIN_COMP2   0x031c
#define GPIO_PIN_PB13_TIM1_CH1N         0x011d
#define GPIO_PIN_PB14_TIM1_CH2N         0x011e
#define GPIO_PIN_PB15_TIM1_CH3N         0x011f
#define GPIO_PIN_PE7_TIM1_ETR           0x0147
#define GPIO_PIN_PE8_TIM1_CH1N          0x0148
#define GPIO_PIN_PE9_TIM1_CH1           0x0149
#define GPIO_PIN_PE10_TIM1_CH2N         0x014a
#define GPIO_PIN_PE11_TIM1_CH2          0x014b
#define GPIO_PIN_PE12_TIM1_CH3N         0x014c
#define GPIO_PIN_PE13_TIM1_CH3          0x014d
#define GPIO_PIN_PE14_TIM1_BKIN2        0x024e
#define GPIO_PIN_PE14_TIM1_BKIN2_COMP2  0x034e
#define GPIO_PIN_PE14_TIM1_CH4          0x014e
#define GPIO_PIN_PE15_TIM1_BKIN         0x014f
#define GPIO_PIN_PE15_TIM1_BKIN_COMP1   0x034f

#define GPIO_PIN_PA0_TIM2_CH1           0x0100
#define GPIO_PIN_PA0_TIM2_ETR           0x0e00
#define GPIO_PIN_PA1_TIM2_CH2           0x0101
#define GPIO_PIN_PA2_TIM2_CH3           0x0102
#define GPIO_PIN_PA3_TIM2_CH4           0x0103
#define GPIO_PIN_PA5_TIM2_CH1           0x0105
#define GPIO_PIN_PA5_TIM2_ETR           0x0205
#define GPIO_PIN_PA15_TIM2_CH1          0x010f
#define GPIO_PIN_PA15_TIM2_ETR          0x020f
#define GPIO_PIN_PB3_TIM2_CH2           0x0113
#define GPIO_PIN_PB10_TIM2_CH3          0x011a
#define GPIO_PIN_PB11_TIM2_CH4          0x011b

#define GPIO_PIN_PA6_TIM3_CH1           0x0206
#define GPIO_PIN_PA7_TIM3_CH2           0x0207
#define GPIO_PIN_PB0_TIM3_CH3           0x0210
#define GPIO_PIN_PB1_TIM3_CH4           0x0211
#define GPIO_PIN_PB4_TIM3_CH1           0x0214
#define GPIO_PIN_PB5_TIM3_CH2           0x0215
#define GPIO_PIN_PC6_TIM3_CH1           0x0226
#define GPIO_PIN_PC7_TIM3_CH2           0x0227
#define GPIO_PIN_PC8_TIM3_CH3           0x0228
#define GPIO_PIN_PC9_TIM3_CH4           0x0229
#define GPIO_PIN_PD2_TIM3_ETR           0x0232
#define GPIO_PIN_PE2_TIM3_ETR           0x0242
#define GPIO_PIN_PE3_TIM3_CH1           0x0243
#define GPIO_PIN_PE4_TIM3_CH2           0x0244
#define GPIO_PIN_PE5_TIM3_CH3           0x0245
#define GPIO_PIN_PE6_TIM3_CH4           0x0246

#define GPIO_PIN_PB6_TIM4_CH1           0x0216
#define GPIO_PIN_PB7_TIM4_CH2           0x0217
#define GPIO_PIN_PB8_TIM4_CH3           0x0218
#define GPIO_PIN_PB9_TIM4_CH4           0x0219
#define GPIO_PIN_PD12_TIM4_CH1          0x023c
#define GPIO_PIN_PD13_TIM4_CH2          0x023d
#define GPIO_PIN_PD14_TIM4_CH3          0x023e
#define GPIO_PIN_PD15_TIM4_CH4          0x023f
#define GPIO_PIN_PE0_TIM4_ETR           0x0240

#define GPIO_PIN_PA0_TIM5_CH1           0x0200
#define GPIO_PIN_PA1_TIM5_CH2           0x0201
#define GPIO_PIN_PA2_TIM5_CH3           0x0202
#define GPIO_PIN_PA3_TIM5_CH4           0x0203
#define GPIO_PIN_PF6_TIM5_CH1           0x0256
#define GPIO_PIN_PF6_TIM5_ETR           0x0156
#define GPIO_PIN_PF7_TIM5_CH2           0x0257
#define GPIO_PIN_PF8_TIM5_CH3           0x0258
#define GPIO_PIN_PF9_TIM5_CH4           0x0259

#define GPIO_PIN_PA0_TIM8_ETR           0x0300
#define GPIO_PIN_PA5_TIM8_CH1N          0x0305
#define GPIO_PIN_PA6_TIM8_BKIN          0x0306
#define GPIO_PIN_PA6_TIM8_BKIN_COMP2    0x0d06
#define GPIO_PIN_PA7_TIM8_CH1N          0x0307
#define GPIO_PIN_PB0_TIM8_CH2N          0x0310
#define GPIO_PIN_PB1_TIM8_CH3N          0x0311
#define GPIO_PIN_PB6_TIM8_BKIN2         0x0316
#define GPIO_PIN_PB6_TIM8_BKIN2_COMP2   0x0c16
#define GPIO_PIN_PB7_TIM8_BKIN          0x0317
#define GPIO_PIN_PB7_TIM8_BKIN_COMP1    0x0d17
#define GPIO_PIN_PB14_TIM8_CH2N         0x031e
#define GPIO_PIN_PB15_TIM8_CH3N         0x031f
#define GPIO_PIN_PC6_TIM8_CH1           0x0326
#define GPIO_PIN_PC7_TIM8_CH2           0x0327
#define GPIO_PIN_PC8_TIM8_CH3           0x0328
#define GPIO_PIN_PC9_TIM8_BKIN2         0x0129
#define GPIO_PIN_PC9_TIM8_BKIN2_COMP1   0x0e29
#define GPIO_PIN_PC9_TIM8_CH4           0x0329

#define GPIO_PIN_PA1_TIM15_CH1N         0x0e01
#define GPIO_PIN_PA2_TIM15_CH1          0x0e02
#define GPIO_PIN_PA3_TIM15_CH2          0x0e03
#define GPIO_PIN_PA9_TIM15_BKIN         0x0e09
#define GPIO_PIN_PB12_TIM15_BKIN        0x0e1c
#define GPIO_PIN_PB13_TIM15_CH1N        0x0e1d
#define GPIO_PIN_PB14_TIM15_CH1         0x0e1e
#define GPIO_PIN_PB15_TIM15_CH2         0x0e1f
#define GPIO_PIN_PF9_TIM15_CH1          0x0e59
#define GPIO_PIN_PF10_TIM15_CH2         0x0e5a
#define GPIO_PIN_PG9_TIM15_CH1N         0x0e69
#define GPIO_PIN_PG10_TIM15_CH1         0x0e6a
#define GPIO_PIN_PG11_TIM15_CH2         0x0e6b

#define GPIO_PIN_PA6_TIM16_CH1          0x0e06
#define GPIO_PIN_PB5_TIM16_BKIN         0x0e15
#define GPIO_PIN_PB6_TIM16_CH1N         0x0e16
#define GPIO_PIN_PB8_TIM16_CH1          0x0e18
#define GPIO_PIN_PE0_TIM16_CH1          0x0e40

#define GPIO_PIN_PA7_TIM17_CH1          0x0e07
#define GPIO_PIN_PA10_TIM17_BKIN        0x0e0a
#define GPIO_PIN_PB4_TIM17_BKIN         0x0e14
#define GPIO_PIN_PB7_TIM17_CH1N         0x0e17
#define GPIO_PIN_PB9_TIM17_CH1          0x0e19
#define GPIO_PIN_PE1_TIM17_CH1          0x0e41

#define GPIO_PIN_PB2_LPTIM1_OUT         0x0112
#define GPIO_PIN_PB5_LPTIM1_IN1         0x0115
#define GPIO_PIN_PB6_LPTIM1_ETR         0x0116
#define GPIO_PIN_PB7_LPTIM1_IN2         0x0117
#define GPIO_PIN_PC0_LPTIM1_IN1         0x0120
#define GPIO_PIN_PC1_LPTIM1_OUT         0x0121
#define GPIO_PIN_PC2_LPTIM1_IN2         0x0122
#define GPIO_PIN_PC3_LPTIM1_ETR         0x0123
#define GPIO_PIN_PG10_LPTIM1_IN1        0x016a
#define GPIO_PIN_PG11_LPTIM1_IN2        0x016b
#define GPIO_PIN_PG12_LPTIM1_ETR        0x016c
#define GPIO_PIN_PG15_LPTIM1_OUT        0x016f

#define GPIO_PIN_PA4_LPTIM2_OUT         0x0e04
#define GPIO_PIN_PA5_LPTIM2_ETR         0x0e05
#define GPIO_PIN_PA8_LPTIM2_OUT         0x0e08
#define GPIO_PIN_PB1_LPTIM2_IN1         0x0e11
#define GPIO_PIN_PC0_LPTIM2_IN1         0x0e20
#define GPIO_PIN_PC3_LPTIM2_ETR         0x0e23
#define GPIO_PIN_PD11_LPTIM2_ETR        0x0e3b
#define GPIO_PIN_PD12_LPTIM2_IN1        0x0e3c
#define GPIO_PIN_PD13_LPTIM2_OUT        0x0e3d

#define GPIO_PIN_PB0_COMP1_OUT          0x0c10
#define GPIO_PIN_PB10_COMP1_OUT         0x0c1a

#define GPIO_PIN_PB5_COMP2_OUT          0x0c15
#define GPIO_PIN_PB11_COMP2_OUT         0x0c1b

#define GPIO_PIN_PA15_TSC_G3_IO1        0x090f
#define GPIO_PIN_PB4_TSC_G2_IO1         0x0914
#define GPIO_PIN_PB5_TSC_G2_IO2         0x0915
#define GPIO_PIN_PB6_TSC_G2_IO3         0x0916
#define GPIO_PIN_PB7_TSC_G2_IO4         0x0917
#define GPIO_PIN_PB12_TSC_G1_IO1        0x091c
#define GPIO_PIN_PB13_TSC_G1_IO2        0x091d
#define GPIO_PIN_PB14_TSC_G1_IO3        0x091e
#define GPIO_PIN_PB15_TSC_G1_IO4        0x091f
#define GPIO_PIN_PC6_TSC_G4_IO1         0x0926
#define GPIO_PIN_PC7_TSC_G4_IO2         0x0927
#define GPIO_PIN_PC8_TSC_G4_IO3         0x0928
#define GPIO_PIN_PC9_TSC_G4_IO4         0x0929
#define GPIO_PIN_PC10_TSC_G3_IO2        0x092a
#define GPIO_PIN_PC11_TSC_G3_IO3        0x092b
#define GPIO_PIN_PC12_TSC_G3_IO4        0x092c
#define GPIO_PIN_PD2_TSC_SYNC           0x0932
#define GPIO_PIN_PD10_TSC_G6_IO1        0x093a
#define GPIO_PIN_PD11_TSC_G6_IO2        0x093b
#define GPIO_PIN_PD12_TSC_G6_IO3        0x093c
#define GPIO_PIN_PD13_TSC_G6_IO4        0x093d
#define GPIO_PIN_PE2_TSC_G7_IO1         0x0942
#define GPIO_PIN_PE3_TSC_G7_IO2         0x0943
#define GPIO_PIN_PE4_TSC_G7_IO3         0x0944
#define GPIO_PIN_PE5_TSC_G7_IO4         0x0945
#define GPIO_PIN_PE10_TSC_G5_IO1        0x094a
#define GPIO_PIN_PE11_TSC_G5_IO2        0x094b
#define GPIO_PIN_PE12_TSC_G5_IO3        0x094c
#define GPIO_PIN_PE13_TSC_G5_IO4        0x094d
#define GPIO_PIN_PF14_TSC_G8_IO1        0x095e
#define GPIO_PIN_PF15_TSC_G8_IO2        0x095f
#define GPIO_PIN_PG0_TSC_G8_IO3         0x0960
#define GPIO_PIN_PG1_TSC_G8_IO4         0x0961

#define GPIO_PIN_PA1_LCD_SEG0           0x0b01
#define GPIO_PIN_PA2_LCD_SEG1           0x0b02
#define GPIO_PIN_PA3_LCD_SEG2           0x0b03
#define GPIO_PIN_PA6_LCD_SEG3           0x0b06
#define GPIO_PIN_PA7_LCD_SEG4           0x0b07
#define GPIO_PIN_PA8_LCD_COM0           0x0b08
#define GPIO_PIN_PA9_LCD_COM1           0x0b09
#define GPIO_PIN_PA10_LCD_COM2          0x0b0a
#define GPIO_PIN_PA15_LCD_SEG17         0x0b0f
#define GPIO_PIN_PB0_LCD_SEG5           0x0b10
#define GPIO_PIN_PB1_LCD_SEG6           0x0b11
#define GPIO_PIN_PB3_LCD_SEG7           0x0b13
#define GPIO_PIN_PB4_LCD_SEG8           0x0b14
#define GPIO_PIN_PB5_LCD_SEG9           0x0b15
#define GPIO_PIN_PB7_LCD_SEG21          0x0b17
#define GPIO_PIN_PB8_LCD_SEG16          0x0b18
#define GPIO_PIN_PB9_LCD_COM3           0x0b19
#define GPIO_PIN_PB10_LCD_SEG10         0x0b1a
#define GPIO_PIN_PB11_LCD_SEG11         0x0b1b
#define GPIO_PIN_PB12_LCD_SEG12         0x0b1c
#define GPIO_PIN_PB13_LCD_SEG13         0x0b1d
#define GPIO_PIN_PB14_LCD_SEG14         0x0b1e
#define GPIO_PIN_PB15_LCD_SEG15         0x0b1f
#define GPIO_PIN_PC0_LCD_SEG18          0x0b20
#define GPIO_PIN_PC1_LCD_SEG19          0x0b21
#define GPIO_PIN_PC2_LCD_SEG20          0x0b22
#define GPIO_PIN_PC3_LCD_VLCD           0x0b23
#define GPIO_PIN_PC4_LCD_SEG22          0x0b24
#define GPIO_PIN_PC5_LCD_SEG23          0x0b25
#define GPIO_PIN_PC6_LCD_SEG24          0x0b26
#define GPIO_PIN_PC7_LCD_SEG25          0x0b27
#define GPIO_PIN_PC8_LCD_SEG26          0x0b28
#define GPIO_PIN_PC9_LCD_SEG27          0x0b29
#define GPIO_PIN_PC10_LCD_COM4          0x0b2a
#define GPIO_PIN_PC10_LCD_SEG28         0x0b2a
#define GPIO_PIN_PC10_LCD_SEG40         0x0b2a
#define GPIO_PIN_PC11_LCD_COM5          0x0b2b
#define GPIO_PIN_PC11_LCD_SEG29         0x0b2b
#define GPIO_PIN_PC11_LCD_SEG41         0x0b2b
#define GPIO_PIN_PC12_LCD_COM6          0x0b2c
#define GPIO_PIN_PC12_LCD_SEG30         0x0b2c
#define GPIO_PIN_PC12_LCD_SEG42         0x0b2c
#define GPIO_PIN_PD2_LCD_COM7           0x0b32
#define GPIO_PIN_PD2_LCD_SEG31          0x0b32
#define GPIO_PIN_PD2_LCD_SEG43          0x0b32
#define GPIO_PIN_PD8_LCD_SEG28          0x0b38
#define GPIO_PIN_PD9_LCD_SEG29          0x0b39
#define GPIO_PIN_PD10_LCD_SEG30         0x0b3a
#define GPIO_PIN_PD11_LCD_SEG31         0x0b3b
#define GPIO_PIN_PD12_LCD_SEG32         0x0b3c
#define GPIO_PIN_PD13_LCD_SEG33         0x0b3d
#define GPIO_PIN_PD14_LCD_SEG34         0x0b3e
#define GPIO_PIN_PD15_LCD_SEG35         0x0b3f
#define GPIO_PIN_PE0_LCD_SEG36          0x0b40
#define GPIO_PIN_PE1_LCD_SEG37          0x0b41
#define GPIO_PIN_PE2_LCD_SEG38          0x0b42
#define GPIO_PIN_PE3_LCD_SEG39          0x0b43

#define GPIO_PIN_PB7_FMC_NL             0x0c17
#define GPIO_PIN_PD0_FMC_D2             0x0c30
#define GPIO_PIN_PD1_FMC_D3             0x0c31
#define GPIO_PIN_PD3_FMC_CLK            0x0c33
#define GPIO_PIN_PD4_FMC_NOE            0x0c34
#define GPIO_PIN_PD5_FMC_NWE            0x0c35
#define GPIO_PIN_PD6_FMC_NWAIT          0x0c36
#define GPIO_PIN_PD7_FMC_NE1            0x0c37
#define GPIO_PIN_PD8_FMC_D13            0x0c38
#define GPIO_PIN_PD9_FMC_D14            0x0c39
#define GPIO_PIN_PD10_FMC_D15           0x0c3a
#define GPIO_PIN_PD11_FMC_A16           0x0c3b
#define GPIO_PIN_PD12_FMC_A17           0x0c3c
#define GPIO_PIN_PD13_FMC_A18           0x0c3d
#define GPIO_PIN_PD14_FMC_D0            0x0c3e
#define GPIO_PIN_PD15_FMC_D1            0x0c3f
#define GPIO_PIN_PE0_FMC_NBL0           0x0c40
#define GPIO_PIN_PE1_FMC_NBL1           0x0c41
#define GPIO_PIN_PE2_FMC_A23            0x0c42
#define GPIO_PIN_PE3_FMC_A19            0x0c43
#define GPIO_PIN_PE4_FMC_A20            0x0c44
#define GPIO_PIN_PE5_FMC_A21            0x0c45
#define GPIO_PIN_PE6_FMC_A22            0x0c46
#define GPIO_PIN_PE7_FMC_D4             0x0c47
#define GPIO_PIN_PE8_FMC_D5             0x0c48
#define GPIO_PIN_PE9_FMC_D6             0x0c49
#define GPIO_PIN_PE10_FMC_D7            0x0c4a
#define GPIO_PIN_PE11_FMC_D8            0x0c4b
#define GPIO_PIN_PE12_FMC_D9            0x0c4c
#define GPIO_PIN_PE13_FMC_D10           0x0c4d
#define GPIO_PIN_PE14_FMC_D11           0x0c4e
#define GPIO_PIN_PE15_FMC_D12           0x0c4f
#define GPIO_PIN_PF0_FMC_A0             0x0c50
#define GPIO_PIN_PF1_FMC_A1             0x0c51
#define GPIO_PIN_PF2_FMC_A2             0x0c52
#define GPIO_PIN_PF3_FMC_A3             0x0c53
#define GPIO_PIN_PF4_FMC_A4             0x0c54
#define GPIO_PIN_PF5_FMC_A5             0x0c55
#define GPIO_PIN_PF12_FMC_A6            0x0c5c
#define GPIO_PIN_PF13_FMC_A7            0x0c5d
#define GPIO_PIN_PF14_FMC_A8            0x0c5e
#define GPIO_PIN_PF15_FMC_A9            0x0c5f
#define GPIO_PIN_PG0_FMC_A10            0x0c60
#define GPIO_PIN_PG1_FMC_A11            0x0c61
#define GPIO_PIN_PG2_FMC_A12            0x0c62
#define GPIO_PIN_PG3_FMC_A13            0x0c63
#define GPIO_PIN_PG4_FMC_A14            0x0c64
#define GPIO_PIN_PG5_FMC_A15            0x0c65
#define GPIO_PIN_PG7_FMC_INT            0x0c67
#define GPIO_PIN_PG9_FMC_NCE            0x0c69
#define GPIO_PIN_PG9_FMC_NE2            0x0c69
#define GPIO_PIN_PG10_FMC_NE3           0x0c6a
#define GPIO_PIN_PG12_FMC_NE4           0x0c6c
#define GPIO_PIN_PG13_FMC_A24           0x0c6d
#define GPIO_PIN_PG14_FMC_A25           0x0c6e

#else
#error "Only STM32L476xx currently supported"
#endif

uint32_t gpio_pin_read(uint32_t pin);

void gpio_pin_write(uint32_t pin, uint32_t data);

void gpio_pin_configure(uint32_t pin, uint32_t mode);

void gpio_pin_input(uint32_t pin);

void gpio_pin_output(uint32_t pin);

void gpio_pin_alternate(uint32_t pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H_ */
