#include "unity_fixture.h"

TEST_GROUP_RUNNER(SERVO)
{
    RUN_TEST_CASE(SERVO, servo_open);
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(SERVO);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
