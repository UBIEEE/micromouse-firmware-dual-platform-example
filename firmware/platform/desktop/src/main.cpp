#include <MicroMouse/Robot.h>

#include <chrono>
#include <csignal>
#include <thread>

static volatile std::sig_atomic_t m_signalStatus = 0;

static void SignalHandler(int signal) { m_signalStatus = signal; }

int main(int argc, char *argv[]) {
  // TODO: Use command line arguments?

  RobotInit();

  while (m_signalStatus == 0) {
    auto start = std::chrono::steady_clock::now();

    RobotProcess();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> elapsed = end - start;
    if (elapsed.count() < ROBOT_UPDATE_PERIOD_MS) {
      auto sleepDuration =
          std::chrono::milliseconds(ROBOT_UPDATE_PERIOD_MS) - elapsed;
      std::this_thread::sleep_for(sleepDuration);
    }
  }

  RobotShutdown();

  return 0;
}
