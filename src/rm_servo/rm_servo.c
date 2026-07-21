#include "rm_servo.h"
#include "bsp_api.h"
#include "r_timer_api.h"

// TODO: Add parameter checking
// TODO: set/reset p_ctrl functions

static void servo_move_cfg_to_ctrl (servo_ctrl_t * const p_ctrl, const servo_cfg_t * const p_cfg)
{
    p_ctrl->servo_direction      = p_cfg->servo_direction;
    p_ctrl->minimum_angle        = p_cfg->minimum_angle;
    p_ctrl->maximum_angle        = p_cfg->maximum_angle;
    p_ctrl->minimum_microseconds = p_cfg->minimum_microseconds;
    p_ctrl->maximum_microseconds = p_cfg->maximum_microseconds;
    p_ctrl->p_timer_instance     = p_cfg->p_timer_instance;
}

static void servo_reset_ctrl (servo_ctrl_t * const p_ctrl)
{
    p_ctrl->servo_direction      = 0;
    p_ctrl->minimum_angle        = 0;
    p_ctrl->maximum_angle        = 0;
    p_ctrl->minimum_microseconds = 0;
    p_ctrl->maximum_microseconds = 0;
    p_ctrl->p_timer_instance     = NULL;
}

fsp_err_t RM_SERVO_Open (servo_ctrl_t * const p_ctrl, const servo_cfg_t * const p_cfg)
{
    FSP_ERROR_RETURN(false == p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    servo_move_cfg_to_ctrl(p_ctrl, p_cfg);

    const timer_instance_t * p_timer_instance = p_ctrl->p_timer_instance;

    p_timer_instance->p_api->open(p_timer_instance->p_ctrl, p_timer_instance->p_cfg);

    p_timer_instance->p_api->start(p_timer_instance->p_ctrl);

    p_ctrl->open = true;

    return FSP_SUCCESS;
}

fsp_err_t RM_SERVO_Close (servo_ctrl_t * const p_ctrl)
{
    FSP_ERROR_RETURN(true == p_ctrl->open, FSP_ERR_NOT_OPEN);

    const timer_instance_t * p_timer_instance = p_ctrl->p_timer_instance;

    // TODO: Do you need to stop the timer in order to close it??
    p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);

    p_timer_instance->p_api->close(p_timer_instance->p_ctrl);

    servo_reset_ctrl(p_ctrl);
    p_ctrl->open = false;

    return FSP_SUCCESS;
}

fsp_err_t RM_SERVO_SetAngle (servo_ctrl_t * const p_ctrl, int16_t angle)
{
    FSP_ERROR_RETURN(true == p_ctrl->open, FSP_ERR_NOT_OPEN);

    const timer_instance_t * p_servo_timer = p_ctrl->p_timer_instance;

    int interval_counts = p_ctrl->maximum_angle - p_ctrl->minimum_angle;

    // int pwm_range_microseconds = p_ctrl->maximum_microseconds - p_ctrl->minimum_microseconds;

    // TODO: error when this fails
    timer_info_t info;
    fsp_err_t    err = p_servo_timer->p_api->infoGet(p_servo_timer->p_ctrl, &info);

    int16_t angle_counts = p_ctrl->maximum_angle - p_ctrl->minimum_angle;

    // Angle normalized to 0.
    uint64_t adjusted_angle = angle - p_ctrl->minimum_angle;

    if (SERVO_DIRECTION_COUNTERCLOCKWISE == p_ctrl->servo_direction)
    {
        adjusted_angle = angle_counts - adjusted_angle;
    }

    uint16_t min_us = p_ctrl->minimum_microseconds;
    uint16_t max_us = p_ctrl->maximum_microseconds;

    uint32_t period_us = ((uint64_t) info.period_counts * 1000000) / info.clock_frequency;

    uint32_t counts_per_us = 1000000 / period_us;
    uint64_t min_counts    = min_us * counts_per_us;
    uint64_t max_counts    = max_us * counts_per_us;

    volatile uint64_t pulse = min_counts +
                              (adjusted_angle * (max_counts - min_counts)) /
                              angle_counts;

    // TODO: test for pin
    p_ctrl->p_timer_instance->p_api->dutyCycleSet(p_servo_timer->p_ctrl, pulse, 0);

    return FSP_SUCCESS;
}

fsp_err_t RM_SERVO_SetPercent (servo_ctrl_t * const p_ctrl, float percentage)
{
    FSP_ERROR_RETURN(true == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_ERR_ASSERTION;
}

// TODO: Better name for this function?
fsp_err_t RM_SERVO_SetTimerCounts (servo_ctrl_t * const p_ctrl, uint32_t count)
{
    FSP_ERROR_RETURN(true == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_ERR_ASSERTION;
}
