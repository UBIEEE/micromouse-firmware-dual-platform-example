#include <MicroMouse/Hardware/Motors.hpp>

namespace hardware {

/**
 * TODO: Implement the functions below to interface with the actual motor
 * hardware.
 */

void MotorsInit() {}

void MotorsShutdown() {}

void MotorsSetPercentOutputs(float left, float right) {}

void MotorsGetEncoderVelocities(float &leftMMPS, float &rightMMPS) {
  leftMMPS = rightMMPS = 0.f;
}

} // namespace hardware
