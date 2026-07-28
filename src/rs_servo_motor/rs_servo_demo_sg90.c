/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/* Motor configuration info from the SG90 datasheet. */
#include <rs_servo.h>

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
        err = rs_servo_SweepRangeOnce(&g_sg90_servo_ctrl, &g_sg90_motor_cfg );
    }

    /* Close the servo control instance and timer hardware if an error occurs. */
    err = rs_servo_Close(&g_sg90_servo_ctrl);

    return err;
}
