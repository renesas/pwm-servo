/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define ARDUINO_A0 (BSP_IO_PORT_00_PIN_00)
#define ARDUINO_A1 (BSP_IO_PORT_00_PIN_01)
#define ARDUINO_A2 (BSP_IO_PORT_00_PIN_02)
#define ARDUINO_A3 (BSP_IO_PORT_00_PIN_12)
#define ARDUINO_A4 (BSP_IO_PORT_00_PIN_13)
#define ARDUINO_A5 (BSP_IO_PORT_00_PIN_14)
#define PMOD1_IRQ7 (BSP_IO_PORT_00_PIN_15)
#define ARDUINO_D12_MISO_PMOD1_MISO (BSP_IO_PORT_01_PIN_00)
#define ARDUINO_D11_MOSI_PMOD1_MOSI (BSP_IO_PORT_01_PIN_01)
#define ARDUINO_D13_SCK_PMOD1_SCK (BSP_IO_PORT_01_PIN_02)
#define ARDUINO_D10_SS_PMOD1_SS (BSP_IO_PORT_01_PIN_03)
#define ARDUINO_D9 (BSP_IO_PORT_01_PIN_04)
#define ARDUINO_D1_TX (BSP_IO_PORT_01_PIN_09)
#define ARDUINO_D0_RX (BSP_IO_PORT_01_PIN_10)
#define ARDUINO_D3 (BSP_IO_PORT_01_PIN_11)
#define ARDUINO_D8 (BSP_IO_PORT_01_PIN_12)
#define SW1 (BSP_IO_PORT_02_PIN_00)
#define ARDUINO_D7_PMOD2_GPIO9 (BSP_IO_PORT_02_PIN_06)
#define PMOD2_GPIO8 (BSP_IO_PORT_02_PIN_07)
#define PMOD2_GPIO7 (BSP_IO_PORT_02_PIN_08)
#define PMOD2_RESET (BSP_IO_PORT_02_PIN_12)
#define LED1 (BSP_IO_PORT_02_PIN_13)
#define ARDUINO_D4_PMOD2_GPIO10 (BSP_IO_PORT_03_PIN_01)
#define ARDUINO_D5 (BSP_IO_PORT_03_PIN_02)
#define ARDUINO_SCL_PMOD1_SCL_PMOD2_SCL (BSP_IO_PORT_04_PIN_00)
#define ARDUINO_SDA_PMOD1_SDA_PMOD2_SDA (BSP_IO_PORT_04_PIN_01)
#define PMOD1_RTS (BSP_IO_PORT_04_PIN_07)
#define PMOD2_INT (BSP_IO_PORT_04_PIN_08)
#define ARDUINO_D2 (BSP_IO_PORT_04_PIN_09)
#define ARDUINO_D6 (BSP_IO_PORT_05_PIN_00)
#define PMOD1_GPIO10 (BSP_IO_PORT_09_PIN_13)
#define LED2_PMOD1_GPIO9 (BSP_IO_PORT_09_PIN_14)
#define PMOD1_RESET (BSP_IO_PORT_09_PIN_15)

extern const ioport_cfg_t g_bsp_pin_cfg; /* RA2E3 FPB */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
