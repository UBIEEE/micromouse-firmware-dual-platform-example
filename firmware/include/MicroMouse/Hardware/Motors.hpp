#pragma once

namespace hardware {

void MotorsInit();
void MotorsShutdown();

void MotorsSetPercentOutputs(float left, float right);
void MotorsGetEncoderVelocities(float &leftMMPS, float &rightMMPS);

} // namespace hardware
