#include "bsp_api.h"
#include "mocks/timer_spy.h"
#include "r_timer_api.h"
#include "unity_fixture.h"

#include "stdbool.h"

timer_spy_ctrl_t g_timer_spy_ctrl = {};
timer_cfg_t      g_timer_spy_cfg  = {};

TEST_GROUP(TIMER_SPY);

TEST_SETUP(TIMER_SPY)
{
}

TEST_TEAR_DOWN(TIMER_SPY)
{
}

TEST(TIMER_SPY, test_open)
{
    fsp_err_t err = g_timer_on_timer_spy.open(&g_timer_spy_ctrl, &g_timer_spy_cfg);
    TEST_ASSERT_EQUAL_INT(FSP_SUCCESS, err);

    timer_status_t p_status;
    R_TimerSpy_StatusGet(&g_timer_spy_ctrl, &p_status);
    TEST_ASSERT_EQUAL_INT(true, g_timer_spy_ctrl.open);
    TEST_ASSERT_EQUAL_INT(TIMER_STATE_STOPPED, p_status.state);
}

TEST(TIMER_SPY, test_open_close)
{
    g_timer_on_timer_spy.open(&g_timer_spy_ctrl, &g_timer_spy_cfg);
    g_timer_on_timer_spy.close(&g_timer_spy_ctrl);

    TEST_ASSERT_EQUAL_INT(false, g_timer_spy_ctrl.open);
    TEST_ASSERT_EQUAL_INT(TIMER_STATE_UNKNOWN, g_timer_spy_ctrl.state);
}

TEST(TIMER_SPY, test_already_open)
{
    g_timer_on_timer_spy.open(&g_timer_spy_ctrl, &g_timer_spy_cfg);
    fsp_err_t err = g_timer_on_timer_spy.open(&g_timer_spy_ctrl, &g_timer_spy_cfg);

    TEST_ASSERT_EQUAL_INT(FSP_ERR_ALREADY_OPEN, err);
    g_timer_on_timer_spy.close(&g_timer_spy_ctrl);
}

TEST(TIMER_SPY, test_not_open_err)
{
    fsp_err_t err = g_timer_on_timer_spy.close(&g_timer_spy_ctrl);
    TEST_ASSERT_EQUAL_INT(FSP_ERR_NOT_OPEN, err);
    err = g_timer_on_timer_spy.start(&g_timer_spy_ctrl);
    TEST_ASSERT_EQUAL_INT(FSP_ERR_NOT_OPEN, err);
    err = g_timer_on_timer_spy.stop(&g_timer_spy_ctrl);
    TEST_ASSERT_EQUAL_INT(FSP_ERR_NOT_OPEN, err);
    timer_status_t p_status;
    err = g_timer_on_timer_spy.statusGet(&g_timer_spy_ctrl, &p_status);
    TEST_ASSERT_EQUAL_INT(FSP_ERR_NOT_OPEN, err);
}

TEST(TIMER_SPY, test_timer_start_stop)
{
    g_timer_on_timer_spy.open(&g_timer_spy_ctrl, &g_timer_spy_cfg);
    fsp_err_t err = g_timer_on_timer_spy.start(&g_timer_spy_ctrl);

    timer_status_t p_status;
    R_TimerSpy_StatusGet(&g_timer_spy_ctrl, &p_status);
    TEST_ASSERT_EQUAL_INT(FSP_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(TIMER_STATE_COUNTING, p_status.state);

    err = g_timer_on_timer_spy.stop(&g_timer_spy_ctrl);
    R_TimerSpy_StatusGet(&g_timer_spy_ctrl, &p_status);
    TEST_ASSERT_EQUAL_INT(FSP_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(TIMER_STATE_STOPPED, p_status.state);
}
