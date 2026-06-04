/*
 * servo.h
 *
 *  Created on: Jun 1, 2026
 *      Author: a5158373
 */

#ifndef RM_SERVO_H_
#define RM_SERVO_H_

#include "bsp_api.h"
#include <stdint.h>
#include <stdbool.h>
#include "r_timer_api.h"

typedef enum e_servo_direction_t
{
    SERVO_DIRECTION_CLOCKWISE,
    SERVO_DIRECTION_COUNTERCLOCKWISE,
} servo_direction_t;

typedef struct st_servo_ctrl
{
    bool open;

    uint16_t steps;

    // Pointer to timer instance
    const timer_instance_t * p_timer_instance;

    // Angle range (in degrees) for SetAngle API
    int16_t minimum_angle;
    int16_t maximum_angle;

    // Millisecond values used to calculate duty cycle range
    uint16_t minimum_microseconds;
    uint16_t maximum_microseconds;

    // Setting to set whether servo rotates clockwise or counterclockwise
    servo_direction_t servo_direction;
} servo_ctrl_t;

typedef struct st_servo_cfg
{
    // Pointer to timer instance
    const timer_instance_t * p_timer_instance;

    // Angle range (in degrees) for SetAngle API
    const int16_t minimum_angle;
    const int16_t maximum_angle;

    // Microsecond values used to calculate duty cycle range
    const uint16_t minimum_microseconds;
    const uint16_t maximum_microseconds;

    // Setting to set whether servo rotates clockwise or counterclockwise
    const servo_direction_t servo_direction;
} servo_cfg_t;

fsp_err_t RM_SERVO_Open(servo_ctrl_t * const p_ctrl, const servo_cfg_t * const p_cfg);
fsp_err_t RM_SERVO_Close(servo_ctrl_t * const p_ctrl);
fsp_err_t RM_SERVO_SetAngle(servo_ctrl_t * const p_ctrl, int16_t angle);
fsp_err_t RM_SERVO_SetPercent(servo_ctrl_t * const p_ctrl, float percentage);

// TODO: Better name for this function?
fsp_err_t RM_SERVO_SetTimerCounts(servo_ctrl_t * const p_ctrl, uint32_t count);

#endif /* RM_SERVO_H_ */
