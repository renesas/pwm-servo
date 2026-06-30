/* Pre-set configuration header file - do not edit */
#if USE_PRESET_CONFIG  //Use pre-set configuration for SG90 Servo Motor
#ifndef SERVO_MOTOR_CONFIG_SG90_FPB_RA2E3_H_
#define SERVO_MOTOR_CONFIG_SG90_FPB_RA2E3_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_pwm_sg90_preset;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_pwm_sg90_ctrl_preset;
extern const timer_cfg_t g_pwm_sg90_cfg_preset;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

FSP_FOOTER
#endif /* SERVO_MOTOR_CONFIG_SG90_FPB_RA2E3_H_ */
#endif  //Use pre-set configuration for SG90 Servo Motor
