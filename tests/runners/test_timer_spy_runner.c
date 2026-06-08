#include "unity_fixture.h"

TEST_GROUP_RUNNER(TIMER_SPY)
{
    RUN_TEST_CASE(TIMER_SPY, test_open)
    RUN_TEST_CASE(TIMER_SPY, test_open_close)
    RUN_TEST_CASE(TIMER_SPY, test_already_open)
    RUN_TEST_CASE(TIMER_SPY, test_not_open_err)
    RUN_TEST_CASE(TIMER_SPY, test_timer_start_stop)
    RUN_TEST_CASE(TIMER_SPY, test_timer_info_get)
    RUN_TEST_CASE(TIMER_SPY, test_timer_info_get)
    RUN_TEST_CASE(TIMER_SPY, test_timer_duty_cycle_set)
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(TIMER_SPY);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
