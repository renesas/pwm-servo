#include "unity_fixture.h"

TEST_GROUP_RUNNER(SERVO)
{
    RUN_TEST_CASE(SERVO, servo_open);
    RUN_TEST_CASE(SERVO, servo_close);
    RUN_TEST_CASE(SERVO, servo_manages_timer_open_and_close);
    RUN_TEST_CASE(SERVO, servo_set_angle);
}

TEST_GROUP_RUNNER(SERVO_PARAM_CHECK)
{
    RUN_TEST_CASE(SERVO_PARAM_CHECK, already_open);
    RUN_TEST_CASE(SERVO_PARAM_CHECK, not_open);
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(SERVO);
    RUN_TEST_GROUP(SERVO_PARAM_CHECK);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
