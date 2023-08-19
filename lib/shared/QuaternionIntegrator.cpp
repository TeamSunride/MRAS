//
// Created by Nikilesh Ramesh on 19/08/2023.
//

#include "QuaternionIntegrator.h"
#include "system_messages/GyroDataMsg.h"

int8_t QuaternionIntegrator::setup() {
    first = true;
    recieved = false;
    q_n[0] = 1;
    q_n[1] = 0;
    q_n[2] = 0;
    q_n[3] = 0;
    return 0;
}
int8_t QuaternionIntegrator::loop() {
    current_time = millis();
    if (first && recieved){
        w_nm1[0] = w_n[0];
        w_nm1[1] = w_n[1];
        w_nm1[2] = w_n[2];
        first = false;
        recieved = false;
        last_time = millis();
    }
    else if (!first && recieved && (float)(current_time - last_time) > dt*1000){

        integrate();
        last_time = current_time;
        log("%f,%f,%f,%f",q_np1[0], q_np1[1], q_np1[2], q_np1[3]);
    }

    return 0;
}
void QuaternionIntegrator::on_message(SystemMessage *msg) {
    switch (msg->get_type()) {
        case GyroDataMsg_t: {
            auto *gmsg = (GyroDataMsg *) msg;
            w_n[0] = gmsg->gyro[0];
            w_n[1] = gmsg->gyro[1];
            w_n[2] = gmsg->gyro[2];
            recieved = true;
            break;
        }
        default:
            break;
    }
}
void QuaternionIntegrator::integrate() {
    w_bar[0] = (w_n[0] + w_nm1[0])/2;
    w_bar[1] = (w_n[1] + w_nm1[1])/2;
    w_bar[2] = (w_n[2] + w_nm1[2])/2;

    auto norm_w_bar = (float) sqrt( (double) (w_bar[0]*w_bar[0] + w_bar[1]*w_bar[1] + w_bar[2]*w_bar[2]));
    float angle = norm_w_bar*dt/2;
    auto sin_angle = (float) sin((double) angle);
    auto cos_angle = (float) cos((double) angle);
    float q_bar[4] = {cos_angle, sin_angle*w_bar[0]/norm_w_bar, sin_angle*w_bar[1]/norm_w_bar, sin_angle*w_bar[2]/norm_w_bar};
    float coeff = dt*dt / 24;
    cross_3D(w_nm1, w_n, w_cross);
    float q_dot[4] = {0, coeff*w_cross[0], coeff*w_cross[1], coeff*w_cross[2]};
    float q_sum[4] = {q_bar[0] + q_dot[0], q_bar[1] + q_dot[1], q_bar[2] + q_dot[2], q_bar[3] + q_dot[3]};
    quatmultiply(q_n, q_sum, q_np1);
    normalize(q_np1);
    q_n[0] = q_np1[0];
    q_n[1] = q_np1[1];
    q_n[2] = q_np1[2];
    q_n[3] = q_np1[3];
    w_nm1[0] = w_n[0];
    w_nm1[1] = w_n[1];
    w_nm1[2] = w_n[2];
}
void QuaternionIntegrator::normalize(float * q) {
    auto norm = (float) sqrt( (double) (q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]));
    q[0] = q[0]/norm;
    q[1] = q[1]/norm;
    q[2] = q[2]/norm;
    q[3] = q[3]/norm;
}
void QuaternionIntegrator::quatmultiply(const float * q1, const float * q2, float * q) {
    q[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
    q[1] = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
    q[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
    q[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
}
void QuaternionIntegrator::cross_3D(const float *v1, const float *v2, float *v3) {
    v3[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v3[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v3[2] = v1[0]*v2[1] - v1[1]*v2[0];
}
