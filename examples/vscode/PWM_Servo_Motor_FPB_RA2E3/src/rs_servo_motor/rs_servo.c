/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
#if USE_PRESET_CONFIG
#include <rs_servo_config_fpb_ra2e3_sg90.h>
#endif
#include <rs_servo.h>

#define RS_SERVO_DELAY_100MS     (100)
#define RS_SERVO_DELAY_1S        (1000)
#define RS_SERVO_US_PER_SECOND   (1000000ULL)
#define RS_SERVO_MIN_PERCENTAGE  (0U)
#define RS_SERVO_MAX_PERCENTAGE  (100U)
#define RS_SERVO_MAX_ANGLE_CFG   (360)
#define RS_SERVO_MIN_ANGLE_CFG   (-180)

fsp_err_t rs_servo_SweepRangeOnce(servo_ctrl_t *p_servo_ctrl, const servo_device_cfg_t *p_motor_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    int16_t sweep_angle = 0;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_motor_cfg, FSP_ERR_INVALID_POINTER);

    /* Open the servo motor. Starts the motor at the minimum angle. */
    if(p_servo_ctrl->open == false)
    {
        err = rs_servo_Open(p_servo_ctrl, p_motor_cfg);
        if(err) return err;
    }
    else
    {
        /* If already open, set to the minimum angle. */
        sweep_angle = p_servo_ctrl->p_device->minimum_angle;
        err = rs_servo_WriteAngle(p_servo_ctrl, sweep_angle);
        if(err) return err;
    }

    R_BSP_SoftwareDelay(RS_SERVO_DELAY_100MS, BSP_DELAY_UNITS_MILLISECONDS);

    /* Perform a sweep through every angle with a 100ms delay in between each write.
     * When returning to the minimum angle add a 1 second delay. */

    for(sweep_angle = p_servo_ctrl->p_device->minimum_angle + 1; sweep_angle <= p_servo_ctrl->p_device->maximum_angle; ++sweep_angle)
    {
        err = rs_servo_WriteAngle(p_servo_ctrl, sweep_angle);
        if(err) return err;
        R_BSP_SoftwareDelay(RS_SERVO_DELAY_100MS, BSP_DELAY_UNITS_MILLISECONDS);
    }

    /* Sweep back to the minimum angle with a larger delay. */
    err = rs_servo_WriteAngle(p_servo_ctrl, p_servo_ctrl->p_device->minimum_angle);
    if(err) return err;
    R_BSP_SoftwareDelay(RS_SERVO_DELAY_1S, BSP_DELAY_UNITS_MILLISECONDS);

    return err;
}

fsp_err_t rs_servo_Open(servo_ctrl_t *p_servo_ctrl, const servo_device_cfg_t *p_motor_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_motor_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_servo_ctrl->open == false, FSP_ERR_ALREADY_OPEN);

    /* Set up the timer configurations. */
#if USE_PRESET_CONFIG
    err = rs_servo_config_gen(p_servo_ctrl, &g_pwm_sg90_preset);
#else
    err = rs_servo_config_gen(p_servo_ctrl, &g_pwm_sg90);
#endif
    if(err) return err;

    /* Assign the servo motor device configurations. */
    p_servo_ctrl->p_device = p_motor_cfg;

    /* Check that the servo control block has the right timer and servo motor device configuration. */
    err = rs_servo_config_check(p_servo_ctrl);
    if(err) return err;

    /* Calculate the one-time values. */
    err = rs_servo_calculate_onetime_values(p_servo_ctrl);
    if(err) return err;

    /* Identify output pin used for the timer. */
    if( (p_servo_ctrl->timer_cfg_extend.gtioca.output_enabled == true )
            && (p_servo_ctrl->timer_cfg_extend.gtiocb.output_enabled == false)  )
    {
        p_servo_ctrl->pin_out = GPT_IO_PIN_GTIOCA;

    }
    else if((p_servo_ctrl->timer_cfg_extend.gtioca.output_enabled == false )
            && (p_servo_ctrl->timer_cfg_extend.gtiocb.output_enabled == true))
    {
        p_servo_ctrl->pin_out = GPT_IO_PIN_GTIOCB;
    }
    else if((p_servo_ctrl->timer_cfg_extend.gtioca.output_enabled == true )
            && (p_servo_ctrl->timer_cfg_extend.gtiocb.output_enabled == true))
    {
        p_servo_ctrl->pin_out = GPT_IO_PIN_GTIOCA_AND_GTIOCB;
    }

    /* Open and start the GPT at the smallest degree position */
    err = p_servo_ctrl->timer.p_api->open(p_servo_ctrl->timer.p_ctrl, p_servo_ctrl->timer.p_cfg);
    if(err) return err;

    err = p_servo_ctrl->timer.p_api->dutyCycleSet(p_servo_ctrl->timer.p_ctrl, p_servo_ctrl->min_duty_counts, p_servo_ctrl->pin_out);
    if(err) return err;

    err = p_servo_ctrl->timer.p_api->start(p_servo_ctrl->timer.p_ctrl);
    if(err) return err;

    /* Mark the servo control instance as open. */
    p_servo_ctrl->open = true;

    return err;
}

fsp_err_t rs_servo_WriteAngle(servo_ctrl_t *p_servo_ctrl, int16_t angle)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_servo_ctrl->p_device, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(true == p_servo_ctrl->open, FSP_ERR_NOT_OPEN);

    int16_t min_angle = p_servo_ctrl->p_device->minimum_angle;
    int16_t max_angle = p_servo_ctrl->p_device->maximum_angle;

    FSP_ERROR_RETURN(angle >= min_angle, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(angle <= max_angle, FSP_ERR_INVALID_ARGUMENT);

    /* Calculate the number of counts for the new duty cycle. */
    uint16_t angle_range_counts = (uint16_t) (max_angle - min_angle);
    uint32_t duty_range_counts  = p_servo_ctrl->max_duty_counts - p_servo_ctrl->min_duty_counts;

    /* Normalize angle minimum to 0. */
    uint32_t adjusted_angle = (uint32_t) (angle - min_angle);

    if (SERVO_DIRECTION_REVERSE == p_servo_ctrl->p_device->direction)
    {
        adjusted_angle = angle_range_counts - adjusted_angle;
    }

    uint32_t pulse_counts = p_servo_ctrl->min_duty_counts +
                            (uint32_t) (( (uint64_t)adjusted_angle * duty_range_counts) / angle_range_counts );

    FSP_ERROR_RETURN(pulse_counts < p_servo_ctrl->period_counts, FSP_ERR_INVALID_ARGUMENT);

    /* Set the new duty cycle. */
    err = p_servo_ctrl->timer.p_api->dutyCycleSet(p_servo_ctrl->timer.p_ctrl, pulse_counts, p_servo_ctrl->pin_out);
    return err;
}

fsp_err_t rs_servo_WritePercent(servo_ctrl_t * p_servo_ctrl, uint8_t percent)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_servo_ctrl->p_device, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(true == p_servo_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Step must be 0–100 */
    FSP_ERROR_RETURN(percent <= RS_SERVO_MAX_PERCENTAGE, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(percent >= RS_SERVO_MIN_PERCENTAGE, FSP_ERR_INVALID_ARGUMENT);

    uint32_t duty_range_counts  = p_servo_ctrl->max_duty_counts - p_servo_ctrl->min_duty_counts;

    /* Consider direction step */
    uint32_t adjusted_percent = (uint32_t) percent;

    if (SERVO_DIRECTION_REVERSE == p_servo_ctrl->p_device->direction)
    {
        adjusted_percent = RS_SERVO_MAX_PERCENTAGE - adjusted_percent;
    }

    uint32_t pulse_counts =
            p_servo_ctrl->min_duty_counts +
            (uint32_t)(((uint64_t) adjusted_percent * duty_range_counts) / RS_SERVO_MAX_PERCENTAGE);

    FSP_ERROR_RETURN(pulse_counts < p_servo_ctrl->period_counts, FSP_ERR_INVALID_ARGUMENT);

    /* Set the new duty cycle. */
    err = p_servo_ctrl->timer.p_api->dutyCycleSet(p_servo_ctrl->timer.p_ctrl, pulse_counts, p_servo_ctrl->pin_out);

    return err;
}

fsp_err_t rs_servo_Close(servo_ctrl_t *p_servo_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(true == p_servo_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Close the timer */
    err = p_servo_ctrl->timer.p_api->close(p_servo_ctrl->timer.p_ctrl);
    if(err) return err;

    /* Reset state */
    p_servo_ctrl->open = false;

    return FSP_SUCCESS;
}

fsp_err_t rs_servo_config_gen(servo_ctrl_t *p_servo_ctrl, const timer_instance_t * p_timer_pwm)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_timer_pwm, FSP_ERR_INVALID_POINTER);

    /* Initialize configuration. */
    memset(&p_servo_ctrl->timer_cfg, 0, sizeof(timer_cfg_t));
    memset(&p_servo_ctrl->timer_cfg_extend, 0, sizeof(gpt_extended_cfg_t));

    /* Copy configurations from the timer instance used into SRAM. */
    memcpy(&p_servo_ctrl->timer_cfg, p_timer_pwm->p_cfg, sizeof(timer_cfg_t));
    memcpy(&p_servo_ctrl->timer_cfg_extend, p_timer_pwm->p_cfg->p_extend,  sizeof(gpt_extended_cfg_t));

    /* Manually assign addresses of p_extend to the extended configs in SRAM. */
    p_servo_ctrl->timer_cfg.p_extend = (gpt_extended_cfg_t *) &p_servo_ctrl->timer_cfg_extend;

    /* Build instance of the public timer wrapper by assigning pointers to its members. */
    p_servo_ctrl->timer.p_ctrl = &p_servo_ctrl->timer_ctrl;
    p_servo_ctrl->timer.p_cfg = &p_servo_ctrl->timer_cfg;
    p_servo_ctrl->timer.p_api = p_timer_pwm->p_api;

    return err;
}

fsp_err_t rs_servo_config_check(const servo_ctrl_t * p_servo_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);

    /* Control block must have a servo device configuration. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl->p_device, FSP_ERR_INVALID_POINTER);

    /* Check that the servo device configurations are acceptable. */
    FSP_ERROR_RETURN(p_servo_ctrl->p_device->minimum_angle >= RS_SERVO_MIN_ANGLE_CFG, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(p_servo_ctrl->p_device->maximum_angle <= RS_SERVO_MAX_ANGLE_CFG, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(p_servo_ctrl->p_device->maximum_angle > p_servo_ctrl->p_device->minimum_angle, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(p_servo_ctrl->p_device->maximum_microseconds > p_servo_ctrl->p_device->minimum_microseconds, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN( (p_servo_ctrl->p_device->direction == SERVO_DIRECTION_DEFAULT) || (p_servo_ctrl->p_device->direction == SERVO_DIRECTION_REVERSE),  FSP_ERR_INVALID_MODE);

    /* Ensure the public timer wrapper encapsulates the ctrl, cfg, and extended cfg. */
    FSP_ERROR_RETURN(p_servo_ctrl->timer.p_ctrl == &p_servo_ctrl->timer_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_servo_ctrl->timer.p_cfg == &p_servo_ctrl->timer_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_servo_ctrl->timer.p_cfg->p_extend == &p_servo_ctrl->timer_cfg_extend, FSP_ERR_INVALID_POINTER);

    return err;
}
fsp_err_t rs_servo_calculate_onetime_values(servo_ctrl_t *p_servo_ctrl)
{

    fsp_err_t err = FSP_SUCCESS;
    timer_info_t timer_info;
    memset(&timer_info, 0, sizeof(timer_info_t));

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_servo_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_servo_ctrl->p_device, FSP_ERR_INVALID_POINTER);

    /* Set the total counts per period. */
    err = p_servo_ctrl->timer.p_api->infoGet(p_servo_ctrl->timer.p_ctrl, &timer_info);
    p_servo_ctrl->period_counts = timer_info.period_counts;

    /* Set the min and max counts based on the specified min/max microsecond values in the servo cfg. */
    p_servo_ctrl->min_duty_counts = (uint32_t) ((((uint64_t) p_servo_ctrl->p_device->minimum_microseconds) *
                                 timer_info.clock_frequency) / RS_SERVO_US_PER_SECOND);

    p_servo_ctrl->max_duty_counts = (uint32_t) ((((uint64_t) p_servo_ctrl->p_device->maximum_microseconds) *
                                 timer_info.clock_frequency) / RS_SERVO_US_PER_SECOND);

    return err;
}

