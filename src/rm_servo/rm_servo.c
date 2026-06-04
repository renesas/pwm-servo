#include "rm_servo.h"
#include "bsp_api.h"

// TODO: Add parameter checking
// TODO: set/reset p_ctrl functions

fsp_err_t RM_SERVO_Open(servo_ctrl_t * const p_ctrl, const servo_cfg_t * const p_cfg)
{
    return FSP_ERR_ASSERTION;
}

fsp_err_t RM_SERVO_Close(servo_ctrl_t * const p_ctrl)
{
    return FSP_ERR_ASSERTION;
}

fsp_err_t RM_SERVO_SetAngle(servo_ctrl_t * const p_ctrl, int16_t angle)
{
    return FSP_ERR_ASSERTION;
}

fsp_err_t RM_SERVO_SetPercent(servo_ctrl_t * const p_ctrl, float percentage)
{
    return FSP_ERR_ASSERTION;
}

// TODO: Better name for this function?
fsp_err_t RM_SERVO_SetTimerCounts(servo_ctrl_t * const p_ctrl, uint32_t count)
{
    return FSP_ERR_ASSERTION;
}
