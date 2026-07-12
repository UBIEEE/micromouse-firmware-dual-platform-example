#include <MicroMouse/Robot.h>

#include <MicroMouse/Subsystems/Drive.hpp>

void RobotInit() {
  // Initialize subsystems here.

  DriveInit();
}

void RobotShutdown() {
  // Shutdown subsystems here.

  DriveShutdown();
}

void RobotProcess() {
  // This function will be called every ROBOT_UPDATE_PERIOD_MS milliseconds.
  // Process sensor inputs and update motor outputs here.

  DriveProcess();
}
