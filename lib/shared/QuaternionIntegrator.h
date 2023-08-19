//
// Created by Nikilesh Ramesh on 19/08/2023.
//

#ifndef MRAS_QUATERNIONINTEGRATOR_H
#define MRAS_QUATERNIONINTEGRATOR_H

#include "Subsystem.h"
#include "SystemMessage.h"
#include "Arduino.h"
#include "math.h"
/* Hamilton convention (scalar first) */
class QuaternionIntegrator : public Subsystem {
public:
    QuaternionIntegrator(uint8_t id, float delta) : Subsystem(id) {
        dt = delta;
    };
    ~QuaternionIntegrator(){};
    static void normalize(float * q);
    static void quatmultiply(const float * q1, const float * q2, float * q);
    static void cross_3D(const float * v1, const float * v2, float * v3);
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;
    void on_message(SystemMessage *msg) override;
    void integrate();

    SUBSYSTEM_NAME("QuaternionIntegrator")
private:
    float w_n[3];
    float w_nm1[3];
    float w_bar[3];
    float w_cross[3];
    float q_n[4];
    float q_np1[4];
    float dt;
    float norm_w_n;

    bool first;
    bool recieved;

    uint32_t last_time;
    uint32_t current_time;
};


#endif //MRAS_QUATERNIONINTEGRATOR_H
