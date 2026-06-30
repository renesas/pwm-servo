#include <rs_servo_motor/rs_servo_demo_fpb_ra2e3_sg90.h>

/* Motor configuration info from the SG90 datasheet. */
const servo_device_cfg_t g_sg90_motor_cfg =
{
    .minimum_angle = -90,
    .maximum_angle = 90,
    .minimum_microseconds = 1000,
    .maximum_microseconds = 2000,
    .direction = SERVO_DIRECTION_CLOCKWISE
};

servo_ctrl_t g_sg90_servo_ctrl = {0};

fsp_err_t servo_demo_entry(void)
{
    fsp_err_t err = FSP_SUCCESS;

    while(err == FSP_SUCCESS)
    {
        /* Perform a timed sweep through every angle of the motor. */
        err = RS_SERVO_SweepRangeOnce(&g_sg90_servo_ctrl, &g_sg90_motor_cfg );
    }

    err = RS_SERVO_Close(&g_sg90_servo_ctrl);

    return err;
}
