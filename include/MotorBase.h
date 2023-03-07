#pragma once
class MotorBase{
    public:

    virtual int getAccel() = 0;
    virtual int getDecel() = 0;
    virtual int getMaxVelocity() = 0;
    virtual void setAccel(int accel) = 0;
    virtual void setDecel(int decel) = 0;
    virtual void setMaxVelocity(int max_velocity) = 0;
    virtual int runMotor(int velocity) = 0;
    virtual int stopMotor() = 0;

};