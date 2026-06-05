#include "unity_fixture.h"
#include "test_servo_shared.h"

TEST_GROUP(SERVO);

TEST_SETUP(SERVO)
{
}

TEST_TEAR_DOWN(SERVO)
{
    RM_SERVO_Close(&g_servo_ctrl);
}

TEST(SERVO, servo_open)
{
    // It should open successfully
    fsp_err_t err = RM_SERVO_Open(&g_servo_ctrl, &g_servo_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    // The open flag should be set to true
    TEST_ASSERT_EQUAL(true, g_servo_ctrl.open);

    // The control struct should have been initialized properly
    TEST_ASSERT_EQUAL(g_servo_cfg.servo_direction, g_servo_ctrl.servo_direction);
    TEST_ASSERT_EQUAL_INT16(g_servo_cfg.minimum_angle, g_servo_ctrl.minimum_angle);
    TEST_ASSERT_EQUAL_INT16(g_servo_cfg.maximum_angle, g_servo_ctrl.maximum_angle);
    TEST_ASSERT_EQUAL_UINT16(g_servo_cfg.minimum_microseconds, g_servo_ctrl.minimum_microseconds);
    TEST_ASSERT_EQUAL_UINT16(g_servo_cfg.maximum_microseconds, g_servo_ctrl.maximum_microseconds);
    TEST_ASSERT_EQUAL_PTR(g_servo_cfg.p_timer_instance, g_servo_ctrl.p_timer_instance);
}

TEST(SERVO, servo_close)
{
    // It should open and close successfully
    fsp_err_t err = RM_SERVO_Open(&g_servo_ctrl, &g_servo_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    err = RM_SERVO_Close(&g_servo_ctrl);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    // The open flag should be set to false
    TEST_ASSERT_EQUAL(false, g_servo_ctrl.open);

    // The control struct should have been cleared properly
    TEST_ASSERT_EQUAL(0, g_servo_ctrl.servo_direction);
    TEST_ASSERT_EQUAL_INT16(0, g_servo_ctrl.minimum_angle);
    TEST_ASSERT_EQUAL_INT16(0, g_servo_ctrl.maximum_angle);
    TEST_ASSERT_EQUAL_UINT16(0, g_servo_ctrl.minimum_microseconds);
    TEST_ASSERT_EQUAL_UINT16(0, g_servo_ctrl.maximum_microseconds);
    TEST_ASSERT_EQUAL_PTR(NULL, g_servo_ctrl.p_timer_instance);
}

TEST(SERVO, servo_manages_timer_open_and_close)
{
    fsp_err_t err = RM_SERVO_Open(&g_servo_ctrl, &g_servo_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    // When the servo is opened the timer should be open and started.
    TEST_ASSERT_EQUAL(true, g_timer_ctrl.open);
    TEST_ASSERT_EQUAL(TIMER_STATE_COUNTING, g_timer_ctrl.state);

    err = RM_SERVO_Close(&g_servo_ctrl);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    // When the servo is closed the timer should be stopped and closed as well.
    TEST_ASSERT_EQUAL(false, g_timer_ctrl.open);
    TEST_ASSERT_EQUAL(TIMER_STATE_UNKNOWN, g_timer_ctrl.state);
}
