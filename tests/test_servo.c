#include "timer_spy.h"
#include "unity_fixture.h"
#include "test_servo_shared.h"

TEST_GROUP(SERVO);

TEST_SETUP(SERVO)
{
    fsp_err_t err = RM_SERVO_Open(&g_servo_ctrl, &g_servo_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
}

TEST_TEAR_DOWN(SERVO)
{
    RM_SERVO_Close(&g_servo_ctrl);
}

TEST(SERVO, servo_open)
{
    // It should open successfully
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
    fsp_err_t err = RM_SERVO_Close(&g_servo_ctrl);
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
    // When the servo is opened the timer should be open and started.
    TEST_ASSERT_EQUAL(true, g_timer_ctrl.open);
    TEST_ASSERT_EQUAL(TIMER_STATE_COUNTING, g_timer_ctrl.state);

    fsp_err_t err = RM_SERVO_Close(&g_servo_ctrl);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    // When the servo is closed the timer should be stopped and closed as well.
    TEST_ASSERT_EQUAL(false, g_timer_ctrl.open);
    TEST_ASSERT_EQUAL(TIMER_STATE_UNKNOWN, g_timer_ctrl.state);
}

TEST(SERVO, servo_set_angle)
{
    // The shared angle struct goes from -90 to 90, counterclockwise.
    // -90 will be at the maximum pulse width and 90 will be at the minimum.

    // Given that the clockspeed is hardcoded to be 50 mHz,
    // and that the pwm period counts are hardcoded to be at 1 mHz,
    // and that the range of duty cycle microseconds is 1000 to 2000,

    // 10% of 1 mHz is 100,000 counts, 5% of 1 mHz is 50,000 counts
    // The duty cycle count should range from 50000 to 100000

    // 60 + 90 = 150
    // 180 - 150 = 30
    // 30 / 180 = 0.166667ish
    //
    // (0.166666 * 50000) + 50000 is appx equal to 58333
    // The setangle call should set the period counts to be 58333
    fsp_err_t err = RM_SERVO_SetAngle(&g_servo_ctrl, 60);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    TEST_ASSERT_EQUAL(58333, g_timer_ctrl.duty_cycle);
}
