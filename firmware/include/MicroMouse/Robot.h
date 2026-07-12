#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define ROBOT_UPDATE_PERIOD_MS 10
#define ROBOT_UPDATE_PERIOD_S (ROBOT_UPDATE_PERIOD_MS / 1000.0f)
#define ROBOT_UPDATE_FREQ_HZ (1000 / ROBOT_UPDATE_PERIOD_MS)

/**
 * RobotInit() and RobotShutdown() should be called once at the beginning and
 * end of the program respectively by platform implementation.
 */
void RobotInit();
void RobotShutdown();

/**
 * RobotProcess() should be called every ROBOT_UPDATE_PERIOD_MS milliseconds by
 * platform implementation.
 */
void RobotProcess();

#ifdef __cplusplus
}
#endif
