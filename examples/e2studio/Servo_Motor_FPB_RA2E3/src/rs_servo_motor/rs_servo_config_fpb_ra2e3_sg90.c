/* Pre-set configuration source file - do not edit */

#if USE_PRESET_CONFIG  //Use pre-set configuration for SG90 Servo Motor
#include <rs_servo_motor/rs_servo_config_fpb_ra2e3_sg90.h>

gpt_instance_ctrl_t g_pwm_sg90_ctrl_preset;

const gpt_extended_cfg_t g_pwm_sg90_extend_preset=
        { .gtioca =
        { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE), .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE), .capture_a_ipl = (BSP_IRQ_DISABLED), .capture_b_ipl =
                  (BSP_IRQ_DISABLED),
          .compare_match_c_ipl = (BSP_IRQ_DISABLED), .compare_match_d_ipl = (BSP_IRQ_DISABLED), .compare_match_e_ipl =
                  (BSP_IRQ_DISABLED),
          .compare_match_f_ipl = (BSP_IRQ_DISABLED),

          .capture_a_irq = FSP_INVALID_VECTOR,

          .capture_b_irq = FSP_INVALID_VECTOR,

          .compare_match_c_irq = FSP_INVALID_VECTOR,

          .compare_match_d_irq = FSP_INVALID_VECTOR,

          .compare_match_e_irq = FSP_INVALID_VECTOR,

          .compare_match_f_irq = FSP_INVALID_VECTOR,

          .compare_match_value =
          { (uint32_t) 0x0, /* CMP_A */
            (uint32_t) 0x0, /* CMP_B */
            (uint32_t) 0x0, /* CMP_C */
            (uint32_t) 0x0, /* CMP_D */
            (uint32_t) 0x0, /* CMP_E */
            (uint32_t) 0x0, /* CMP_F */},
          .compare_match_status = ((0U << 5U) | (0U << 4U) | (0U << 3U) | (0U << 2U) | (0U << 1U) | 0U), .capture_filter_gtioca =
                  GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,

          .p_pwm_cfg = NULL,


          .gtior_setting.gtior = 0U,

          .gtioca_polarity = GPT_GTIOC_POLARITY_NORMAL,
          .gtiocb_polarity = GPT_GTIOC_POLARITY_NORMAL, };

const timer_cfg_t g_pwm_sg90_cfg_preset =
{ .mode = TIMER_MODE_PWM,
/* Actual period: 0.02 seconds. Actual duty: 5%. */.period_counts = (uint32_t) 0xea600,
  .duty_cycle_counts = 0xbb80, .source_div = (timer_source_div_t) 0, .channel = 0, .p_callback = NULL,
  .p_context           = NULL,
  .p_extend = &g_pwm_sg90_extend_preset,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
};
/* Instance structure to use this module. */
const timer_instance_t g_pwm_sg90_preset =
{ .p_ctrl = &g_pwm_sg90_ctrl_preset, .p_cfg = &g_pwm_sg90_cfg_preset, .p_api = &g_timer_on_gpt };

#endif  //Use pre-set configuration for SG90 Servo Motor

