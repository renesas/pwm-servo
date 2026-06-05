#include "rm_servo.h"
#include "unity_fixture.h"
#include "test_servo_shared.h"

TEST_GROUP(SERVO_PARAM_CHECK);

TEST_SETUP(SERVO_PARAM_CHECK)
{
}

TEST_TEAR_DOWN(SERVO_PARAM_CHECK)
{
    RM_SERVO_Close(&g_servo_ctrl);
}

TEST(SERVO_PARAM_CHECK, already_open)
{
    TEST_ASSERT_EQUAL(FSP_SUCCESS, RM_SERVO_Open(&g_servo_ctrl, &g_servo_cfg));
    TEST_ASSERT_EQUAL(FSP_ERR_ALREADY_OPEN, RM_SERVO_Open(&g_servo_ctrl, &g_servo_cfg));
}

TEST(SERVO_PARAM_CHECK, not_open)
{
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, RM_SERVO_Close(&g_servo_ctrl));
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, RM_SERVO_SetAngle(&g_servo_ctrl, 0));
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, RM_SERVO_SetPercent(&g_servo_ctrl, 0));
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, RM_SERVO_SetTimerCounts(&g_servo_ctrl, 0));
}
