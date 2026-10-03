/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/* Pre-set configuration source file - do not edit */
#if USE_PRESET_CONFIG  //Use pre-set configuration for SG90 Servo Motor
#include <rs_servo_config_fpb_ra0l1_sg90.h>

const tau_pwm_channel_cfg_t g_timer_channel_cfg1_preset =
{ .channel = 1,
  /* Actual duty cycle percent: 5%. */
  .duty_cycle_counts = (uint16_t) 0x7d0,
  .output_level = TAU_PWM_OUTPUT_LEVEL_LOW,
  .output_polarity = TAU_PWM_OUTPUT_POLARITY_ACTIVE_HIGH,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
};
tau_pwm_instance_ctrl_t g_pwm_sg90_ctrl_preset;

const tau_pwm_extended_cfg_t g_pwm_sg90_extend_preset =
{ .operation_clock = TAU_PWM_OPERATION_CLOCK_CK00,
  .trigger_source = TAU_PWM_SOURCE_PIN_INPUT,
  .detect_edge = TAU_PWM_DETECT_EDGE_FALLING,
  .p_slave_channel_cfgs =
  {
    &g_timer_channel_cfg1_preset,
   }
};

const timer_cfg_t g_pwm_sg90_cfg_preset =
{ .mode = TIMER_MODE_PWM,
  /* Actual pulse period: 0.02 seconds. */
  .period_counts = (uint32_t) 0x9c40,
  .source_div = (timer_source_div_t) BSP_CFG_TAU_CK00,
  .channel = 0,
  .p_callback = NULL,
  .p_context = NULL,
  .p_extend = &g_pwm_sg90_extend_preset,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
};

/* Instance structure to use this module. */
const timer_instance_t g_pwm_sg90_preset =
{ .p_ctrl = &g_pwm_sg90_ctrl_preset, .p_cfg = &g_pwm_sg90_cfg_preset, .p_api = &g_timer_on_tau_pwm };

#endif  //Use pre-set configuration for SG90 Servo Motor

