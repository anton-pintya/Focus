//
// Created by apin on 04.01.2025.
//

#ifndef VINS_FOCUS_INTEGRATORNODE_HPP
#define VINS_FOCUS_INTEGRATORNODE_HPP


#include "core/transport/Node.hpp"
#include "core/transport/Publisher.hpp"
#include "core/transport/Subscriber.hpp"

#include "core/transport/msg_generated/sensor_accel.hpp"
#include "core/transport/msg_generated/sensor_gyro.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/quaternion.hpp>

#include <chrono>


namespace vins {
namespace nodes {

class IntegratorNode : public vins::core::transport::Node {

public:
    /*********Public fields*********/


    /*********Public methods*********/
    IntegratorNode(const std::string &name);


    void init() override;


protected:
    /*********Protected fields*********/


    /*********Protected methods*********/
    void run() override;


private:
    /*********Private fields*********/
    vins::core::transport::Publisher<sensor_accel> _accel_pub;
    vins::core::transport::Publisher<sensor_gyro> _gyro_pub;

    vins::core::transport::Subscriber<sensor_accel> _accel_sub;
    vins::core::transport::Subscriber<sensor_gyro> _gyro_sub;

    sensor_accel _accel_msg, _accel_msg_prev;
    sensor_gyro _gyro_msg, _gyro_msg_prev;

    cv::Vec3d _position{0, 0, 0};
    cv::Vec3d _velocity{0, 0, 0};
    cv::Quatd _orientation{1, 0, 0, 0};

    std::chrono::steady_clock::time_point _last_time{std::chrono::steady_clock::time_point::min()};

    /*********Private methods*********/
    void _update_pose(double dt);

};

}; // namespace nodes
}; // namespace vins


#endif //VINS_FOCUS_INTEGRATORNODE_HPP
