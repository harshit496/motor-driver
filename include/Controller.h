#include "../include/MotorBase.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <map>
class Controller{
    public:
    typedef std::chrono::time_point<std::chrono::steady_clock> timestamp_t;
    Controller(std::unique_ptr<MotorBase> motor, int run_time, int run_velocity);

    void loopService(timestamp_t ts_now);
    bool isStopped();
    
    private:
    enum MotorState {accel, decel, cruise, idle, stopped, error};
    MotorState curr_state_, next_state_ = idle;
    std::unique_ptr<MotorBase> motor_;
    int accel_duration_, decel_duration_, velocity_, cruise_duration_;
    timestamp_t accel_time_, decel_time_, cruise_time_;
    bool is_stopped_ = false;
    std::map<MotorState, std::string> motor_state_map_ = {
      {accel, "Accelerating"},
      {decel, "Decelerating"},
      {cruise, "Cruising"},
      {idle, "Idle"},
      {error, "Errored"},
      {stopped, "Stopped"}
    };

    void stateMachine(timestamp_t ts_now);
    void goToAccel(timestamp_t ts_now);
    void goToCruise(timestamp_t ts_now);
    void goToDecel(timestamp_t ts_now);
    void goToStopped(timestamp_t ts_now);
    void goToError(timestamp_t ts_now);
    void goToIdle(timestamp_t ts_now);
    void initVars(int accel_duration, int decel_duration, int run_time, int run_velocity);
};
