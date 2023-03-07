#include "../include/Controller.h"

Controller::Controller(std::unique_ptr<MotorBase> motor, int run_time, int run_velocity){
  motor_ = std::move(motor);
  initVars(motor_->getAccel(), motor_->getDecel(), run_time, run_velocity);
}

void Controller::initVars(int accel_duration, int decel_duration, int run_time, int run_velocity){
  curr_state_ = idle;
  accel_duration_ = accel_duration;
  decel_duration_ = decel_duration;
  cruise_duration_ = run_time - (accel_duration_ + decel_duration_);
  velocity_ = run_velocity;
}

void Controller::loopService(timestamp_t ts_now){
  std::cout << motor_state_map_[curr_state_] << std::endl;
  if (curr_state_ == idle && next_state_ == idle){
    next_state_ = accel;
  }
  stateMachine(ts_now);
}

void Controller::stateMachine(timestamp_t ts_now){
  switch(next_state_){
    case accel:
    goToAccel(ts_now);
    break;
    case cruise:
    goToCruise(ts_now);
    break;
    case decel:
    goToDecel(ts_now);
    break;
    case stopped:
    goToStopped(ts_now);
    break;
    case error:
    goToError(ts_now);
    break;
    case idle:
    goToIdle(ts_now);
    break;
  }
}

void Controller::goToAccel(timestamp_t ts_now){
  if (curr_state_ == idle && next_state_ == accel){
    curr_state_ = accel;
    accel_time_ = ts_now + std::chrono::milliseconds(accel_duration_);
    int resp = motor_->runMotor(velocity_);
    if (resp == -1){
      next_state_ = error;
    }
  }
  if (ts_now > accel_time_){
    next_state_ = cruise;
  }
}

void Controller::goToCruise(timestamp_t ts_now){
  if (curr_state_ == accel && next_state_ == cruise){
    curr_state_ = cruise;
    cruise_time_ = ts_now + std::chrono::milliseconds(cruise_duration_);
  }
  if (ts_now > cruise_time_){
    next_state_ = decel;
  }
}

void Controller::goToDecel(timestamp_t ts_now){
  if (curr_state_ == cruise && next_state_ == decel){
    curr_state_ = decel;
    decel_time_ = ts_now + std::chrono::milliseconds(decel_duration_);
  }
  if (ts_now > decel_time_){
    next_state_ = idle;
  }
}

void Controller::goToIdle(timestamp_t ts_now){
  if (curr_state_ == decel && next_state_ == idle){
    curr_state_ = idle;
    next_state_ = stopped;
  }
}

void Controller::goToStopped(timestamp_t ts_now){
  is_stopped_ = true;

}

void Controller::goToError(timestamp_t ts_now){
  if (next_state_ == error){
    next_state_ = stopped;
    curr_state_ = error;
  }
}

bool Controller::isStopped(){
  return is_stopped_;
}
