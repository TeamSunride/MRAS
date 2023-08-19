//
// Created by Nikilesh Ramesh on 19/08/2023.
//

#include "QuaternionIntegrator.h"
#include "system_messages/GyroDataMsg.h"

int8_t QuaternionIntegrator::setup() {
    return 0;
}
int8_t QuaternionIntegrator::loop() {
    return 0;
}
void QuaternionIntegrator::on_message(SystemMessage *msg) {
    switch (msg->get_type()) {
        case GyroDataMsg_t: {
            auto *gmsg = (GyroDataMsg *) msg;
            w_n[0] = gmsg->gyro[0];
            w_n[1] = gmsg->gyro[1];
            w_n[2] = gmsg->gyro[2];
            break;
        }
        default:
            break;
    }
}
void QuaternionIntegrator::integrate(float * w, float * q, float * q_np1) {}
void QuaternionIntegrator::normalize(float * q) {}
void QuaternionIntegrator::quatmultiply(float * q1, float * q2, float * q) {}
