#ifndef _TEST_SERVO_SHARED
#define _TEST_SERVO_SHARED

#include "r_timer_api.h"
#include "rm_servo.h"
#include "timer_spy.h"

// TIMER INSTANCE
extern timer_spy_ctrl_t g_timer_ctrl;
extern timer_cfg_t      g_timer_cfg;

extern const timer_instance_t g_timer0_instance;

// SERVO STRUCTURES
extern servo_ctrl_t g_servo_ctrl;

extern servo_cfg_t g_servo_cfg;

#endif
