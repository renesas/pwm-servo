/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/* Pre-set configuration header file - do not edit */
#if USE_PRESET_CONFIG  //Use pre-set configuration for SG90 Servo Motor
#ifndef SERVO_MOTOR_CONFIG_SG90_FPB_RA0L1_H_
#define SERVO_MOTOR_CONFIG_SG90_FPB_RA0l1_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_tau_pwm.h"
#include "r_timer_api.h"
FSP_HEADER

/* The PWM Timer Module Used */
#define PWM_SERVO_USE_TAU

/** TAU PWM Timer Instance */
extern const timer_instance_t g_pwm_sg90_preset;

/** Access the TAU PWM instance using these structures when calling API functions directly (::p_api is not used). */
extern tau_pwm_instance_ctrl_t g_pwm_sg90_ctrl_preset;
extern const timer_cfg_t g_pwm_sg90_cfg_preset;

FSP_FOOTER
#endif /* SERVO_MOTOR_CONFIG_SG90_FPB_RA0L1_H_ */
#endif  //Use pre-set configuration for SG90 Servo Motor
