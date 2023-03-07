#include <iostream>
#include <memory>
#include <chrono>
#include "include/FakeMotor.h"
#include "include/Controller.h"
int main(){
  std::cout << "A Simple Fake Motor Program" << std::endl;
  std::unique_ptr<MotorBase> fakeMotor (new FakeMotor(100, 100, 5000));
  std::unique_ptr<Controller> controller (new Controller(std::move(fakeMotor), 1000, 6000));
  while (!controller->isStopped()){
    auto ts_now = std::chrono::steady_clock::now();
    controller->loopService(ts_now);
  }


}
