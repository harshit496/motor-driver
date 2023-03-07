#include "MotorBase.h"
#include <iostream>
class FakeMotor : public MotorBase{
    public:

    explicit FakeMotor(int accel, int decel, int max_velocity);

    int getAccel();
    int getDecel();
    int getMaxVelocity();
    void setAccel(int accel);
    void setDecel(int decel);
    void setMaxVelocity(int max_velocity);
    int runMotor(int velocity);
    int stopMotor();

    private:

    int accel_; // millisecs
    int decel_; // millisecs
    int max_velocity_; // rpm
};
