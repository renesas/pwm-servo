#ifndef _PIN_DATA_H
#define _PIN_DATA_H

#include "r_ioport_api.h"

typedef struct st_ioport_instance_ctrl
{
    uint32_t open;
    void   * p_context;
} ioport_instance_ctrl_t;

extern const ioport_cfg_t      g_bsp_pin_cfg;
extern ioport_instance_ctrl_t  g_ioport_ctrl;
extern const ioport_instance_t g_ioport;

#endif
