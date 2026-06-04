#include "pin_data.h"
#include "mocks/pin_api_spy.h"

const ioport_pin_cfg_t g_bsp_pin_cfg_data[] =
{
    // TODO: real pin cfg data here!
    {.pin = 0x100, .pin_cfg = 0},
    {.pin = 0x200, .pin_cfg = 0},
    {.pin = 0x300, .pin_cfg = 0},
    {.pin = 0x400, .pin_cfg = 0},
    {.pin = 0x500, .pin_cfg = 0},
};

const ioport_cfg_t g_bsp_pin_cfg =
{
    .number_of_pins = sizeof(g_bsp_pin_cfg_data) / sizeof(ioport_pin_cfg_t),
    .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
};

ioport_instance_ctrl_t g_ioport_ctrl = {};

const ioport_instance_t g_ioport =
{
    .p_api  = &g_ioport_on_ioport,
    .p_ctrl = &g_ioport_ctrl,
    .p_cfg  = &g_bsp_pin_cfg,
};
