#ifndef _DEFS_H
#define _DEFS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "bsp_common.h"

typedef int IRQn_Type;
typedef int bsp_io_port_t;
typedef int bsp_io_port_pin_t;

/** Levels that can be set and read for individual pins */
typedef enum e_bsp_io_level
{
    BSP_IO_LEVEL_LOW = 0,              ///< Low
    BSP_IO_LEVEL_HIGH                  ///< High
} bsp_io_level_t;

typedef enum e_fsp_err
{
    FSP_SUCCESS = 0,

    FSP_ERR_ASSERTION        = 1,                           ///< A critical assertion has failed
    FSP_ERR_INVALID_POINTER  = 2,                           ///< Pointer points to invalid memory location
    FSP_ERR_INVALID_ARGUMENT = 3,                           ///< Invalid input parameter
    FSP_ERR_INVALID_CHANNEL  = 4,                           ///< Selected channel does not exist
    FSP_ERR_INVALID_MODE     = 5,                           ///< Unsupported or incorrect mode
    FSP_ERR_UNSUPPORTED      = 6,                           ///< Selected mode not supported by this API
    FSP_ERR_NOT_OPEN         = 7,                           ///< Requested channel is not configured or API not open
    FSP_ERR_IN_USE           = 8,                           ///< Channel/peripheral is running/busy
    FSP_ERR_OUT_OF_MEMORY    = 9,                           ///< Allocate more memory in the driver's cfg.h
    FSP_ERR_HW_LOCKED        = 10,                          ///< Hardware is locked
    FSP_ERR_IRQ_BSP_DISABLED = 11,                          ///< IRQ not enabled in BSP
    FSP_ERR_OVERFLOW         = 12,                          ///< Hardware overflow
    FSP_ERR_UNDERFLOW        = 13,                          ///< Hardware underflow
    FSP_ERR_ALREADY_OPEN     = 14,                          ///< Requested channel is already open in a different
                                                            ///< configuration
    FSP_ERR_APPROXIMATION         = 15,                     ///< Could not set value to exact result
    FSP_ERR_CLAMPED               = 16,                     ///< Value had to be limited for some reason
    FSP_ERR_INVALID_RATE          = 17,                     ///< Selected rate could not be met
    FSP_ERR_ABORTED               = 18,                     ///< An operation was aborted
    FSP_ERR_NOT_ENABLED           = 19,                     ///< Requested operation is not enabled
    FSP_ERR_TIMEOUT               = 20,                     ///< Timeout error
    FSP_ERR_INVALID_BLOCKS        = 21,                     ///< Invalid number of blocks supplied
    FSP_ERR_INVALID_ADDRESS       = 22,                     ///< Invalid address supplied
    FSP_ERR_INVALID_SIZE          = 23,                     ///< Invalid size/length supplied for operation
    FSP_ERR_WRITE_FAILED          = 24,                     ///< Write operation failed
    FSP_ERR_ERASE_FAILED          = 25,                     ///< Erase operation failed
    FSP_ERR_INVALID_CALL          = 26,                     ///< Invalid function call is made
    FSP_ERR_INVALID_HW_CONDITION  = 27,                     ///< Detected hardware is in invalid condition
    FSP_ERR_INVALID_FACTORY_FLASH = 28,                     ///< Factory flash is not available on this MCU
    FSP_ERR_INVALID_STATE         = 30,                     ///< API or command not valid in the current state
    FSP_ERR_NOT_ERASED            = 31,                     ///< Erase verification failed
    FSP_ERR_SECTOR_RELEASE_FAILED = 32,                     ///< Sector release failed
    FSP_ERR_NOT_INITIALIZED       = 33,                     ///< Required initialization not complete
    FSP_ERR_NOT_FOUND             = 34,                     ///< The requested item could not be found
    FSP_ERR_NO_CALLBACK_MEMORY    = 35,                     ///< Non-secure callback memory not provided for non-secure
                                                            ///< callback
    FSP_ERR_BUFFER_EMPTY = 36,                              ///< No data available in buffer
    FSP_ERR_INVALID_DATA = 37,                              ///< Accuracy of data is not guaranteed

    /* Start of RTOS only error codes */
    FSP_ERR_INTERNAL     = 100,                             ///< Internal error
    FSP_ERR_WAIT_ABORTED = 101,                             ///< Wait aborted

    /* Start of UART specific */
    FSP_ERR_FRAMING            = 200,                       ///< Framing error occurs
    FSP_ERR_BREAK_DETECT       = 201,                       ///< Break signal detects
    FSP_ERR_PARITY             = 202,                       ///< Parity error occurs
    FSP_ERR_RXBUF_OVERFLOW     = 203,                       ///< Receive queue overflow
    FSP_ERR_QUEUE_UNAVAILABLE  = 204,                       ///< Can't open s/w queue
    FSP_ERR_INSUFFICIENT_SPACE = 205,                       ///< Not enough space in transmission circular buffer
    FSP_ERR_INSUFFICIENT_DATA  = 206,                       ///< Not enough data in receive circular buffer

    /* Start of SPI specific */
    FSP_ERR_TRANSFER_ABORTED = 300,                         ///< The data transfer was aborted.
    FSP_ERR_MODE_FAULT       = 301,                         ///< Mode fault error.
    FSP_ERR_READ_OVERFLOW    = 302,                         ///< Read overflow.
    FSP_ERR_SPI_PARITY       = 303,                         ///< Parity error.
    FSP_ERR_OVERRUN          = 304,                         ///< Overrun error.

    /* Start of CGC Specific */
    FSP_ERR_CLOCK_INACTIVE = 400,                           ///< Inactive clock specified as system clock.
    FSP_ERR_CLOCK_ACTIVE   = 401,                           ///< Active clock source cannot be modified without stopping
                                                            ///< first.
    FSP_ERR_NOT_STABILIZED   = 403,                         ///< Clock has not stabilized after its been turned on/off
    FSP_ERR_PLL_SRC_INACTIVE = 404,                         ///< PLL initialization attempted when PLL source is turned
                                                            ///< off
    FSP_ERR_OSC_STOP_DET_ENABLED = 405,                     ///< Illegal attempt to stop LOCO when Oscillation stop is
                                                            ///< enabled
    FSP_ERR_OSC_STOP_DETECTED     = 406,                    ///< The Oscillation stop detection status flag is set
    FSP_ERR_OSC_STOP_CLOCK_ACTIVE = 407,                    ///< Attempt to clear Oscillation Stop Detect Status with
                                                            ///< PLL/MAIN_OSC active
    FSP_ERR_CLKOUT_EXCEEDED = 408,                          ///< Output on target output clock pin exceeds maximum
                                                            ///< supported limit
    FSP_ERR_USB_MODULE_ENABLED = 409,                       ///< USB clock configure request with USB Module enabled
    FSP_ERR_HARDWARE_TIMEOUT   = 410,                       ///< A register read or write timed out
    FSP_ERR_LOW_VOLTAGE_MODE   = 411,                       ///< Invalid clock setting attempted in low voltage mode

    /* Start of FLASH Specific */
    FSP_ERR_PE_FAILURE             = 500,                   ///< Unable to enter Programming mode.
    FSP_ERR_CMD_LOCKED             = 501,                   ///< Peripheral in command locked state
    FSP_ERR_FCLK                   = 502,                   ///< FCLK must be >= 4 MHz
    FSP_ERR_INVALID_LINKED_ADDRESS = 503,                   ///< Function or data are linked at an invalid region of
                                                            ///< memory
    FSP_ERR_BLANK_CHECK_FAILED = 504,                       ///< Blank check operation failed
    FSP_ERR_HUK_ZEROIZATION    = 505,                       ///< W-HUK zeroization is in progress

    /* Start of CAC Specific */
    FSP_ERR_INVALID_CAC_REF_CLOCK = 600,                    ///< Measured clock rate < reference clock rate

    /* Start of IIRFA Specific */
    FSP_ERR_INVALID_RESULT = 700,                           ///< The result of one or more calculations was +/-
                                                            ///< infinity.

    /* Start of GLCD Specific */
    FSP_ERR_CLOCK_GENERATION           = 1000,              ///< Clock cannot be specified as system clock
    FSP_ERR_INVALID_TIMING_SETTING     = 1001,              ///< Invalid timing parameter
    FSP_ERR_INVALID_LAYER_SETTING      = 1002,              ///< Invalid layer parameter
    FSP_ERR_INVALID_ALIGNMENT          = 1003,              ///< Invalid memory alignment found
    FSP_ERR_INVALID_GAMMA_SETTING      = 1004,              ///< Invalid gamma correction parameter
    FSP_ERR_INVALID_LAYER_FORMAT       = 1005,              ///< Invalid color format in layer
    FSP_ERR_INVALID_UPDATE_TIMING      = 1006,              ///< Invalid timing for register update
    FSP_ERR_INVALID_CLUT_ACCESS        = 1007,              ///< Invalid access to CLUT entry
    FSP_ERR_INVALID_FADE_SETTING       = 1008,              ///< Invalid fade-in/fade-out setting
    FSP_ERR_INVALID_BRIGHTNESS_SETTING = 1009,              ///< Invalid gamma correction parameter

    /* Start of JPEG Specific */
    FSP_ERR_JPEG_ERR                      = 1100,           ///< JPEG error
    FSP_ERR_JPEG_SOI_NOT_DETECTED         = 1101,           ///< SOI not detected until EOI detected.
    FSP_ERR_JPEG_SOF1_TO_SOFF_DETECTED    = 1102,           ///< SOF1 to SOFF detected.
    FSP_ERR_JPEG_UNSUPPORTED_PIXEL_FORMAT = 1103,           ///< Unprovided pixel format detected.
    FSP_ERR_JPEG_SOF_ACCURACY_ERROR       = 1104,           ///< SOF accuracy error: other than 8 detected.
    FSP_ERR_JPEG_DQT_ACCURACY_ERROR       = 1105,           ///< DQT accuracy error: other than 0 detected.
    FSP_ERR_JPEG_COMPONENT_ERROR1         = 1106,           ///< Component error 1: the number of SOF0 header components
                                                            ///< detected is other than 1, 3, or 4.
    FSP_ERR_JPEG_COMPONENT_ERROR2 = 1107,                   ///< Component error 2: the number of components differs
                                                            ///< between SOF0 header and SOS.
    FSP_ERR_JPEG_SOF0_DQT_DHT_NOT_DETECTED          = 1108, ///< SOF0, DQT, and DHT not detected when SOS detected.
    FSP_ERR_JPEG_SOS_NOT_DETECTED                   = 1109, ///< SOS not detected: SOS not detected until EOI detected.
    FSP_ERR_JPEG_EOI_NOT_DETECTED                   = 1110, ///< EOI not detected (default)
    FSP_ERR_JPEG_RESTART_INTERVAL_DATA_NUMBER_ERROR = 1111, ///< Restart interval data number error detected.
    FSP_ERR_JPEG_IMAGE_SIZE_ERROR                   = 1112, ///< Image size error detected.
    FSP_ERR_JPEG_LAST_MCU_DATA_NUMBER_ERROR         = 1113, ///< Last MCU data number error detected.
    FSP_ERR_JPEG_BLOCK_DATA_NUMBER_ERROR            = 1114, ///< Block data number error detected.
    FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH              = 1115, ///< User provided buffer size not enough
    FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE             = 1116, ///< JPEG Image size is not aligned with MCU

    /* Start of touch panel framework specific */
    FSP_ERR_CALIBRATE_FAILED = 1200,                        ///< Calibration failed

    /* Start of IIRFA specific */
    FSP_ERR_IIRFA_ECC_1BIT = 1300,                          ///< 1-bit ECC error detected
    FSP_ERR_IIRFA_ECC_2BIT = 1301,                          ///< 2-bit ECC error detected

    /* Start of IP specific */
    FSP_ERR_IP_HARDWARE_NOT_PRESENT = 1400,                 ///< Requested IP does not exist on this device
    FSP_ERR_IP_UNIT_NOT_PRESENT     = 1401,                 ///< Requested unit does not exist on this device
    FSP_ERR_IP_CHANNEL_NOT_PRESENT  = 1402,                 ///< Requested channel does not exist on this device

    /* Start of USB specific */
    FSP_ERR_USB_FAILED      = 1500,
    FSP_ERR_USB_BUSY        = 1501,
    FSP_ERR_USB_SIZE_SHORT  = 1502,
    FSP_ERR_USB_SIZE_OVER   = 1503,
    FSP_ERR_USB_NOT_OPEN    = 1504,
    FSP_ERR_USB_NOT_SUSPEND = 1505,
    FSP_ERR_USB_PARAMETER   = 1506,

    /* Start of Message framework specific */
    FSP_ERR_NO_MORE_BUFFER           = 2000,         ///< No more buffer found in the memory block pool
    FSP_ERR_ILLEGAL_BUFFER_ADDRESS   = 2001,         ///< Buffer address is out of block memory pool
    FSP_ERR_INVALID_WORKBUFFER_SIZE  = 2002,         ///< Work buffer size is invalid
    FSP_ERR_INVALID_MSG_BUFFER_SIZE  = 2003,         ///< Message buffer size is invalid
    FSP_ERR_TOO_MANY_BUFFERS         = 2004,         ///< Number of buffer is too many
    FSP_ERR_NO_SUBSCRIBER_FOUND      = 2005,         ///< No message subscriber found
    FSP_ERR_MESSAGE_QUEUE_EMPTY      = 2006,         ///< No message found in the message queue
    FSP_ERR_MESSAGE_QUEUE_FULL       = 2007,         ///< No room for new message in the message queue
    FSP_ERR_ILLEGAL_SUBSCRIBER_LISTS = 2008,         ///< Message subscriber lists is illegal
    FSP_ERR_BUFFER_RELEASED          = 2009,         ///< Buffer has been released

    /* Start of 2DG Driver specific */
    FSP_ERR_D2D_ERROR_INIT      = 3000,              ///< D/AVE 2D has an error in the initialization
    FSP_ERR_D2D_ERROR_DEINIT    = 3001,              ///< D/AVE 2D has an error in the initialization
    FSP_ERR_D2D_ERROR_RENDERING = 3002,              ///< D/AVE 2D has an error in the rendering
    FSP_ERR_D2D_ERROR_SIZE      = 3003,              ///< D/AVE 2D has an error in the rendering

    /* Start of ETHER Driver specific */
    FSP_ERR_ETHER_ERROR_NO_DATA           = 4000,    ///< No Data in Receive buffer.
    FSP_ERR_ETHER_ERROR_LINK              = 4001,    ///< ETHERC/EDMAC has an error in the Auto-negotiation
    FSP_ERR_ETHER_ERROR_MAGIC_PACKET_MODE = 4002,    ///< As a Magic Packet is being detected, and
                                                     ///< transmission/reception is not enabled
    FSP_ERR_ETHER_ERROR_TRANSMIT_BUFFER_FULL = 4003, ///< Transmit buffer is not empty
    FSP_ERR_ETHER_ERROR_FILTERING            = 4004, ///< Detect multicast frame when multicast frame filtering enable
    FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION    = 4005, ///< ETHERC/EDMAC has an error in the phy communication
    FSP_ERR_ETHER_RECEIVE_BUFFER_ACTIVE      = 4006, ///< Receive buffer is active.

    /* Start of ETHER_PHY Driver specific */
    FSP_ERR_ETHER_PHY_ERROR_LINK = 5000,             ///< PHY is not link up.
    FSP_ERR_ETHER_PHY_NOT_READY  = 5001,             ///< PHY has an error in the Auto-negotiation

    /* Start of BYTEQ library specific */
    FSP_ERR_QUEUE_FULL  = 10000,                     ///< Queue is full, cannot queue another data
    FSP_ERR_QUEUE_EMPTY = 10001,                     ///< Queue is empty, no data to dequeue

    /* Start of CTSU Driver specific */
    FSP_ERR_CTSU_SCANNING              = 6000,       ///< Scanning.
    FSP_ERR_CTSU_NOT_GET_DATA          = 6001,       ///< Not processed previous scan data.
    FSP_ERR_CTSU_INCOMPLETE_TUNING     = 6002,       ///< Incomplete initial offset tuning.
    FSP_ERR_CTSU_DIAG_NOT_YET          = 6003,       ///< Diagnosis of data collected no yet.
    FSP_ERR_CTSU_DIAG_LDO_OVER_VOLTAGE = 6004,       ///< Diagnosis of LDO over voltage failed.
    FSP_ERR_CTSU_DIAG_CCO_HIGH         = 6005,       ///< Diagnosis of CCO into 19.2uA failed.
    FSP_ERR_CTSU_DIAG_CCO_LOW          = 6006,       ///< Diagnosis of CCO into 2.4uA failed.
    FSP_ERR_CTSU_DIAG_SSCG             = 6007,       ///< Diagnosis of SSCG frequency failed.
    FSP_ERR_CTSU_DIAG_DAC              = 6008,       ///< Diagnosis of non-touch count value failed.
    FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE   = 6009,       ///< Diagnosis of LDO output voltage failed.
    FSP_ERR_CTSU_DIAG_OVER_VOLTAGE     = 6010,       ///< Diagnosis of over voltage detection circuit failed.
    FSP_ERR_CTSU_DIAG_OVER_CURRENT     = 6011,       ///< Diagnosis of over current detection circuit failed.
    FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE  = 6012,       ///< Diagnosis of LDO internal resistance value failed.
    FSP_ERR_CTSU_DIAG_CURRENT_SOURCE   = 6013,       ///< Diagnosis of Current source value failed.
    FSP_ERR_CTSU_DIAG_SENSCLK_GAIN     = 6014,       ///< Diagnosis of SENSCLK frequency gain failed.
    FSP_ERR_CTSU_DIAG_SUCLK_GAIN       = 6015,       ///< Diagnosis of SUCLK frequency gain failed.
    FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY   = 6016,       ///< Diagnosis of SUCLK clock recovery function failed.
    FSP_ERR_CTSU_DIAG_CFC_GAIN         = 6017,       ///< Diagnosis of CFC oscillator gain failed.

    /* Start of SDMMC specific */
    FSP_ERR_CARD_INIT_FAILED     = 40000,            ///< SD card or eMMC device failed to initialize.
    FSP_ERR_CARD_NOT_INSERTED    = 40001,            ///< SD card not installed.
    FSP_ERR_DEVICE_BUSY          = 40002,            ///< Device is holding DAT0 low or another operation is ongoing.
    FSP_ERR_CARD_NOT_INITIALIZED = 40004,            ///< SD card was removed.
    FSP_ERR_CARD_WRITE_PROTECTED = 40005,            ///< Media is write protected.
    FSP_ERR_TRANSFER_BUSY        = 40006,            ///< Transfer in progress.
    FSP_ERR_RESPONSE             = 40007,            ///< Card did not respond or responded with an error.

    /* Start of FX_IO specific */
    FSP_ERR_MEDIA_FORMAT_FAILED = 50000,             ///< Media format failed.
    FSP_ERR_MEDIA_OPEN_FAILED   = 50001,             ///< Media open failed.

    /* Start of CAN specific */
    FSP_ERR_CAN_DATA_UNAVAILABLE   = 60000,          ///< No data available.
    FSP_ERR_CAN_MODE_SWITCH_FAILED = 60001,          ///< Switching operation modes failed.
    FSP_ERR_CAN_INIT_FAILED        = 60002,          ///< Hardware initialization failed.
    FSP_ERR_CAN_TRANSMIT_NOT_READY = 60003,          ///< Transmit in progress.
    FSP_ERR_CAN_RECEIVE_MAILBOX    = 60004,          ///< Mailbox is setup as a receive mailbox.
    FSP_ERR_CAN_TRANSMIT_MAILBOX   = 60005,          ///< Mailbox is setup as a transmit mailbox.
    FSP_ERR_CAN_MESSAGE_LOST       = 60006,          ///< Receive message has been overwritten or overrun.
    FSP_ERR_CAN_TRANSMIT_FIFO_FULL = 60007,          ///< Transmit FIFO is full.

    /* Start of SF_WIFI Specific */
    FSP_ERR_WIFI_CONFIG_FAILED    = 70000,           ///< WiFi module Configuration failed.
    FSP_ERR_WIFI_INIT_FAILED      = 70001,           ///< WiFi module initialization failed.
    FSP_ERR_WIFI_TRANSMIT_FAILED  = 70002,           ///< Transmission failed
    FSP_ERR_WIFI_INVALID_MODE     = 70003,           ///< API called when provisioned in client mode
    FSP_ERR_WIFI_FAILED           = 70004,           ///< WiFi Failed.
    FSP_ERR_WIFI_SCAN_COMPLETE    = 70005,           ///< Wifi scan has completed.
    FSP_ERR_WIFI_AP_NOT_CONNECTED = 70006,           ///< WiFi module is not connected to access point
    FSP_ERR_WIFI_UNKNOWN_AT_CMD   = 70007,           ///< DA16XXX Unknown AT command Error
    FSP_ERR_WIFI_INSUF_PARAM      = 70008,           ///< DA16XXX Insufficient parameter
    FSP_ERR_WIFI_TOO_MANY_PARAMS  = 70009,           ///< DA16XXX Too many parameters
    FSP_ERR_WIFI_INV_PARAM_VAL    = 70010,           ///< DA16XXX Wrong parameter value
    FSP_ERR_WIFI_NO_RESULT        = 70011,           ///< DA16XXX No result
    FSP_ERR_WIFI_RSP_BUF_OVFLW    = 70012,           ///< DA16XXX Response buffer overflow
    FSP_ERR_WIFI_FUNC_NOT_CONFIG  = 70013,           ///< DA16XXX Function is not configured
    FSP_ERR_WIFI_NVRAM_WR_FAIL    = 70014,           ///< DA16XXX NVRAM write failure
    FSP_ERR_WIFI_RET_MEM_WR_FAIL  = 70015,           ///< DA16XXX Retention memory write failure
    FSP_ERR_WIFI_UNKNOWN_ERR      = 70016,           ///< DA16XXX unknown error

    /* Start of SF_CELLULAR Specific */
    FSP_ERR_CELLULAR_CONFIG_FAILED       = 80000,    ///< Cellular module Configuration failed.
    FSP_ERR_CELLULAR_INIT_FAILED         = 80001,    ///< Cellular module initialization failed.
    FSP_ERR_CELLULAR_TRANSMIT_FAILED     = 80002,    ///< Transmission failed
    FSP_ERR_CELLULAR_FW_UPTODATE         = 80003,    ///< Firmware is uptodate
    FSP_ERR_CELLULAR_FW_UPGRADE_FAILED   = 80004,    ///< Firmware upgrade failed
    FSP_ERR_CELLULAR_FAILED              = 80005,    ///< Cellular Failed.
    FSP_ERR_CELLULAR_INVALID_STATE       = 80006,    ///< API Called in invalid state.
    FSP_ERR_CELLULAR_REGISTRATION_FAILED = 80007,    ///< Cellular Network registration failed

    /* Start of SF_BLE specific */
    FSP_ERR_BLE_FAILED              = 90001,         ///< BLE operation failed
    FSP_ERR_BLE_INIT_FAILED         = 90002,         ///< BLE device initialization failed
    FSP_ERR_BLE_CONFIG_FAILED       = 90003,         ///< BLE device configuration failed
    FSP_ERR_BLE_PRF_ALREADY_ENABLED = 90004,         ///< BLE device Profile already enabled
    FSP_ERR_BLE_PRF_NOT_ENABLED     = 90005,         ///< BLE device not enabled

    /* Start of SF_BLE_ABS specific */
    FSP_ERR_BLE_ABS_INVALID_OPERATION = 91001,       ///< Invalid operation is executed.
    FSP_ERR_BLE_ABS_NOT_FOUND         = 91002,       ///< Valid data or free space is not found.

    /* Start of Crypto specific (0x10000) @note Refer to sf_cryoto_err.h for Crypto error code. */
    FSP_ERR_CRYPTO_CONTINUE              = 0x10000,  ///< Continue executing function
    FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT = 0x10001,  ///< Hardware resource busy
    FSP_ERR_CRYPTO_SCE_FAIL              = 0x10002,  ///< Internal I/O buffer is not empty
    FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX = 0x10003,  ///< Invalid index
    FSP_ERR_CRYPTO_SCE_RETRY             = 0x10004,  ///< Retry
    FSP_ERR_CRYPTO_SCE_VERIFY_FAIL       = 0x10005,  ///< Verify is failed
    FSP_ERR_CRYPTO_SCE_ALREADY_OPEN      = 0x10006,  ///< HW SCE module is already opened
    FSP_ERR_CRYPTO_NOT_OPEN              = 0x10007,  ///< Hardware module is not initialized
    FSP_ERR_CRYPTO_UNKNOWN               = 0x10008,  ///< Some unknown error occurred
    FSP_ERR_CRYPTO_NULL_POINTER          = 0x10009,  ///< Null pointer input as a parameter
    FSP_ERR_CRYPTO_NOT_IMPLEMENTED       = 0x1000a,  ///< Algorithm/size not implemented
    FSP_ERR_CRYPTO_RNG_INVALID_PARAM     = 0x1000b,  ///< An invalid parameter is specified
    FSP_ERR_CRYPTO_RNG_FATAL_ERROR       = 0x1000c,  ///< A fatal error occurred
    FSP_ERR_CRYPTO_INVALID_SIZE          = 0x1000d,  ///< Size specified is invalid
    FSP_ERR_CRYPTO_INVALID_STATE         = 0x1000e,  ///< Function used in an valid state
    FSP_ERR_CRYPTO_ALREADY_OPEN          = 0x1000f,  ///< control block is already opened
    FSP_ERR_CRYPTO_INSTALL_KEY_FAILED    = 0x10010,  ///< Specified input key is invalid.
    FSP_ERR_CRYPTO_AUTHENTICATION_FAILED = 0x10011,  ///< Authentication failed
    FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      = 0x10012,  ///< Failure to Init Cipher
    FSP_ERR_CRYPTO_SCE_AUTHENTICATION    = 0x10013,  ///< Authentication failed
    FSP_ERR_CRYPTO_SCE_PARAMETER         = 0x10014,  ///< Input date is illegal.
    FSP_ERR_CRYPTO_SCE_PROHIBIT_FUNCTION = 0x10015,  ///< An invalid function call occurred.

    FSP_ERR_CRYPTO_SCE_LBIST_CHECK_BUSY = 0x100ff,   ///< LBIST Check BUSY

    /* Start of Crypto RSIP specific (0x10100) */
    FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT = 0x10100, ///< Hardware resource is busy
    FSP_ERR_CRYPTO_RSIP_FATAL             = 0x10101, ///< Hardware fatal error or unexpected return
    FSP_ERR_CRYPTO_RSIP_FAIL              = 0x10102, ///< Internal error
    FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      = 0x10103, ///< Input key type is illegal
    FSP_ERR_CRYPTO_RSIP_AUTHENTICATION    = 0x10104, ///< Authentication failed

    FSP_ERR_CRYPTO_RSIP_LBIST_CHECK_BUSY = 0x101ff,  ///< LBIST Check BUSY

    /* Start of SF_CRYPTO specific */
    FSP_ERR_CRYPTO_COMMON_NOT_OPENED      = 0x20000, ///< Crypto Framework Common is not opened
    FSP_ERR_CRYPTO_HAL_ERROR              = 0x20001, ///< Cryoto HAL module returned an error
    FSP_ERR_CRYPTO_KEY_BUF_NOT_ENOUGH     = 0x20002, ///< Key buffer size is not enough to generate a key
    FSP_ERR_CRYPTO_BUF_OVERFLOW           = 0x20003, ///< Attempt to write data larger than what the buffer can hold
    FSP_ERR_CRYPTO_INVALID_OPERATION_MODE = 0x20004, ///< Invalid operation mode.
    FSP_ERR_MESSAGE_TOO_LONG              = 0x20005, ///< Message for RSA encryption is too long.
    FSP_ERR_RSA_DECRYPTION_ERROR          = 0x20006, ///< RSA Decryption error.

    /** @note SF_CRYPTO APIs may return an error code starting from 0x10000 which is of Crypto module.
     *        Refer to sf_cryoto_err.h for Crypto error codes.
     */

    /* Start of Sensor specific */
    FSP_ERR_SENSOR_INVALID_DATA             = 0x30000, ///< Data is invalid.
    FSP_ERR_SENSOR_IN_STABILIZATION         = 0x30001, ///< Sensor is stabilizing.
    FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED = 0x30002, ///< Measurement is not finished.

    /* Start of COMMS specific */
    FSP_ERR_COMMS_BUS_NOT_OPEN = 0x40000,              ///< Bus is not open.
} fsp_err_t;

typedef enum e_elc_event
{
    ELC_EVENT_NONE                   = (0x0),   // Link disabled
    ELC_EVENT_ICU_IRQ0               = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1               = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2               = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3               = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4               = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5               = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6               = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7               = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8               = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9               = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10              = (0x00B), // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11              = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12              = (0x00D), // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13              = (0x00E), // External pin interrupt 13
    ELC_EVENT_ICU_IRQ14              = (0x00F), // External pin interrupt 14
    ELC_EVENT_DMAC0_INT              = (0x020), // DMAC0 transfer end
    ELC_EVENT_DMAC1_INT              = (0x021), // DMAC1 transfer end
    ELC_EVENT_DMAC2_INT              = (0x022), // DMAC2 transfer end
    ELC_EVENT_DMAC3_INT              = (0x023), // DMAC3 transfer end
    ELC_EVENT_DMAC4_INT              = (0x024), // DMAC4 transfer end
    ELC_EVENT_DMAC5_INT              = (0x025), // DMAC5 transfer end
    ELC_EVENT_DMAC6_INT              = (0x026), // DMAC6 transfer end
    ELC_EVENT_DMAC7_INT              = (0x027), // DMAC7 transfer end
    ELC_EVENT_DTC_COMPLETE           = (0x029), // DTC transfer complete
    ELC_EVENT_DMA_TRANSERR           = (0x02B), // DMA/DTC transfer error
    ELC_EVENT_ICU_SNOOZE_CANCEL      = (0x02D), // Canceling from Snooze mode
    ELC_EVENT_FCU_FIFERR             = (0x030), // Flash access error interrupt
    ELC_EVENT_FCU_FRDYI              = (0x031), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1               = (0x038), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2               = (0x039), // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP          = (0x03B), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST     = (0x03C), // Snooze entry
    ELC_EVENT_AGT0_INT               = (0x040), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A         = (0x041), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B         = (0x042), // Compare match B
    ELC_EVENT_AGT1_INT               = (0x043), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A         = (0x044), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B         = (0x045), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (0x052), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (0x053), // WDT underflow
    ELC_EVENT_CAN_RXF                = (0x059), // Global receive FIFO interrupt
    ELC_EVENT_CAN_GLERR              = (0x05A), // Global error
    ELC_EVENT_CAN_DMAREQ0            = (0x05B), // RX fifo DMA request 0
    ELC_EVENT_CAN_DMAREQ1            = (0x05C), // RX fifo DMA request 1
    ELC_EVENT_CAN0_TX                = (0x063), // Transmit interrupt
    ELC_EVENT_CAN0_CHERR             = (0x064), // Channel  error
    ELC_EVENT_CAN0_COMFRX            = (0x065), // Common FIFO receive interrupt
    ELC_EVENT_CAN0_CF_DMAREQ         = (0x066), // Channel  DMA request
    ELC_EVENT_CAN0_RXMB              = (0x067), // Receive message buffer interrupt
    ELC_EVENT_ACMPHS0_INT            = (0x08E), // High Speed Comparator channel 0 interrupt
    ELC_EVENT_ACMPHS1_INT            = (0x08F), // High Speed Comparator channel 1 interrupt
    ELC_EVENT_ACMPHS2_INT            = (0x090), // High Speed Comparator channel 2 interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (0x09E), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (0x09F), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (0x0A0), // Overflow interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (0x0B1), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (0x0B2), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3         = (0x0B3), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4         = (0x0B4), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (0x0B5), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (0x0B6), // Software event 1
    ELC_EVENT_POEG0_EVENT            = (0x0B7), // Port Output disable 0 interrupt
    ELC_EVENT_POEG1_EVENT            = (0x0B8), // Port Output disable 1 interrupt
    ELC_EVENT_POEG2_EVENT            = (0x0B9), // Port Output disable 2 interrupt
    ELC_EVENT_POEG3_EVENT            = (0x0BA), // Port Output disable 3 interrupt
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (0x0C0), // Capture/Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (0x0C1), // Capture/Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (0x0C2), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (0x0C3), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E         = (0x0C4), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F         = (0x0C5), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (0x0C6), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (0x0C7), // Underflow
    ELC_EVENT_GPT0_PC                = (0x0C8), // Period count function finish
    ELC_EVENT_GPT0_AD_TRIG_A         = (0x0C9), // A/D converter start request A
    ELC_EVENT_GPT0_AD_TRIG_B         = (0x0CA), // A/D converter start request B
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (0x0CB), // Capture/Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (0x0CC), // Capture/Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (0x0CD), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (0x0CE), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E         = (0x0CF), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F         = (0x0D0), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (0x0D1), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (0x0D2), // Underflow
    ELC_EVENT_GPT1_PC                = (0x0D3), // Period count function finish
    ELC_EVENT_GPT1_AD_TRIG_A         = (0x0D4), // A/D converter start request A
    ELC_EVENT_GPT1_AD_TRIG_B         = (0x0D5), // A/D converter start request B
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (0x0D6), // Capture/Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (0x0D7), // Capture/Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (0x0D8), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (0x0D9), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E         = (0x0DA), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F         = (0x0DB), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (0x0DC), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (0x0DD), // Underflow
    ELC_EVENT_GPT2_AD_TRIG_A         = (0x0DF), // A/D converter start request A
    ELC_EVENT_GPT2_AD_TRIG_B         = (0x0E0), // A/D converter start request B
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (0x0E1), // Capture/Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (0x0E2), // Capture/Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (0x0E3), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (0x0E4), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E         = (0x0E5), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F         = (0x0E6), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (0x0E7), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (0x0E8), // Underflow
    ELC_EVENT_GPT3_AD_TRIG_A         = (0x0EA), // A/D converter start request A
    ELC_EVENT_GPT3_AD_TRIG_B         = (0x0EB), // A/D converter start request B
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (0x0EC), // Capture/Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (0x0ED), // Capture/Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (0x0EE), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (0x0EF), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E         = (0x0F0), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F         = (0x0F1), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (0x0F2), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (0x0F3), // Underflow
    ELC_EVENT_GPT4_PC                = (0x0F4), // Period count function finish
    ELC_EVENT_GPT4_AD_TRIG_A         = (0x0F5), // A/D converter start request A
    ELC_EVENT_GPT4_AD_TRIG_B         = (0x0F6), // A/D converter start request B
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (0x0F7), // Capture/Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (0x0F8), // Capture/Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (0x0F9), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (0x0FA), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E         = (0x0FB), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F         = (0x0FC), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (0x0FD), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (0x0FE), // Underflow
    ELC_EVENT_GPT5_PC                = (0x0FF), // Period count function finish
    ELC_EVENT_GPT5_AD_TRIG_A         = (0x100), // A/D converter start request A
    ELC_EVENT_GPT5_AD_TRIG_B         = (0x101), // A/D converter start request B
    ELC_EVENT_OPS_UVW_EDGE           = (0x15C), // UVW edge event
    ELC_EVENT_ADC0_SCAN_END          = (0x160), // End of A/D scanning operation
    ELC_EVENT_ADC0_SCAN_END_B        = (0x161), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A          = (0x162), // Window A Compare match interrupt
    ELC_EVENT_ADC0_WINDOW_B          = (0x163), // Window B Compare match interrupt
    ELC_EVENT_ADC0_COMPARE_MATCH     = (0x164), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH  = (0x165), // Compare mismatch
    ELC_EVENT_SCI0_RXI               = (0x180), // Receive data full
    ELC_EVENT_SCI0_TXI               = (0x181), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (0x182), // Transmit end
    ELC_EVENT_SCI0_ERI               = (0x183), // Receive error
    ELC_EVENT_SCI0_AM                = (0x184), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (0x185), // Receive data full/Receive error
    ELC_EVENT_SCI9_RXI               = (0x1B6), // Receive data full
    ELC_EVENT_SCI9_TXI               = (0x1B7), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (0x1B8), // Transmit end
    ELC_EVENT_SCI9_ERI               = (0x1B9), // Receive error
    ELC_EVENT_SCI9_AM                = (0x1BA), // Address match event
    ELC_EVENT_SPI0_RXI               = (0x1C4), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (0x1C5), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (0x1C6), // Idle
    ELC_EVENT_SPI0_ERI               = (0x1C7), // Error
    ELC_EVENT_SPI0_TEI               = (0x1C8), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (0x1C9), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (0x1CA), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (0x1CB), // Idle
    ELC_EVENT_SPI1_ERI               = (0x1CC), // Error
    ELC_EVENT_SPI1_TEI               = (0x1CD), // Transmission complete event
    ELC_EVENT_CAN0_MRAM_ERI          = (0x1D0), // CANFD0 ECC error
    ELC_EVENT_DOC_INT                = (0x1DB), // Data operation circuit interrupt
    ELC_EVENT_I3C0_RESPONSE          = (0x1DC), // Response status buffer full
    ELC_EVENT_I3C0_COMMAND           = (0x1DD), // Command buffer empty
    ELC_EVENT_I3C0_IBI               = (0x1DE), // IBI status buffer full
    ELC_EVENT_I3C0_RX                = (0x1DF), // Receive
    ELC_EVENT_IICB0_RXI              = (0x1DF), // Receive
    ELC_EVENT_I3C0_TX                = (0x1E0), // Transmit
    ELC_EVENT_IICB0_TXI              = (0x1E0), // Transmit
    ELC_EVENT_I3C0_RCV_STATUS        = (0x1E1), // Receive status buffer full
    ELC_EVENT_I3C0_HRESP             = (0x1E2), // High priority response queue full
    ELC_EVENT_I3C0_HCMD              = (0x1E3), // High priority command queue empty
    ELC_EVENT_I3C0_HRX               = (0x1E4), // High priority rx data buffer full
    ELC_EVENT_I3C0_HTX               = (0x1E5), // High priority tx data buffer empty
    ELC_EVENT_I3C0_TEND              = (0x1E6), // Transmit end
    ELC_EVENT_IICB0_TEI              = (0x1E6), // Transmit end
    ELC_EVENT_I3C0_EEI               = (0x1E7), // Error
    ELC_EVENT_IICB0_ERI              = (0x1E7), // Error
    ELC_EVENT_I3C0_STEV              = (0x1E8), // Synchronous timing
    ELC_EVENT_I3C0_MREFOVF           = (0x1E9), // MREF counter overflow
    ELC_EVENT_I3C0_MREFCPT           = (0x1EA), // MREF capture
    ELC_EVENT_I3C0_AMEV              = (0x1EB), // Additional master-initiated bus event
    ELC_EVENT_I3C0_WU                = (0x1EC), // Wake-up Condition Detection interrupt
    ELC_EVENT_TRNG_RDREQ             = (0x1F3)  // TRNG Read Request
} elc_event_t;

#define FSP_PARAMETER_NOT_USED(p)    (void) ((p))

#define FSP_HEADER
#define FSP_FOOTER
#endif
