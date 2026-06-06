#ifndef _TIMER_SPY_H
#define _TIMER_SPY_H

#include "bsp_api.h"
#include "r_timer_api.h"

typedef struct st_timer_ctrl
{
    bool          open;
    timer_state_t state;
} timer_spy_ctrl_t;

struct timer_spy_state * timer_spy_get_state(void);

fsp_err_t R_TimerSpy_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_TimerSpy_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TimerSpy_Start(timer_ctrl_t * const p_ctrl);

// fsp_err_t R_TimerSpy_Reset(timer_ctrl_t * const p_ctrl);
// fsp_err_t R_TimerSpy_Enable(timer_ctrl_t * const p_ctrl);
// fsp_err_t R_TimerSpy_Disable(timer_ctrl_t * const p_ctrl);
// fsp_err_t R_TimerSpy_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
// fsp_err_t R_TimerSpy_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
// fsp_err_t R_TimerSpy_CompareMatchSet(timer_ctrl_t * const        p_ctrl,
// uint32_t const              compare_match_value,
// timer_compare_match_t const match_channel);
fsp_err_t R_TimerSpy_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_TimerSpy_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);

// fsp_err_t R_TimerSpy_CallbackSet(timer_ctrl_t * const          p_api_ctrl,
// void (                      * p_callback)(timer_callback_args_t *),
// void * const                  p_context,
// timer_callback_args_t * const p_callback_memory);
fsp_err_t R_TimerSpy_Close(timer_ctrl_t * const p_ctrl);

extern const timer_api_t g_timer_on_timer_spy;
#endif
