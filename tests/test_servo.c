#include "unity_fixture.h"
#include "rm_servo.h"
#include "timer_spy.h"

// TIMER INSTANCE
timer_spy_ctrl_t g_timer_ctrl;
timer_cfg_t      g_timer_cfg;

const timer_instance_t g_timer0_instance =
{
    .p_api  = &g_timer_on_timer_spy,
    .p_cfg  = &g_timer_cfg,
    .p_ctrl = (timer_ctrl_t *) &g_timer_ctrl,
};

// SERVO STRUCTURES
servo_ctrl_t g_servo_ctrl;

servo_cfg_t g_servo_cfg =
{
    .servo_direction      = SERVO_DIRECTION_CLOCKWISE,
    .minimum_angle        = 0,
    .maximum_angle        = 180,
    .minimum_microseconds = 1000,
    .maximum_microseconds = 2000,
    .p_timer_instance     = &g_timer0_instance,
};

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
