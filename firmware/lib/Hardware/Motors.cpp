#include <MicroMouse/Hardware/Motors.hpp>

namespace hardware {

/**
 * Unimplemented weakly-linked functions. These will be overridden by the
 * target-specific implementation.
 */

__attribute__((weak)) void MotorsInit() {}

__attribute__((weak)) void MotorsShutdown() {}

__attribute__((weak)) void MotorsSetPercentOutputs(float left, float right) {}

__attribute__((weak)) void MotorsGetEncoderVelocities(float &leftMMPS,
                                                      float &rightMMPS) {
  leftMMPS = rightMMPS = 0.f;
}

} // namespace hardware
