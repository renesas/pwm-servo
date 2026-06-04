#include "unity_fixture.h"

TEST_GROUP_RUNNER(SERVO)
{
    RUN_TEST_CASE(SERVO, servo_open);
    RUN_TEST_CASE(SERVO, servo_close);
    RUN_TEST_CASE(SERVO, servo_manages_timer_open_and_close);
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(SERVO);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
