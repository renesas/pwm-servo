#include "test_servo_shared.h"

timer_spy_ctrl_t g_timer_ctrl;
timer_cfg_t      g_timer_cfg;

const timer_instance_t g_timer0_instance =
{
    .p_api  = &g_timer_on_timer_spy,
    .p_cfg  = &g_timer_cfg,
    .p_ctrl = (timer_ctrl_t *) &g_timer_ctrl,
};

// SERVO STRUCTURES
servo_ctrl_t g_servo_ctrl;

servo_cfg_t g_servo_cfg =
{
    .servo_direction      = SERVO_DIRECTION_CLOCKWISE,
    .minimum_angle        = 0,
    .maximum_angle        = 180,
    .minimum_microseconds = 1000,
    .maximum_microseconds = 2000,
    .p_timer_instance     = &g_timer0_instance,
};
