/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define BUTTON2 (BSP_IO_PORT_00_PIN_00)
#define BUTTON1 (BSP_IO_PORT_00_PIN_01)
#define LED1 (BSP_IO_PORT_00_PIN_02) /* Green, Hi: Turn on */
#define ARDUINO_A5 (BSP_IO_PORT_00_PIN_08)
#define PMOD1_GPIO10_ARDUINO_A4 (BSP_IO_PORT_00_PIN_09)
#define ARDUINO_AREF (BSP_IO_PORT_00_PIN_10)
#define PMOD1_GPIO9_ARDUINO_A3 (BSP_IO_PORT_00_PIN_12)
#define PMOD1_GPIO8_ARDUINO_A2 (BSP_IO_PORT_00_PIN_13)
#define ARDUINO_A1 (BSP_IO_PORT_00_PIN_14)
#define ARDUINO_A0 (BSP_IO_PORT_00_PIN_15)
#define PMOD1_MISO_RXD_ARDUINO_D4 (BSP_IO_PORT_01_PIN_00)
#define PMOD1_MOSI_TXD_ARDUINO_D5 (BSP_IO_PORT_01_PIN_01)
#define PMOD1_SCK (BSP_IO_PORT_01_PIN_02)
#define PMOD1_CS_ARDUINO_D7 (BSP_IO_PORT_01_PIN_03) /* PMOD1_INT */
#define LED2 (BSP_IO_PORT_01_PIN_04) /* Green, Hi: Turn on */
#define VCOM_RXD (BSP_IO_PORT_01_PIN_05)
#define VCOM_TXD (BSP_IO_PORT_01_PIN_06)
#define ARDUINO_D8 (BSP_IO_PORT_01_PIN_09) /* PMOD1_SDA */
#define ARDUINO_D10 (BSP_IO_PORT_01_PIN_10) /* PMOD1_SCL */
#define ARDUINO_D2 (BSP_IO_PORT_01_PIN_11)
#define TSCAP (BSP_IO_PORT_01_PIN_12)
#define SW1 (BSP_IO_PORT_02_PIN_00)
#define PMOD1_INT_ARDUINO_D3 (BSP_IO_PORT_02_PIN_01)
#define PMOD2_GPIO7 (BSP_IO_PORT_02_PIN_06) /* PMOD2_INT */
#define ARDUINO_RX (BSP_IO_PORT_02_PIN_07)
#define ARDUINO_TX (BSP_IO_PORT_02_PIN_08)
#define ARDUINO_MISO (BSP_IO_PORT_02_PIN_12) /* PMOD2_MISO_RXD */
#define ARDUINO_MOSI (BSP_IO_PORT_02_PIN_13) /* PMOD2_MOSI_TXD */
#define PMOD2_GPIO10_ARDUINO_D9 (BSP_IO_PORT_03_PIN_01)
#define PMOD2_GPIO9 (BSP_IO_PORT_03_PIN_02)
#define LED6 (BSP_IO_PORT_04_PIN_00) /* Green, Lo: Turn on */
#define LED5 (BSP_IO_PORT_04_PIN_01) /* Green, Lo: Turn on */
#define PMOD2_SDA_ARDUINO_SCK (BSP_IO_PORT_04_PIN_07) /* PMOD2_SCK */
#define PMOD2_SCL (BSP_IO_PORT_04_PIN_08)
#define PMOD2_INT (BSP_IO_PORT_04_PIN_09)
#define ARDUINO_D6 (BSP_IO_PORT_05_PIN_00)
#define ARDUINO_SDA (BSP_IO_PORT_09_PIN_13)
#define ARDUINO_SCL (BSP_IO_PORT_09_PIN_14)
#define PMOD2_GPIO8 (BSP_IO_PORT_09_PIN_15)
                                
#define PIN_SCLA0 (BSP_IO_PORT_09_PIN_14)
#define CFG_SCLA0 ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_IICA1)
                                
#define PIN_SDAA0 (BSP_IO_PORT_09_PIN_13)
#define CFG_SDAA0 ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_IICA1)

extern const ioport_cfg_t g_bsp_pin_cfg; /* FPB-RA0L1 */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
