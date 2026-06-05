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

    return FSP_ERR_ASSERTION;
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
