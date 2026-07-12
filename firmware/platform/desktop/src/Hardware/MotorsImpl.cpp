#include <MicroMouse/Hardware/Motors.hpp>

namespace hardware {

/**
 * On desktop you don't have actual motors or encoders to control, so you can
 * choose to simulate a drivetrain or maybe just log the motor outputs to the
 * console, it is up to you.
 */

void MotorsInit() {}

void MotorsShutdown() {}

void MotorsSetPercentOutputs(float left, float right) {}

void MotorsGetEncoderVelocities(float &leftMMPS, float &rightMMPS) {
  leftMMPS = rightMMPS = 0.f;
}

} // namespace hardware
