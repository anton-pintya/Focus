//
// Created by apin on 01.01.2025.
//

#include "IMUNode.hpp"
#include "sensors/real_sensors/imu/basic_source/InertialSourceFactory.hpp"
//#include <utility>


using namespace vins::nodes;


IMUNode::IMUNode(const std::string &name, std::string config_path): Node(name) {
    _imu_source = vins::sensors::InertialSourceFactory::createInertialSource(std::move(config_path));
};


IMUNode::IMUNode(const std::string &name, const cv::FileStorage &config): Node(name) {
    _imu_source = vins::sensors::InertialSourceFactory::createInertialSource(config);
};


void IMUNode::init() {
    _imu_source->print_info();
}


void IMUNode::run() {
    while (_running) {
        _imu_source->read();
        publish();
    }
}