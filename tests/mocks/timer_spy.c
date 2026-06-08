#include "timer_spy.h"
#include "bsp_api.h"
#include "bsp_common.h"
#include "r_timer_api.h"

fsp_err_t R_TimerSpy_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    FSP_PARAMETER_NOT_USED(p_cfg);

    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;

    FSP_ERROR_RETURN(false == p_inst_ctrl->open, FSP_ERR_ALREADY_OPEN);

    p_inst_ctrl->open  = true;
    p_inst_ctrl->state = TIMER_STATE_STOPPED;

    return FSP_SUCCESS;
}

fsp_err_t R_TimerSpy_Close (timer_ctrl_t * const p_ctrl)
{
    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;

    FSP_ERROR_RETURN(true == p_inst_ctrl->open, FSP_ERR_NOT_OPEN);

    p_inst_ctrl->open  = false;
    p_inst_ctrl->state = TIMER_STATE_UNKNOWN;

    return FSP_SUCCESS;
}

fsp_err_t R_TimerSpy_Start (timer_ctrl_t * const p_ctrl)
{
    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;
    FSP_ERROR_RETURN(true == p_inst_ctrl->open, FSP_ERR_NOT_OPEN);

    p_inst_ctrl->state = TIMER_STATE_COUNTING;

    return FSP_SUCCESS;
}

fsp_err_t R_TimerSpy_Stop (timer_ctrl_t * const p_ctrl)
{
    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;
    FSP_ERROR_RETURN(true == p_inst_ctrl->open, FSP_ERR_NOT_OPEN);

    p_inst_ctrl->state = TIMER_STATE_STOPPED;

    return FSP_SUCCESS;
}

fsp_err_t R_TimerSpy_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;
    FSP_ERROR_RETURN(true == p_inst_ctrl->open, FSP_ERR_NOT_OPEN);

    p_status->state   = p_inst_ctrl->state;
    p_status->counter = 0;

    return FSP_SUCCESS;
}

fsp_err_t R_TimerSpy_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;
    FSP_ERROR_RETURN(true == p_inst_ctrl->open, FSP_ERR_NOT_OPEN);

    p_info->clock_frequency = 48000000;
    p_info->count_direction = TIMER_DIRECTION_UP;
    p_info->period_counts   = 65000;

    return FSP_SUCCESS;
}

fsp_err_t R_TimerSpy_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
    timer_spy_ctrl_t * p_inst_ctrl = (timer_spy_ctrl_t *) p_ctrl;
    FSP_ERROR_RETURN(true == p_inst_ctrl->open, FSP_ERR_NOT_OPEN);

    p_inst_ctrl->duty_cycle = duty_cycle_counts;

    return FSP_SUCCESS;
}

const timer_api_t g_timer_on_timer_spy =
{
    .open         = &R_TimerSpy_Open,
    .close        = &R_TimerSpy_Close,
    .start        = &R_TimerSpy_Start,
    .stop         = &R_TimerSpy_Stop,
    .statusGet    = &R_TimerSpy_StatusGet,
    .infoGet      = &R_TimerSpy_InfoGet,
    .dutyCycleSet = &R_TimerSpy_DutyCycleSet
};
