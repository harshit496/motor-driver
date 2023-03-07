
#include "../include/FakeMotor.h"
FakeMotor::FakeMotor(int accel, int decel, int max_velocity) : MotorBase(){
  accel_ = accel;
  decel_ = decel;
  max_velocity_ = max_velocity;
}


int FakeMotor::getAccel(){
  return accel_;
}

int FakeMotor::getDecel(){
  return decel_;
}

int FakeMotor::getMaxVelocity(){
  return max_velocity_;
}

void FakeMotor::setAccel(int accel){
  accel_ = accel;
}

void FakeMotor::setDecel(int decel){
  decel_ = decel;
}

void FakeMotor::setMaxVelocity(int max_velocity){
  max_velocity_ = max_velocity;
}

int FakeMotor::runMotor(int velocity){
  if (velocity > max_velocity_){
    std::cout << "Motor Error, Velocity too high!" << std::endl;
    stopMotor();
    return -1;
  }else{
    std::cout << "Motor Spinning with " << velocity << " RPM" << std::endl;
    return 1;
  }
  return 0;
}

int FakeMotor::stopMotor() {
  std::cout << "Motor Stopped..." << std::endl;
  return 1;
}
