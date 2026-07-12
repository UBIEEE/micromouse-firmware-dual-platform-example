#include <MicroMouse/Subsystems/Drive.hpp>

#include <MicroMouse/Hardware/Motors.hpp>

#include <algorithm>

static constexpr float kMaxMotorVelocityMMPS = 1000.0f;

static float m_leftTargetMotorVelocityMMPS = 0.f;
static float m_rightTargetMotorVelocityMMPS = 0.f;

void DriveInit() {
  hardware::MotorsInit();
  hardware::MotorsSetPercentOutputs(0.f, 0.f);
}

void DriveShutdown() {
  hardware::MotorsSetPercentOutputs(0.f, 0.f);
  hardware::MotorsShutdown();
}

void DriveProcess() {
  float encoderLeftMMPS = 0.f;
  float encoderRightMMPS = 0.f;
  hardware::MotorsGetEncoderVelocities(encoderLeftMMPS, encoderRightMMPS);

  /**
   * TODO: Use PID controllers to calculate raw percent outputs based on the
   * target and measured velocities.
   */
  float leftPercentOutput = 0.f;
  float rightPercentOutput = 0.f;
  hardware::MotorsSetPercentOutputs(leftPercentOutput, rightPercentOutput);
}

void DriveSetMotorVelocities(float leftVelocityMMPS, float rightVelocityMMPS) {
  m_leftTargetMotorVelocityMMPS = std::clamp(
      leftVelocityMMPS, -kMaxMotorVelocityMMPS, kMaxMotorVelocityMMPS);
  m_rightTargetMotorVelocityMMPS = std::clamp(
      rightVelocityMMPS, -kMaxMotorVelocityMMPS, kMaxMotorVelocityMMPS);
}
