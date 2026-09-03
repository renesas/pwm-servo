/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#ifndef SERVO_MOTOR_SERVO_H_
#define SERVO_MOTOR_SERVO_H_

#include "hal_data.h"

#if USE_PRESET_CONFIG
#ifdef BSP_MCU_R7FA2E3073CFL
#include <rs_servo_config_fpb_ra2e3_sg90.h>
#endif
#ifdef BSP_MCU_R7FA0L1074CFL
#include <rs_servo_config_fpb_ra0l1_sg90.h>
#endif
#endif

/* Public Data */

/* Servo Direction Enum */
typedef enum e_servo_direction_t
{
    SERVO_DIRECTION_DEFAULT,
    SERVO_DIRECTION_REVERSE,
} servo_direction_t;

/* Servo Device Configuration */
typedef struct st_servo_device_cfg
{
    int16_t minimum_angle;
    int16_t maximum_angle;
    uint16_t minimum_microseconds;
    uint16_t maximum_microseconds;
    servo_direction_t direction;
} servo_device_cfg_t;

/* Servo Function Control Block */
typedef struct st_servo_ctrl
{
    bool open;
/* PWM Timer
 * Supported: R_GPT, R_TAU_PWM */
#ifdef PWM_SERVO_USE_GPT
    /* GPT Timer Instance */
    gpt_instance_ctrl_t timer_ctrl;
    timer_cfg_t timer_cfg;
    gpt_extended_cfg_t  timer_cfg_extend;
#endif
#ifdef PWM_SERVO_USE_TAU
    /* TAU PWM Timer Instance */
    tau_pwm_instance_ctrl_t timer_ctrl;
    timer_cfg_t timer_cfg;
    tau_pwm_extended_cfg_t  timer_cfg_extend;
#endif

    /* Generic Public Timer Wrapper */
    timer_instance_t timer;

    /* Servo Device Configuration */
    const servo_device_cfg_t * p_device;

    /* Output Pin(s) */
    uint32_t pin_out;

    /* Derived Values */
    uint32_t period_counts;
    uint32_t min_duty_counts;
    uint32_t max_duty_counts;
} servo_ctrl_t;

/* Public Functions */
fsp_err_t rs_servo_SweepRangeOnce(servo_ctrl_t *p_servo_ctrl, const servo_device_cfg_t *p_motor_cfg);
fsp_err_t rs_servo_Open(servo_ctrl_t *p_servo_ctrl, const servo_device_cfg_t *p_motor_cfg);
fsp_err_t rs_servo_WriteAngle(servo_ctrl_t *p_servo_ctrl, int16_t angle);
fsp_err_t rs_servo_WritePercent(servo_ctrl_t * p_servo_ctrl, uint8_t percent);
fsp_err_t rs_servo_Close(servo_ctrl_t *p_servo_ctrl);
fsp_err_t rs_servo_config_gen(servo_ctrl_t *p_servo_ctrl, const timer_instance_t * p_timer_pwm);
fsp_err_t rs_servo_config_check(const servo_ctrl_t * p_servo_ctrl);
fsp_err_t rs_servo_calculate_onetime_values(servo_ctrl_t *p_servo_ctrl);

#endif /* SERVO_MOTOR_SERVO_H_ */
