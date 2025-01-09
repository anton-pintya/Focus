//
// Created by apin on 04.01.2025.
//

#include "IntegratorNode.hpp"

#include "utils/print_info.hpp"


using namespace vins::nodes;

IntegratorNode::IntegratorNode(const std::string &name)
    : Node(name) {

}


void IntegratorNode::init() {

}


void IntegratorNode::run() {
    while (true) {

        if (_last_time == std::chrono::steady_clock::time_point::min()) {
            _last_time = std::chrono::steady_clock::now();

            _accel_msg_prev = _accel_sub.receive();
            _gyro_msg_prev = _gyro_sub.receive();

            continue;
        }

        _accel_msg = _accel_sub.receive();
        _gyro_msg = _gyro_sub.receive();

        if (_accel_msg.timestamp <= _accel_msg_prev.timestamp || _gyro_msg.timestamp <= _gyro_msg_prev.timestamp) {
            continue;
        }

        auto now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration_cast<std::chrono::duration<double>>(now - _last_time).count();
        _last_time = now;

        _update_pose(dt);

        _accel_msg_prev = _accel_msg;
        _gyro_msg_prev = _gyro_msg;
    }
}


void IntegratorNode::_update_pose(double dt) {
    // Update orientation using gyro data
    cv::Vec3d omega(_gyro_msg.x, _gyro_msg.y, _gyro_msg.z);
    cv::Quatd delta_q(1, omega[0] * dt / 2, omega[1] * dt / 2, omega[2] * dt / 2);

    cv::Quatd orientation = cv::Quatd::createFromAngleAxis(cv::norm(omega * dt), omega);
    orientation = (orientation * delta_q).normalize();

    // Update velocity and position using accel data
    cv::Vec3d accel(_accel_msg.x, _accel_msg.y, _accel_msg.z);
    cv::Vec3d gravity(0, 0, -9.81);
    cv::Vec3d accel_world = orientation.toRotMat3x3() * accel + gravity;
    cv::Vec3d velocity = accel_world * dt;
    cv::Vec3d position = velocity * dt;

    // Update velocity, position and orientation
    _velocity += velocity;
    _position += position;
    _orientation = orientation;

    // Print updated position and orientation
//    vins_utils::VINS_DATA("Position: (%.4f, %.4f, %.4f)", _position[0], _position[1], _position[2]);
//    vins_utils::VINS_DATA("Velocity: (%.4f, %.4f, %.4f)", _velocity[0], _velocity[1], _velocity[2]);
//    vins_utils::VINS_DATA("Orientation: (%.4f, %.4f, %.4f, %.4f)", _orientation.w, _orientation.x, _orientation.y, _orientation.z);
}