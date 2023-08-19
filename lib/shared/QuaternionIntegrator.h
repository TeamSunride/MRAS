//
// Created by Nikilesh Ramesh on 19/08/2023.
//

#ifndef MRAS_QUATERNIONINTEGRATOR_H
#define MRAS_QUATERNIONINTEGRATOR_H

#include "Subsystem.h"
#include "SystemMessage.h"

class QuaternionIntegrator : public Subsystem {
public:
    QuaternionIntegrator(uint8_t id) : Subsystem(id) {};
    ~QuaternionIntegrator(){};
    void normalize(float * q);
    void quatmultiply(float * q1, float * q2, float * q);
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;
    void on_message(SystemMessage *msg) override;
    void integrate(float * w, float * q, float * q_np1);

    SUBSYSTEM_NAME("QuaternionIntegrator")
private:
    float w_n[3];
    float w_np1[3];
    float q_n[4];
    float q_np1[4];
};


#endif //MRAS_QUATERNIONINTEGRATOR_H
