#pragma once

void DriveInit();
void DriveProcess();
void DriveShutdown();

void DriveSetMotorVelocities(float leftVelocityMMPS, float rightVelocityMMPS);
