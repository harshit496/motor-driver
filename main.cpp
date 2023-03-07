#include <iostream>
#include <memory>
#include <chrono>
#include "include/FakeMotor.h"
#include "include/Controller.h"
int main(){
  std::cout << "A Simple Fake Motor Program\n" << std::endl;
  int accel_time, decel_time, max_velocity, velocity, run_time;
  std::cout << "Enter Acceleration Time (ms): ";
  std::cin >> accel_time;
  std::cout << "Enter Deceleration Time (ms): ";
  std::cin >> decel_time;
  std::cout << "Enter Max Velocity (rpm): ";
  std::cin >> max_velocity;
  std::cout << "Enter Run Time Velocity (rpm): ";
  std::cin >> velocity;
  std::cout << "Enter Total Run Time (ms): ";
  std::cin >> run_time;
  std::unique_ptr<MotorBase> fakeMotor (new FakeMotor(accel_time, decel_time, max_velocity));
  std::unique_ptr<Controller> controller (new Controller(std::move(fakeMotor), run_time, velocity));

  std::cout << "\n\nStarting Fake Motor Program..." << std::endl;

  while (!controller->isStopped()){
    auto ts_now = std::chrono::steady_clock::now();
    controller->loopService(ts_now);
  }


}
